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
  // vai sumir
  for (unsigned int i = 0; i < entities.size(); i++) {
    //entities[i].setUpdated(false);
  }
  // ajustar
  FieldRegions groupedBlobs = pairBlobs();

  // Settting team positions
  // ainda falta!
  findTeam(entities, debugFrame, groupedBlobs.team);

  // Falta criar essa parte ainda!
  if (this->_enemySearch != Nothing) findEnemys(entities,debugFrame,groupedBlobs.enemys);
  else findEnemysWithPrimary(entities, debugFrame);

  // feito!
  findBall(entities, debugFrame);
  //std::cout << std::endl;
  //printf("BallPosition (%+4.2lf, %+4.2lf)", vss.ball().speed().x, vss.ball().speed().y);
  //std::cout << std::endl;
  /*std::cout << "accumulateTime      = " << vss.ball().accumulateTime() << std::endl;
  std::cout << "accumulatePosition  = " << vss.ball().accumulatePosition() << std::endl;
  std::cout << "accumulateSpeed     = " << vss.ball().accumulateSpeed() << std::endl;
  std::cout << "BallPosition        = " << vss.ball().position() << std::endl;
  std::cout << "BallSpeed           = " << vss.ball().speed() << std::endl;
  std::cout << "BallAcceleration    = " << vss.ball().acceleration() << std::endl;*/
}

void PositionProcessing::findTeam(std::vector<Entity> &entities, cv::Mat& debugFrame, std::vector<Region> &teamRegions) {
  // depois substituir por essa funcao
  /*std::function<void(GameInfo &, Vector<Region> &)> FindAllies = [&](GameInfo &vss, Vector<Region> &teamRegions) -> void {
    // desativar todos os jogadores para identificar
    // somente os ativos no frame atual
    AlliesTable &alliesTable = vss.alliesTable();

    // Os jogadores ativos serao salvos em uma tabela
    // de referencias
    References<Ally> &allies = vss.allies();
    allies.clear();
    for (Ally &ally : alliesTable) {
      ally.setActive(false);
    }
    for (Region &region : teamRegions) {
      if (region.distance < blobMaxDist()) {
        int colorIndex = Utils::convertOldColorToNewColor(region.color);
        if (!Utils::isRobotColor(colorIndex)) {
          // cor invalida
          continue;
        }
        Blob b1, b2;
        std::tie(b1, b2) = region.blobs;
        Player &robot = alliesTable[static_cast<size_t>(colorIndex)];
        Point lastPosition = robot.position();
        Point newPositionInPixels = (b1.position + b2.position) / 2.0;
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
        Float newAngle = Utils::angle(b1.position, b2.position);
        robot.update(newTime, newPosition, newAngle);
        robot.setIndex(colorIndex);
        robot.setActive(true);
        allies.push_back(robot);
      }
    }
  };

  FindAllies(vss, teamRegions);
*/

}

