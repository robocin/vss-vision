#include "PositionProcessing.h"
#include "Utils/EnumsAndConstants.h"

void PositionProcessing::saveXML()
{
  cv::FileStorage file(POSITION_PROCESSING_FILE,cv::FileStorage::WRITE);
  file<<"Default";
  file<<"{";
  file<<MINSIZE<<param[MINSIZE];
  file<<MAXSIZE<<param[MAXSIZE];
  file<<MINSIZEBALL<<param[MINSIZEBALL];
  file<<MAXSIZEBALL<<param[MAXSIZEBALL];
  file<<BLOBMAXDIST<<param[BLOBMAXDIST ];
  file<<MYTEAM<<param[MYTEAM];
  file<<ENEMYTEAM<<param[ENEMYTEAM];
  file<<ENEMYSEARCH<<param[ENEMYSEARCH];
  file<<SHOWELEMENT<<param[SHOWELEMENT];
  file<<"}";
  file.release();

}

void PositionProcessing::matchBlobs(cv::Mat& debugFrame){

  FieldRegions groupedBlobs = pairBlobs();
  static Players empty_players;

  vss.setPlayers(empty_players);

  // Settting team positions
  Players teamA;
  findTeam(teamA, debugFrame, groupedBlobs.team);
  setTeamColor(getTeamColor() == Color::YELLOW ? Color::BLUE : Color::YELLOW);
  Players teamB;
  findTeam(teamB, debugFrame, groupedBlobs.enemies);
  setTeamColor(getTeamColor() == Color::YELLOW ? Color::BLUE : Color::YELLOW);

  Players allPlayers;
  allPlayers.insert(allPlayers.end(),teamA.begin(),teamA.end());
  allPlayers.insert(allPlayers.end(),teamB.begin(),teamB.end());
  sort(allPlayers.begin(),allPlayers.end());

  Entity ball;
  findBall(ball,debugFrame);

  vss.setEntities(ball,allPlayers);
}

void PositionProcessing::findTeam(Players &players, cv::Mat& debugFrame, std::vector<Region> &teamRegions) {

  players.clear();
  filterPattern(teamRegions);
  uint teamColor = static_cast<uint>(getTeamColor());
  for (Region &region : teamRegions) {
    if(USE_OLD_PATTERN){

      int colorIndex = region.blobs[1].color;
      
      if (!Utils::isRobotColor(colorIndex)) {
        // cor invalida
        continue;
      }

      Blobs blobs = region.blobs;
      Blob b1 = blobs[1], b2 = blobs[0];
      Player robot((teamColor-1)*100 + static_cast<uint>(colorIndex) - Color::RED); // seta o id da robo na regiao
      robot.team(teamColor);
      Point newPositionInPixels = (b1.position + b2.position) * 0.5;
      Point newPosition = Utils::convertPositionPixelToCm(newPositionInPixels);
      Float newAngle = Utils::angle(b1.position, b2.position);

      robot.update(Point(newPosition.x,newPosition.y), newAngle);
      players.push_back(robot);
      cv::circle(debugFrame, Utils::convertPositionCmToPixel(Point(newPosition.x,newPosition.y)), 15, _colorCar[teamColor], 2, cv::LINE_AA);
      cv::circle(debugFrame, Utils::convertPositionCmToPixel(Point(newPosition.x,newPosition.y)), 12, _colorCar[colorIndex], 2, cv::LINE_AA);
    } 
    else if(region.blobs.size() == 3) {
      int firstSecondary = region.blobs[1].color;
      int secondSecondary = region.blobs[2].color;
      int colorIndex = ((teamColor) + (firstSecondary * MAX_ROBOTS) + (secondSecondary * MAX_ROBOTS * MAX_ROBOTS));  

      if (!Utils::isRobotColor(firstSecondary) || !Utils::isRobotColor(secondSecondary)) {
        continue;
      }

      // markedColors[size_t(newId(colorIndex))] = true;
      Blobs blobs = region.blobs;
      Blob b1 = blobs[0], b2 = blobs[1], b3 = blobs[2];
      if(newId(colorIndex) > 12)
        continue;
      
      Player robot(newId(colorIndex));
        
      robot.team(teamColor);

      cv::Point secondaryPosition = (b2.position + b3.position) * 0.5;
      Point newPositionInPixels = (b1.position + secondaryPosition) * 0.5;
      Point newPosition = Utils::convertPositionPixelToCm(newPositionInPixels);
      Float newAngle = Utils::angle(secondaryPosition, b1.position);

      auto & playerPosVel = _kalmanFilterRobots[teamColor-2][robot.id()].update(newPosition.x,newPosition.y);

      Geometry::PT filtPoint (playerPosVel(0, 0), playerPosVel(1, 0));
      Geometry::PT PlayVel(playerPosVel(2, 0), playerPosVel(3, 0));

      auto &playerRotVel = _dirFilteRobots[teamColor-2][robot.id()%100].update(std::cos(newAngle), std::sin(newAngle));
      double filterDir = std::atan2(playerRotVel(1, 0), playerRotVel(0, 0));
    
      robot.update(Point(filtPoint.x,filtPoint.y), filterDir);
      players.push_back(robot);

      cv::circle(debugFrame, Utils::convertPositionCmToPixel(newPosition), 15, _colorCar[teamColor], 2, cv::LINE_AA);
      cv::circle(debugFrame, Utils::convertPositionCmToPixel(newPosition), 12, _colorCar[teamColor], 2, cv::LINE_AA);
    }
  }
}

