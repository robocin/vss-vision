#include "CoachUtils.h"

int CoachUtils::robotCountInDefensiveField(std::vector<Entity>& entities) {
  int count = 0;

  for (int i = ROBOT1; i <= ROBOT3; i++) {
    if (entities[i].getPositionMatrix().x < Field::middle().x)
      count++;
  }

  return count;
}

bool CoachUtils::isRobotNearToBall(std::vector<Entity>& entities, int robotIndex) {
  cv::Point2d robotPosition = entities[robotIndex].getPositionCartesian();
  cv::Point2d ballPosition = entities[BALL].getPositionCartesian();

  return Geometry::distance(robotPosition, ballPosition) <= 6.5;
}

fieldWall CoachUtils::isNearToWall(cv::Point2d position) {
  fieldWall res = NONE_WALL;

  // if is inside goal section
  if (position.y >= Field::goalMin().y + (Global::halfAxis() * 4) &&
      position.y <= Field::goalMax().y - (Global::halfAxis() * 4)) {

    // if is near to inside right or left goal wall
    if (position.x <=
        Field::min().x + (Global::halfAxis() * 4) /*Constants::fieldLimits.ourGoalXMin*/)
      res = LEFT_WALL;
    if (position.x >=
        /*Constants::fieldLimits.enemyGoalXMax*/ Field::goalMin().x + (Global::halfAxis() * 4))
      res = RIGHT_WALL;

  } else {
    // if is near to right wall or left wall
    if (position.x <= Field::min().x + (Global::halfAxis() * 4) /*Constants::fieldLimits.xMin*/)
      res = LEFT_WALL;
    if (position.x >= Field::max().x - (Global::halfAxis() * 4) /*Constants::fieldLimits.xMax*/)
      res = RIGHT_WALL;
  }

  // if is near to bottom wall
  if (position.y <= Field::min().y + (Global::halfAxis() * 4) /*Constants::fieldLimits.yMin*/ &&
      res != RIGHT_WALL)
    res = BOTTOM_WALL;

  // if is near to upper wall
  if (position.y >= Field::max().y - (Global::halfAxis() * 4) /*Constants::fieldLimits.yMax*/ &&
      res != RIGHT_WALL)
    res = UP_WALL;

  return res;
}

bool CoachUtils::canCarryBall(std::vector<Entity>& entities, int robotIndex, bool wasCarryingBall) {
  cv::Point2d robot_position = entities[robotIndex].getPositionCartesian();
  cv::Point2d ballPosition = entities[BALL].getPositionCartesian();

  if (!(robot_position.x > ballPosition.x))
    return false;

  double robot_angle;
  cv::Point2d goal_center;
  double projectionInGoal;
  double ballAngle;
  double ballRobotAngleDifference;

  double robot_rotation = entities[robotIndex].getAngle();

  if (robot_rotation > M_PI / 2)
    robot_rotation = robot_rotation - M_PI;
  else if (robot_rotation < -M_PI / 2)
    robot_rotation = robot_rotation + M_PI;

  robot_angle = robot_rotation;
  goal_center = cv::Point2d(0.0, 65.0);

  projectionInGoal = tan(robot_rotation) * (robot_position.x) + (130.0 - robot_position.y);

  ballPosition = entities[BALL].getPositionCartesian();
  ballAngle = atan2(robot_position.y - ballPosition.y, robot_position.x - ballPosition.x);
  ballRobotAngleDifference = Utils::smallestAngleDiff(robot_angle, ballAngle);

  cv::Point2d goalPosition = entities[robotIndex].getObjective();
  double goalAngle = atan2(robot_position.y - goalPosition.y, robot_position.x - goalPosition.x);
  double goalBallDistance = Geometry::distance(goalPosition, ballPosition);
  double goalRobotDistance = Geometry::distance(goalPosition, robot_position);
  double goalRobotAngleDifference = Utils::smallestAngleDiff(robot_angle, goalAngle);

  double projectionThreshold = (robot_position.x / 170.0) * 25 + 15;

  double angleLimit = 30, goalRobotDistanceLimit = 5, goalBallDistanceLimit = 16;

  if (wasCarryingBall) {
    angleLimit *= 1.5;
    goalRobotDistanceLimit *= 1.5;
    goalBallDistanceLimit *= 1.5;
    projectionThreshold *= 1.5;
  }

  if ((fabs(Geometry::radiansToDegrees(goalRobotAngleDifference)) < angleLimit &&
       goalRobotDistance < goalRobotDistanceLimit && goalBallDistance < goalBallDistanceLimit) ||
      (fabs(Geometry::radiansToDegrees(ballRobotAngleDifference)) < 30 &&
       fabs(projectionInGoal - 65.0) <= projectionThreshold &&
       Geometry::distance(robot_position, ballPosition) < 20.0)) {
    return true;
  } else {
    return false;
  }
}

