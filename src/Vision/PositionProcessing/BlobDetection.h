/**\mainpage WhereAreThose class made by the RoboCIn for the project IEEE - VSS
 * @author RoboCIn
 *
 * This class is a detection algorithm
 *
 */
#ifndef WHEREARETHOSE_H
#define WHEREARETHOSE_H

#include "PositionProcessing.h"
#include "Entity/Entity.h"

/**
 * @brief    Class for detection algorithm based on brutal force DFS.
 */
class BlobDetection : public PositionProcessing {
 public:
  BlobDetection();

  /**
   * @brief    Basic function to run the algoritmh
   *
   * @param[in]  matrix  src matrix, already segmented
   * @param[in]  rows    Number of rows
   * @param[in]  cols    Number of cols
   *
   * @return   Vector of positions
   */

  void run(std::vector<std::vector<Run>> runs, int rows = DEFAULT_ROWS, int cols = DEFAULT_COLS);

  /**
   * @brief    Initialize the algorithm
   *
   */
  void init();

  /**
   * @brief    Get a frame that helps to debug a function
   *
   * @param[in]  frame  frame
   */
  void getDebugFrame(cv::Mat& frame);

  /**
   * @brief    Save all param used in this class.
   */
  void saveParam();

 private:
  /**
   * @brief    Calculate the centroid for every color, using the _runLengthEncoding
   *
   * @param[in]  debugFrame   will have circles in each centroid, to help debugging
   */
  void findBlobs(cv::Mat& debugFrame);

  /**
   * @brief    match a centroid of the team color with other centroid to
   * 			   find the true position of a robot
   *
   * @param    entities  The entities
   */
  void whereAreThoseRobots(Entity entities[]);

  cv::Mat _visit;
  int _clusterCount[CLUSTERSPERCOLOR];

  std::vector<std::vector<Run>> _runs;
};

#endif