void PositionProcessing::findEnemys(Entities &players, cv::Mat& debugFrame, std::vector<Region> &enemyRegions) {

    players.clear();

    uint teamColor = this->_teamId == Color::YELLOW ? Color::BLUE : Color::YELLOW;

    for (Region &region : enemyRegions) {
      if (region.distance < blobMaxDist()) {
        int colorIndex = region.blobs[0].color;
        Blobs blobs = region.blobs;
        Blob b1 = blobs[0], b2 = blobs[1];
        Player robot((teamColor-1)*100 + static_cast<uint>(colorIndex) - Color::RED);
        robot.team(teamColor);
        Point newPositionInPixels = b2.position ;
        Point newPosition = Utils::convertPositionPixelToCm(newPositionInPixels);

        // Debug
        cv::circle(debugFrame, newPositionInPixels, 12, _colorCar[colorIndex], 2, cv::LINE_AA);

        Float newAngle = Utils::angle(b2.position, b1.position);
        robot.update(newPosition, newAngle);
        players.push_back(robot);
      }
    }
}

void PositionProcessing::findBall(Entity &ball, cv::Mat& debugFrame) {
    // Desativar, so ativar quando encontrar
    // a bola no frame atual
    ball.outdate();
    Blob blobBall;
    Int maxArea = -1;
    blobBall.valid = false;

    for (size_t i = 0; i < CLUSTERSPERCOLOR; i++) {
      if (blob[OrangeCOL][i].area > maxArea &&
          blob[OrangeCOL][i].valid) {
        blobBall = blob[OrangeCOL][i];
        maxArea = blobBall.area;
      }
    }

    if (!blobBall.valid) {
        int fps = 30;
        auto & ballPosVel = _kalmanFilterBall[0][0].update(this->_ballLastPosition.x,this->_ballLastPosition.y);
        Geometry::PT filtPoint (ballPosVel(0, 0), ballPosVel(1, 0));
        Geometry::PT ballVel(ballPosVel(2, 0)*fps, ballPosVel(3, 0)*fps);

        Float actualTime = vss.time().getMilliseconds();
        Float dt = (actualTime-this->_ballLastTime)/1000; // dt in seconds
        this->_ballLastTime = actualTime;

        Float lostFrames = dt*fps;
        ballVel = ballVel/lostFrames;
        filtPoint.x = filtPoint.x + ballVel.x*dt;
        filtPoint.y = filtPoint.y + ballVel.y*dt;

        filtPoint.x = Utils::bound(filtPoint.x, -85, 85);
        filtPoint.y = Utils::bound(filtPoint.y, -65, 65);

        cv::circle(debugFrame, Utils::convertPositionCmToPixel(cv::Point(static_cast<int>(filtPoint.x),static_cast<int>(filtPoint.y))), 9, _colorCar[OrangeCOL], 2, cv::LINE_AA);
        //cv::line(debugFrame, Utils::convertPositionCmToPixel(cv::Point(filtPoint.x,filtPoint.y)),Utils::convertPositionCmToPixel(cv::Point(filtPoint.x+ballVel.x,filtPoint.y+ballVel.y)),_colorCar[OrangeCOL], 2);

        ball.id(0);
        ball.update(Point(filtPoint.x,filtPoint.y),atan2(ballVel.y,ballVel.x));
        this->_ballLastPosition.x = filtPoint.x;
        this->_ballLastPosition.y = filtPoint.y;
    }

    // Debug
    //cv::circle(debugFrame, blobBall.position, 9, _colorCar[OrangeCOL], 2, cv::LINE_AA);
    Point newPosition = Utils::convertPositionPixelToCm(blobBall.position);
    this->_ballLastPosition = vss.ball().position();

    auto & ballPosVel = _kalmanFilterBall[0][0].update(newPosition.x,newPosition.y);

    Geometry::PT filtPoint (ballPosVel(0, 0), ballPosVel(1, 0));
    int fps = 100;
    Geometry::PT ballVel(ballPosVel(2, 0)*fps, ballPosVel(3, 0)*fps);
    ball.update(Point(newPosition.x,newPosition.y),atan2(ballVel.y,ballVel.x));
    this->_ballLastTime = vss.time().getMilliseconds();
    ball.id(0);

    newPosition.x = Utils::bound(newPosition.x, -85, 85);
    newPosition.y = Utils::bound(newPosition.y, -65, 65);

    cv::circle(debugFrame, Utils::convertPositionCmToPixel(cv::Point(static_cast<int>(newPosition.x),static_cast<int>(newPosition.y))), 9, _colorCar[OrangeCOL], 2, cv::LINE_AA);
    //cv::line(debugFrame, Utils::convertPositionCmToPixel(cv::Point(filtPoint.x,filtPoint.y)),Utils::convertPositionCmToPixel(cv::Point(filtPoint.x+ballVel.x,filtPoint.y+ballVel.y)),_colorCar[OrangeCOL], 2);
    this->_ballLastPosition = cv::Point(static_cast<int>(newPosition.x),
                                        static_cast<int>(newPosition.y));
}

