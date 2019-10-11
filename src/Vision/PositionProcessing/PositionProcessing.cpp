#include "PositionProcessing.h"


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

void PositionProcessing::matchBlobs(std::vector<Entity>& entities, cv::Mat& debugFrame){

  FieldRegions groupedBlobs = pairBlobs();
  static Players empty_players;

  vss.setPlayers(empty_players);
  // printf("Team Color %d\n", getTeamColor());

  // Settting team positions
  Players teamA = findTeam(entities, debugFrame, groupedBlobs.team);
  setTeamColor(getTeamColor() == Color::YELLOW ? Color::BLUE : Color::YELLOW);
  Players teamB = findEnemys(entities, debugFrame, groupedBlobs.enemys);
  setTeamColor(getTeamColor() == Color::YELLOW ? Color::BLUE : Color::YELLOW);

  Players allPlayers;
  allPlayers.insert(allPlayers.end(),teamA.begin(),teamA.end());
  allPlayers.insert(allPlayers.end(),teamB.begin(),teamB.end());
  sort(allPlayers.begin(),allPlayers.end());

  Entity ball = findBall(entities, debugFrame);

  vss.setPlayers(allPlayers);
  vss.setBall(ball);
}

Players PositionProcessing::findTeam(std::vector<Entity> &entities, cv::Mat& debugFrame, std::vector<Region> &teamRegions) {

    Entities players;

    std::bitset<MAX_PLAYERS> markedColors;
    int teamCounter = 0;
    uint teamColor = static_cast<uint>(getTeamColor());

    for (Region &region : teamRegions) {
      if (region.distance < blobMaxDist()) {
        //int colorIndex = Utils::convertOldColorToNewColor(region.color);
        int colorIndex = region.color;
        if (!Utils::isRobotColor(colorIndex)) {
          // cor invalida
          continue;
        }

        if (markedColors[size_t(colorIndex)]){
          continue;
        }

        markedColors[size_t(colorIndex)] = true;
        Blob b1, b2;
        std::tie(b1, b2) = region.blobs;
        Player robot((teamColor-1)*100 + colorIndex - Color::RED);
        robot.team(teamColor);
        Point lastPosition = robot.position();
        Point newPositionInPixels = (b1.position + b2.position) * 0.5;
        Point newPosition = Utils::convertPositionPixelToCm(newPositionInPixels);

        // Debug
        cv::circle(debugFrame, newPositionInPixels, 15, _colorCar[colorIndex], 1, CV_AA);
        //cv::circle(debugFrame,Utils::convertPositionCmToPixel(Point(170/2,130/2)),10,cv::Scalar(0,255,0));
        // Para evitar ruido, se o robo se movimentar muito pouco,
        // ele permanece no mesmo local

//        if (std::abs(newPosition.x - lastPosition.x) < Global::minPositionDifference() &&
//            std::abs(newPosition.y - lastPosition.y) < Global::minPositionDifference()) {
//          newPosition = lastPosition;
//        }

        Float newTime = vss.time().getMilliseconds();
        Float newAngle = Utils::angle(b1.position, b2.position);
        robot.update(newPosition, newAngle);
        players.push_back(robot);
      }
    }
    return players;
}

Players PositionProcessing::findEnemys(std::vector<Entity> &entities, cv::Mat& debugFrame, std::vector<Region> &enemyRegions) {

    Entities players;

    std::bitset<MAX_PLAYERS> markedColors;
    uint teamColor = this->_teamId == Color::YELLOW ? Color::BLUE : Color::YELLOW;


    for (Region &region : enemyRegions) {
      if (region.distance < blobMaxDist()) {
        int colorIndex = region.color;
        Blob b1, b2;
        std::tie(b1, b2) = region.blobs;
        Player robot((teamColor-1)*100 + colorIndex - Color::RED);
        robot.team(teamColor);
        Point lastPosition = robot.position();
        Point newPositionInPixels = b2.position ;
        Point newPosition = Utils::convertPositionPixelToCm(newPositionInPixels);

        // Debug
        cv::circle(debugFrame, newPositionInPixels, 15, _colorCar[colorIndex], 1, CV_AA);
        //cv::circle(debugFrame,Utils::convertPositionCmToPixel(Point(170/2,130/2)),10,cv::Scalar(0,255,0));
        // Para evitar ruido, se o robo se movimentar muito pouco,
        // ele permanece no mesmo local

        if (std::abs(newPosition.x - lastPosition.x) < Global::minPositionDifference() &&
            std::abs(newPosition.y - lastPosition.y) < Global::minPositionDifference()) {
          newPosition = lastPosition;
        }

        Float newTime = vss.time().getMilliseconds();
        Float newAngle = Utils::angle(b2.position, b2.position);
        robot.update(newPosition, newAngle);
        players.push_back(robot);
      }
    }
    return players;
}

void PositionProcessing::findEnemysWithPrimary(std::vector<Entity> &entities, cv::Mat& debugFrame) {
  int enemyIndex=3;
  cv::Point currentPos, lastPos;
  /*
  for(int i = 0 ; i < 3 ; i++)
  {
    if(blob[this->_enemyTeam][i].valid)
    {
      lastPos.x = entities[enemyIndex].getPositionPixel().x;
      lastPos.y = entities[enemyIndex].getPositionPixel().y;

      currentPos.x = (blob[this->_enemyTeam][i].position.x);
      currentPos.y = (blob[this->_enemyTeam][i].position.y);

      if(abs(lastPos.x-currentPos.x) < 2 && abs(lastPos.y-currentPos.y) < 2)
       {
         currentPos.x = lastPos.x;
         currentPos.y = lastPos.y;
       }

      cv::circle(debugFrame, currentPos,15,this->_colorCar[this->_enemyTeam],1, CV_AA);

      entities[enemyIndex].setPosition(currentPos.x,currentPos.y);
      entities[enemyIndex].setUpdated(true);
      entities[enemyIndex].setColor(this->_enemyTeam);
      enemyIndex++;
    }
  }
  */
}