bool CoachUtils::insideOurArea(cv::Point2d pos, double sumX, double sumY) {
  return (pos.x > 145 - sumX) && (pos.y > 30 - sumY) && (pos.y < 100 + sumY);
}

/*bool CoachUtils::gkShouldLeaveArea(std::vector<Entity>& entities, Job job) {
  return (insideOurArea(entities[job.goalkeeper.index].getPositionCartesian()) &&
      (insideOurArea(entities[job.forward.index].getPositionCartesian()) ||
insideOurArea(entities[job.defender.index].getPositionCartesian()))&&
      insideOurArea(entities[BALL].getPositionCartesian()));
}*/

cv::Point2d CoachUtils::predictEntity(cv::Point2d position, cv::Point2d velocity, double limiter) {
  double maxDistance = 50.0;

  if (limiter > maxDistance) {
    position.x += velocity.x;
    position.y += velocity.y;
  } else {
    position.x += velocity.x * (limiter / maxDistance);
    position.y += velocity.y * (limiter / maxDistance);
  }

  if (position.x < 0)
    position.x += 2 * (0 - position.x);
  else if (position.x > 170)
    position.x += 2 * (170 - position.x);
  else if (position.y > 95.0 || position.y < 45.0) {

    if (position.x < 10)
      position.x += 2 * (10 - position.x);
    else if (position.x > 160)
      position.x += 2 * (160 - position.x);
  }

  if (position.y < 0)
    position.y += 2 * (0 - position.y);
  else if (position.y > 130)
    position.y += 2 * (130 - position.y);
  else if (position.x < 10 || position.x > 160) {
    if (position.y < 45.0)
      position.y += 2.0 * (45.0 - position.x);
    if (position.y > 95.0)
      position.y += 2.0 * (95.0 - position.x);
  }

  return position;
}

bool CoachUtils::gkShouldWaitArea(std::vector<Entity>& entities, Job job) {
  return !freeArea(entities, job) &&
         gkCloseToArea(entities[job.goalkeeper.index].getPositionCartesian());
}

bool CoachUtils::gkCloseToArea(cv::Point2d pos) {
  return ((pos.x < 145) && (pos.x > 125) && // In front of area
          (pos.y > 30) && (pos.y < 100)) ||
         ((pos.x > 135) && (((pos.y > 20) && (pos.y < 30)) ||   // One side of area
                            ((pos.y > 100) && (pos.y < 110)))); // Other side of area
}

bool CoachUtils::freeArea(std::vector<Entity>& entities, Job job) {
  return !insideOurArea(entities[job.forward.index].getPositionCartesian()) ||
         !insideOurArea(entities[BALL].getPositionCartesian());
}

void CoachUtils::debugObjective(cv::Mat cameraFrame, std::vector<Entity>& entities, int job) {
  cv::Point2d robot_objective = entities[job].getObjective();
  cv::Point2d ball_estimative = entities[job].getEstimateBall();

  cv::circle(cameraFrame,
             Utils::convertPositionCmToPixel(ball_estimative),
             4,
             cv::Scalar(255, 255, 51),
             8);
  cv::circle(cameraFrame,
             Utils::convertPositionCmToPixel(robot_objective),
             4,
             cv::Scalar(229, 149, 190),
             8);
}