std::pair<PositionProcessing::Blob, PositionProcessing::NearestBlobInfo> PositionProcessing::getNearestPrimary(Blob current) {
  int dMin = INT_MAX, distance, team = 0;
  Blob choosen;
  NearestBlobInfo result;

  for(int teamColor = Color::BLUE ; teamColor <= Color::YELLOW ; teamColor++) {
    for(int i = 0 ; i < CLUSTERSPERCOLOR ;i++) {
      if(blob[teamColor][i].valid) {
        distance = static_cast<int>(Utils::sumOfSquares(current.position,blob[teamColor][i].position));

        if(distance < dMin) {
          dMin = distance;
          choosen = blob[teamColor][i];
          team = teamColor;
        }
      }
      else break;
    }
  }

  result.distance = dMin;
  result.teamIndex = team;
  choosen.color = team;

  return std::make_pair(choosen,result);

}

void PositionProcessing::filterPattern(Regions &regions) {

  Regions f_regions;
  // Sort regions by leftmost blob
  for (auto &r : regions) {
    if (r.blobs.size() < 3) {
      continue;
    }

    Point b0 = r.blobs[0].position;
    Point b1 = r.blobs[1].position;
    Point b2 = r.blobs[2].position;

    // Compute robot center:
    Point robot = 0.5 * (b0 + 0.5 * (b1 + b2));

    // Compute robot x and y axis vectors:
    Point vx = 0.5 * (b1 + b2) - robot;
    Point vy(-vx.y, vx.x);

    // Compute b2 projection on vy
    // Swap blobs if projection is positive (should be the opposite, but it worked this way!)
    bool swap_blobs = ((b2.x-robot.x)*vy.x+(b2.y-robot.y)*vy.y>0);
    
    if (swap_blobs) {
      std::swap(r.blobs[1], r.blobs[2]);
    }

    f_regions.push_back(r);

  //  cv::Point b2 = (r.blobs[1].position + r.blobs[2].position) * 0.5;
  //
  //
  //  double angleThreshold = 10.0 * (M_PI / 180.0);
  //  double angleDiffTo180 = std::abs(std::abs(Utils::angle(b2, b1)) - M_PI);
  //
  //  if(std::abs(Utils::angle(b2, b1)) < angleThreshold || angleDiffTo180 < angleThreshold) {
  //
  //    if (r.blobs[0].position.x > (r.blobs[1].position.x + r.blobs[2].position.x) / 2) {
  //      if(r.blobs[1].position.y > r.blobs[2].position.y){
  //        std::swap(r.blobs[1], r.blobs[2]);
  //      }
  //    }else{
  //      if(r.blobs[1].position.y < r.blobs[2].position.y){
  //        std::swap(r.blobs[1], r.blobs[2]);
  //      }
  //    }
  //  }
  //  else if(r.blobs[0].position.y < (r.blobs[1].position.y + r.blobs[2].position.y)/2) // Primary blob on top
  //  {
  //    if(r.blobs[1].position.x > r.blobs[2].position.x)
  //    { 
  //      std::swap(r.blobs[1], r.blobs[2]); 
  //    }     
  //  } 
  //  else if(r.blobs[1].position.x < r.blobs[2].position.x) // Primary blob on bottom
  //  {
  //    std::swap(r.blobs[1], r.blobs[2]);
  //  }
  //  f_regions.push_back(r);
  }
  regions = f_regions;
}

