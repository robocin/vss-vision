#ifndef COACHUTILS_H
#define COACHUTILS_H

#include <Entity/Entity.h>
#include <Utils/EnumsAndConstants.h>

namespace CoachUtils {

  int robotCountInDefensiveField(std::vector<Entity>& entities);
  bool isRobotNearToBall(std::vector<Entity>& entities, int robotIndex);
  fieldWall isNearToWall(cv::Point2d position);
  bool canCarryBall(std::vector<Entity>& entities, int robotIndex, bool wasCarryingBall);
  bool insideOurArea(cv::Point2d pos, double sumX, double sumY);
  cv::Point2d predictEntity(cv::Point2d position, cv::Point2d velocity, double limiter);
  bool gkShouldWaitArea(std::vector<Entity>& entities, Job job);
  /*
   * Verifies if there's 2 or more players and the ball inside our area
   * @param entities vector to get positions
   * @param job object that holds index of each players role
   * @return true if there's a penaulty condition
  */
  //bool gkShouldLeaveArea(std::vector<Entity>& entities, Job job);

  bool freeArea(std::vector<Entity>& entities, Job job);

  /*
   * Function to check if a given object is inside our area of goal
   * @param position of the object to check
   * @return bool , true if object in our area, false otherwise
   */
  bool insideOurArea(cv::Point2d pos, double sumX = 0, double sumY = 0);
  /*
   * Checks if goalkeeper is within a close range of the goal area
   * @param position of goal keeper
   * @return bool
   */

  bool gkCloseToArea(cv::Point2d pos);

  void debugObjective(cv::Mat cameraFrame, std::vector<Entity>& entities, int job);
}

#endif // COACHUTILS_H