Entity PositionProcessing::findBall(std::vector<Entity> &entities, cv::Mat& debugFrame) {
    Entity ball;
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
      return ball;
    }

    // Debug
    //cv::circle(vss.frame(), blobBall.position, 9, _colorCar[OrangeCOL], 1, CV_AA);
    {
        //cv::Mat tmp(EMPTY_MATRIX);
        //std::cout << stringizer(blobBall.position) << " " << blobBall.position << std::endl;
        //std::cout << stringizer(convert_twice    ) << " " << Utils::convertPositionCmToPixel(Utils::convertPositionPixelToCm(blobBall.position)) << std::endl;
        //cv::circle(tmp, blobBall.position, 9, cv::Scalar(0,165,255), 1, CV_AA);
        //vss.mergeFrame(tmp);
    }

    Point newPosition = Utils::convertPositionPixelToCm(blobBall.position);
    Point lastPosition = vss.ball().position();

    if (std::abs(newPosition.x - lastPosition.x) < Global::minPositionDifference() &&
        std::abs(newPosition.y - lastPosition.y) < Global::minPositionDifference()) {
      newPosition = lastPosition;
    }

    Float newTime = vss.time().getMilliseconds();
    ball.update(newPosition);
    ball.id(0);

  return ball;

//  Blob ball;
//  ball.valid = false;
//  int maxArea = -1;

//  //get orange blob with larger area
//  for (int i=0; i < CLUSTERSPERCOLOR; i++) {
//    if (blob[OrangeCOL][i].area > maxArea && blob[OrangeCOL][i].valid) {
//      maxArea = blob[OrangeCOL][i].area;
//      ball = blob[OrangeCOL][i];
//      ball.valid = true;
//    }
//  }

//  if (!ball.valid) {
//     //entities[BALL_INDEX].setUpdated(false);
//     return;
//  }

//  cv::Point currentPos = ball.position, lastPos;
//  //lastPos.x = entities[BALL_INDEX].position().x;
//  //lastPos.y = entities[BALL_INDEX].position().y;

//  //with pos does not change so much, dont change position ( prevent position noise )
//  if(abs(lastPos.x-currentPos.x) < 2 && abs(lastPos.y-currentPos.y) < 2) {
//     currentPos.x = lastPos.x;
//     currentPos.y = lastPos.y;
//  }

//  double realX=0, realY=0;
//  /*
//  double convertWidth = entities[BALL_INDEX].getConvert().x;
//  double convertHeigth = entities[BALL_INDEX].getConvert().y;

//  // verifying if position is inside field
//  if(entities[BALL_INDEX].getConvertSet()) {

//    realX = currentPos.x * convertWidth;
//    realY = 130 - currentPos.y* convertHeigth;

//    if(!Utils::between(realX,MIN_X_LIMIT,RANGE_X) && !Utils::between(realY,MIN_GOAL_Y,RANGE_Y)) {

//      if(realX < MIN_X_LIMIT)
//        currentPos.x = MIN_X_LIMIT/entities[BALL_INDEX].getConvert().x;
//      else
//        currentPos.x = (MIN_X_LIMIT + RANGE_X)/entities[BALL_INDEX].getConvert().x;
//    }
//  }
//  */

//  //draw bal in frame
//  cv::circle(debugFrame, currentPos, 9, this->_colorCar[OrangeCOL], 1, CV_AA);


//  //entities[BALL_INDEX] = Entity(0);
//  //entities[BALL_INDEX].update(cv::Point2f(currentPos.x, currentPos.y),0);

}

std::pair<PositionProcessing::Blob, PositionProcessing::NearestBlobInfo> PositionProcessing::getNearestPrimary(Blob current) {
  int dMin = INT_MAX, distance, team;
  Blob choosen;
  NearestBlobInfo result;

  for(int teamColor = Color::BLUE ; teamColor <= Color::YELLOW ; teamColor++) {
    for(int i = 0 ; i < CLUSTERSPERCOLOR ;i++) {
      if(blob[teamColor][i].valid) {
        distance = Utils::sumOfSquares(current.position,blob[teamColor][i].position);

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

  return std::make_pair(choosen,result);

}

PositionProcessing::FieldRegions PositionProcessing::pairBlobs() {
  FieldRegions result;
  std::pair<Blob, NearestBlobInfo> primary;
  Region current;

  for(int idColor = Color::RED ; idColor < Color::BROWN+1; idColor++) {
    for(int i = 0 ; i < CLUSTERSPERCOLOR ; i++) {
      if(blob[idColor][i].valid) {
        primary = this->getNearestPrimary(blob[idColor][i]);

        current.blobs = std::make_pair(blob[idColor][i], primary.first);
        current.team = primary.second.teamIndex;
        current.color = idColor;
        current.distance = primary.second.distance;
        if (current.team == this->_teamId) result.team.push_back(current);
        //else result.enemys.push_back(current);
      } else break;
    }
  }

  if(result.enemys.empty() || result.enemys.size() < 3)
  {
      int idColor = this->_teamId == Color::YELLOW ? Color::BLUE : Color::YELLOW;
      for(int i = 0 ; i < CLUSTERSPERCOLOR ; i++) {
        if(blob[idColor][i].valid) {

          current.blobs = std::make_pair(blob[idColor][i], blob[idColor][i]);
          current.team = idColor;
          current.color = idColor;
          current.distance = 0.0;
          std::cout << current.team << std::endl;
          result.enemys.push_back(current);
      }
      }
  }
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