void PositionProcessing::filterTeam(Regions &regions) {
    std::unordered_map<int,Region> t_regions;
    Regions r_regions;

    for (auto &r : regions) {
        int id = r.blobs[0].id;
        if (t_regions.find(id) == t_regions.end()) { // Didn't found region of with given id
            t_regions[id] = r; // Then, associate it with this region
        } else {
            Region &t_r = t_regions[r.blobs[0].id]; // Get already existing region of same id
            t_r.blobs.push_back(r.blobs[1]); // Insert second secondary color
        }
    }

    // Set all of the new merged regions into a vector
    for (auto &r_t : t_regions) {
        r_regions.push_back(r_t.second);
    }
    // Sort them by first blob id
    std::sort(r_regions.begin(),r_regions.end());

    // Update regions with filtered blobs
    regions.assign(r_regions.begin(),r_regions.end());
}

PositionProcessing::FieldRegions PositionProcessing::pairBlobs() {
  FieldRegions result;
  std::pair<Blob, NearestBlobInfo> primary;
  Region current;

  for(int idColor = Color::RED ; idColor < Color::BROWN+1; idColor++) {
    for(int i = 0 ; i < CLUSTERSPERCOLOR ; i++) {
      if(blob[idColor][i].valid) {
        current.blobs.clear();
        primary = this->getNearestPrimary(blob[idColor][i]);
        blob[idColor][i].color = idColor;

        current.blobs.push_back(primary.first);
        current.blobs.push_back(blob[idColor][i]);
        current.team = primary.second.teamIndex;

        current.distance = primary.second.distance;
        if (current.team == this->_teamId) result.team.push_back(current);
        else if (USE_PATTERN_FOR_ENEMIES) result.enemies.push_back(current);
      } else break;
    }
  }

  if(!USE_PATTERN_FOR_ENEMIES && (result.enemies.empty() || result.enemies.size() < 3))
  {
    int idColor = this->_teamId == Color::YELLOW ? Color::BLUE : Color::YELLOW;
    int qnt = 0;
    for(int i = 0 ; i < CLUSTERSPERCOLOR ; i++) {
      if(blob[idColor][i].valid) {
        current.blobs.clear();

        blob[idColor][i].color = current.team;
        current.blobs.push_back(blob[idColor][i]);
        current.blobs.push_back(blob[idColor][i]);
        current.team = idColor;
        current.distance = 0.0;
        result.enemies.push_back(current);
      }
    }
  }
  filterTeam(result.team);
  filterTeam(result.enemies);

  return result;
}

void PositionProcessing::setUp(std::string var, int value)
{
  this->param[var] = value;

  if(var == MINSIZE)
  {
    this->_minSize = value;
  }
  else if(var == MAXSIZE)
  {
    this->_maxSize = value;
  }
  else if(var == MINSIZEBALL)
  {
    this->_minSizeBall = value;
  }
  else if(var == MAXSIZEBALL)
  {
    this->_maxSizeBall = value;
  }
  else if(var == BLOBMAXDIST)
  {
    this->_blobMaxDist = value;
  }
  else if(var == MYTEAM)
  {
    this->_teamId = value;
  }
  else if(var == ENEMYTEAM)
  {
    this->_enemyTeam = value;
  }
  else if(var == ENEMYSEARCH)
  {
    this->_enemySearch = value;
  }
  else if(var == SHOWELEMENT)
  {
    this->_showElement = value;
  }
  else
  {
    spdlog::get("Vision")->warn("Variavel Invalida");
  }

}