void PositionProcessing::findEnemys(std::vector<Entity> &entities, cv::Mat& debugFrame, std::vector<Region> &enemyRegions) {
  int enemyIndex = 3;
  cv::Point currentPos, lastPos;
  int mappedId, idColor;
  Blob b1, b2;
/*
  for (unsigned int i=0; i < enemyRegions.size(); i++) {

    mappedId = this->_colorIndex[enemyRegions[i].color];

    if (enemyRegions[i].distance <= this->_blobMaxDist && enemyIndex < 6) {
      lastPos.x = entities[mappedId].getPositionPixel().x;
      lastPos.y = entities[mappedId].getPositionPixel().y;

      b1 = enemyRegions[i].blobs.first;
      b2 = enemyRegions[i].blobs.second;

      idColor = enemyRegions[i].color;

      switch (this->_enemySearch) {
        case Both:
          currentPos.x = (b1.position.x + b2.position.x)/2;
          currentPos.y = (b1.position.y + b2.position.y)/2;
          break;
        case Primary:
          currentPos.x = b1.position.x;
          currentPos.y = b1.position.y;
          break;
        case Secundary:
          currentPos.x = b2.position.x;
          currentPos.y = b2.position.y;
          break;
        default:
          break;
      }

      if(abs(lastPos.x-currentPos.x) < 2 && abs(lastPos.y-currentPos.y) < 2) {
         currentPos.x = lastPos.x;
         currentPos.y = lastPos.y;
      }

      double xw, yh, wConvert, hConvert;
      wConvert = entities[enemyIndex].getConvert().x;
      hConvert = entities[enemyIndex].getConvert().y;

      if(entities[enemyIndex].getConvertSet()) {

        xw = currentPos.x * wConvert;
        yh = 130 - currentPos.y* hConvert;

        if(!Utils::between(xw,MIN_X_LIMIT,RANGE_X) && !Utils::between(yh,MIN_GOAL_Y,RANGE_Y)) {
          if(xw < MIN_X_LIMIT)
            currentPos.x = MIN_X_LIMIT/entities[enemyIndex].getConvert().x;
          else
            currentPos.x = (MIN_X_LIMIT + RANGE_X)/entities[enemyIndex].getConvert().x;
        }

        cv::circle(debugFrame, currentPos,15,this->_colorCar[enemyRegions[i].team],1, CV_AA);

      }

      entities[enemyIndex].setPosition(currentPos.x,currentPos.y);
      entities[enemyIndex].setAngle(Utils::angle(b1.position,b2.position));
      entities[enemyIndex].setUpdated(true);
      entities[enemyIndex].setColor(idColor);
      enemyIndex++;
    }
  }*/
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

void PositionProcessing::findBall(std::vector<Entity> &entities, cv::Mat& debugFrame) {
  // AJUSTAR
  std::function<void(GameInfo &)> newFindBall = [&](GameInfo &vss) {
    Entity &ball = vss.ball();
    // Desativar, so ativar quando encontrar
    // a bola no frame atual
    ball.setActive(false);
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
      return;
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
    vss.ball().update(newTime, newPosition);
    vss.ball().setActive(true);
  };
  newFindBall(vss);

  Blob ball;
  ball.valid = false;
  int maxArea = -1;

  //get orange blob with larger area
  for (int i=0; i < CLUSTERSPERCOLOR; i++) {
    if (blob[OrangeCOL][i].area > maxArea && blob[OrangeCOL][i].valid) {
      maxArea = blob[OrangeCOL][i].area;
      ball = blob[OrangeCOL][i];
    }
  }

  if (!ball.valid) {
     //entities[BALL_INDEX].setUpdated(false);
     return;
  }

  cv::Point currentPos = ball.position, lastPos;
  //lastPos.x = entities[BALL_INDEX].getPositionPixel().x;
  //lastPos.y = entities[BALL_INDEX].getPositionPixel().y;

  //with pos does not change so much, dont change position ( prevent position noise )
  if(abs(lastPos.x-currentPos.x) < 2 && abs(lastPos.y-currentPos.y) < 2) {
     currentPos.x = lastPos.x;
     currentPos.y = lastPos.y;
  }

  double realX=0, realY=0;
  /*
  double convertWidth = entities[BALL_INDEX].getConvert().x;
  double convertHeigth = entities[BALL_INDEX].getConvert().y;

  // verifying if position is inside field
  if(entities[BALL_INDEX].getConvertSet()) {

    realX = currentPos.x * convertWidth;
    realY = 130 - currentPos.y* convertHeigth;

    if(!Utils::between(realX,MIN_X_LIMIT,RANGE_X) && !Utils::between(realY,MIN_GOAL_Y,RANGE_Y)) {

      if(realX < MIN_X_LIMIT)
        currentPos.x = MIN_X_LIMIT/entities[BALL_INDEX].getConvert().x;
      else
        currentPos.x = (MIN_X_LIMIT + RANGE_X)/entities[BALL_INDEX].getConvert().x;
    }
  }
  */

  //draw bal in frame
  cv::circle(debugFrame, currentPos, 9, this->_colorCar[OrangeCOL], 1, CV_AA);

  /*
  entities[BALL_INDEX].setPosition(currentPos.x, currentPos.y);
  entities[BALL_INDEX].setAngle(0);
  entities[BALL_INDEX].setUpdated(true);
  entities[BALL_INDEX].setColor(OrangeCOL);
  */
}

std::pair<PositionProcessing::Blob, PositionProcessing::NearestBlobInfo> PositionProcessing::getNearestPrimary(Blob current) {
  int dMin = INT_MAX, distance, team;

  Blob choosen;
  NearestBlobInfo result;

  for(int teamColor = BlueCOL ; teamColor <= YellowCOL ; teamColor++) {
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

  for(int idColor = RedCOL ; idColor < ColorStrange ; idColor++) {
    for(int i = 0 ; i < CLUSTERSPERCOLOR ; i++) {
      if(blob[idColor][i].valid) {
        primary = this->getNearestPrimary(blob[idColor][i]);

        current.blobs = std::make_pair(blob[idColor][i], primary.first);
        current.team = primary.second.teamIndex;
        current.color = idColor;
        current.distance = primary.second.distance;

        if (current.team == this->_teamId) result.team.push_back(current);
        else result.enemys.push_back(current);
      } else break;
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