int PositionProcessing::setColorIndex(int color, int index)
{
  int sameIndex = this->_colorIndex[color];
  for( int i = RedCOL ; i < ColorStrange ; i ++)
    if( this->_colorIndex[i] == index)
    {
      this->_colorIndex[i] = -1;
    }
  this->_colorIndex[color] = index;

  return sameIndex;
}

int PositionProcessing::getParam(std::string var)
{
  return this->param[var];
}

void PositionProcessing::initBlob(PositionProcessing::Blob &blob)
{
  blob.position = cv::Point(-1,-1);
  blob.area = 0;
  blob.angle = 0;
  blob.valid = false;
}

void PositionProcessing::initDefault()
{
  this->_colorCar[NoCOL] = cv::Scalar(255,255,255);
  this->_colorCar[OrangeCOL] = cv::Scalar(0,165,255);
  this->_colorCar[BlueCOL] = cv::Scalar(255,0,0);
  this->_colorCar[YellowCOL] = cv::Scalar(0,255,255);
  this->_colorCar[RedCOL] = cv::Scalar(0,0,255);
  this->_colorCar[GreenCOL] = cv::Scalar(0,255,0);
  this->_colorCar[PinkCOL] = cv::Scalar(255,0,255);
  this->_colorCar[LightBlueCOL] = cv::Scalar(210,252,4);
  this->_colorCar[PurpleCOL] = cv::Scalar(200,055,055);
  this->_colorCar[BrownCOL] = cv::Scalar(38,66,107);
  this->_colorCar[ColorStrange] = cv::Scalar(255,255,255);

  this->segColor[NoCOL] = cv::Vec3b(0,0,0);
  this->segColor[OrangeCOL] = cv::Vec3b(20,147,255);
  this->segColor[BlueCOL] = cv::Vec3b(255,0,0);
  this->segColor[YellowCOL] = cv::Vec3b(0,255,255);
  this->segColor[RedCOL] = cv::Vec3b(0,0,255);
  this->segColor[GreenCOL] = cv::Vec3b(0,255,0);
  this->segColor[PinkCOL] = cv::Vec3b(164,0,255);
  this->segColor[LightBlueCOL] = cv::Vec3b(206,250,135);
  this->segColor[PurpleCOL] = cv::Vec3b(250,230,230);
  this->segColor[BrownCOL] = cv::Vec3b(25,0,51);
  this->segColor[ColorStrange] = cv::Vec3b(0,0,0);

  cv::FileStorage fs(POSITION_PROCESSING_FILE,cv::FileStorage::READ);

  if(!fs.isOpened())
  {
    spdlog::get("Vision")->error("Position Processing Xml: Error diretorio, {}", POSITION_PROCESSING_FILE);
    return;
  }
  cv::FileNode node = fs[DEFAULT];
  this->setUp(MINSIZE,node[MINSIZE]);
  this->setUp(MAXSIZE,node[MAXSIZE]);
  this->setUp(MINSIZEBALL,node[MINSIZEBALL]);
  this->setUp(MAXSIZEBALL,node[MAXSIZEBALL]);
  this->setUp(BLOBMAXDIST,node[BLOBMAXDIST]);
  this->setUp(MYTEAM,node[MYTEAM]);
  this->setUp(ENEMYTEAM,node[ENEMYTEAM]);
  this->setUp(ENEMYSEARCH,node[ENEMYSEARCH]);
  this->setUp(SHOWELEMENT,node[SHOWELEMENT]);
  fs.release();
}

int PositionProcessing::getTeamColor()
{
  return this->_teamColor;
}

void PositionProcessing::setTeamColor(int teamColor)
{
  this->_teamColor = teamColor;
}

int PositionProcessing::blobMaxDist() {
  return _blobMaxDist;
}

int PositionProcessing::newId(int oldId){
  int id = 255;

  auto it = std::find(idGenerated.begin(), idGenerated.end(), oldId);
  
  if (it != idGenerated.end()){
    id = std::distance(idGenerated.begin(), it);
  } else {
    it = std::find(idGenerated.begin(), idGenerated.end(), oldId-1);
    if(it != idGenerated.end()){
      id = std::distance(idGenerated.begin(), it);
    }
  } 
  return id;
}


