/**\mainpage PositionProcessing class made by the RoboCIn for the project IEEE - VSS
 * @author RoboCIn
 *
 * This class is a interface for both, tracking and detection algorithm
 *
 */
#ifndef POSITIONPROCESSING
#define POSITIONPROCESSING

#include <iostream>
#include <cmath>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "Utils/Utils.h"
#include <map>
#include <string>
#include "Entity/Entity.h"
#include <QReadWriteLock>
#include "runlengthencoding.h"
#include "GameInfo/GameInfo.h"
#include <Utils/kalmanfilter.h>

#define CLUSTERSPERCOLOR 8
#define MAX_ROBOTS 6
#define BALL_INDEX 6
#define MIN_ID 176

#define POSITION_PROCESSING_FILE  "Config/PositionProcessing.xml"
#define WHERE_ARE_THOSE_FILE  "Config/PositionProcessingWhereAre.xml"
#define KMEANS_FILE  "Config/PositionProcessingKMeans.xml"
#define DEFAULT "Default"
#define MINSIZE "minSize"
#define MAXSIZE "maxSize"
#define MINSIZEBALL "minSizeBall"
#define MAXSIZEBALL "maxSizeBall"
#define BLOBMAXDIST "blobMaxDist"
#define MYTEAM "myTeam"
#define ENEMYTEAM "enemyTeam"
#define ENEMYSEARCH "enemySearch"
#define SHOWELEMENT "showElement"

#define NUMCLUSTERS  "NUMCLUSTERS"
#define Nok    "Nok"
#define Orangek  "Orangek"
#define Bluek    "Bluek"
#define Yellowk  "Yellowk"
#define Redk     "Redk"
#define Greenk   "Greenk"
#define Pinkk    "Pinkk"
#define LightBluek "LightBluek"
#define Purplek  "Purplek"
#define Brownk   "Brownk"
#define ColorStrangek "ColorStrangek"
#define secondaryColor0  "SecondaryColor0"
#define secondaryColor1  "SecondaryColor1"
#define secondaryColor2  "SecondaryColor2"
#define secondaryColor3  "SecondaryColor3"
#define secondaryColor4  "SecondaryColor4"
#define secondaryColor5  "SecondaryColor5"
#define secondaryColor6  "SecondaryColor6"

#define GREEN_PINK  248
#define GREEN_CYAN  284
#define GREEN_RED   176
#define CYAN_PINK   260
#define CYAN_RED    188
#define PINK_RED    182

#define GREEN_PINK_ALT  218
#define GREEN_CYAN_ALT  224
#define GREEN_RED_ALT   206
#define CYAN_PINK_ALT   290
#define CYAN_RED_ALT    278
#define PINK_RED_ALT    242

#define DEFAULT_ROWS 660
#define DEFAULT_COLS 880

#define MIN_X_LIMIT 11
#define RANGE_X 146
#define MIN_GOAL_Y 45
#define RANGE_Y 40





/**
 * @brief    interface Class for tracking and detection.
 */
class PositionProcessing {
public:

  /**
   * @brief    Basic struct to a object to be detected
   */

  typedef struct Blob {
    int     id;
    cv::Point position;
    double  angle;
    bool    valid;
    int     area;
    int     color;
    Blob():angle(0),valid(false),area(0) {}
    // This is used to sort the blobs by its
    bool operator<(Blob &b) {
        return color < b.color;
    }
  } Blob;

  typedef std::vector<Blob> Blobs;

  typedef struct NearestBlobInfo{
    int teamIndex;
    double distance;
  } NearestBlobInfo;

  typedef struct Region {
    Blobs blobs;
    int team;
    double distance;

    bool operator<(Region &b) {
        if (blobs.size() == 0 || b.blobs.size() == 0) return false;
        return blobs[0].id < b.blobs[0].id;
    }
  } Region;

  typedef std::vector<Region> Regions;

  typedef struct FieldRegions {
    Regions team;
    Regions enemies;
  } FieldRegions;

  /**
   * @brief    Basic function to run the algoritmh
   *
   * @param[in]  matriz  src matriz, already segmented
   * @param[in]  rows    Number of rows
   * @param[in]  cols    Number of cols
   *
   * @return   Vector of positions
   */

  virtual void run(std::vector< std::vector< Run > > runs,
           int rows = DEFAULT_ROWS,
           int cols = DEFAULT_COLS) = 0;

  /**
   * @brief    Initialize the algorithm from file
   *
   */     
  virtual void init() = 0;

  /**
   * @brief    Get a frame that helps to debug a function
   *
   * @param[in]  frame  frame
   */
  virtual void getDebugFrame(cv::Mat& frame) = 0;

    /**
   * @brief    Save all the paramenters into a xml file
   */
  virtual void saveParam() = 0;
  /**
   * @brief    Change a variable
   *
   * @param[in]  var  The name of a variable
   * @param[in]  value  The new value
   *
   */
  void setUp(std::string var,int value);

  /**
   * @brief setColorIndex
   * @param color { RedCOL to ColorStrange }
   * @param index 0, 1, 2
   */
  int setColorIndex(int color, int index);

  /**
   * @brief    Destroys the object.
   */
  virtual ~PositionProcessing() = default;

  int getTeamColor();

  void setTeamColor(int teamColor);

protected:

  /**
   * @brief    Saves a xml file with all common param for this interface class.
   */
  void saveXML();

  /**
   * @brief    Identifies the ball, and updates its position in entity.
   *
   * @param    ball  The entity to be returned
   */
  void findBall(Entity &ball, cv::Mat &debugFrame);

  /**
   * @brief    Filter blobs to merge valid blos in new tag format.
   *
   * @param    regions The regions to filter the blobs into new regions
   */
  void filterTeam(Regions &regions);

  void filterPattern(Regions &regions);

   /**
  * @brief    Identifies from which team the blob belongs to.
  */
  FieldRegions pairBlobs();

   /**
  * @brief    combines a color patch identifier with the closer team patch.
  */
  std::pair<Blob, NearestBlobInfo> getNearestPrimary(Blob current);

   /**
  * @brief    Identifies all robots
  *
  * @param    debugFrame  The debugFrame to draw the blob's positions
  */
  void matchBlobs(cv::Mat &debugFrame);

   /**
  * @brief    Updates the teammates positions.
  *
  * @param    players  The players entities
  */
  void findTeam(Players &players, cv::Mat& debugFrame, std::vector<Region>& teamRegions);

  /**
   * @brief    Updates the enemys positions.
   *
   * @param    players  The players entities
   */
  void findEnemys(Players &players, cv::Mat& debugFrame, std::vector<Region> &enemyRegions);


  /**
   * @brief    Calculate a speed of an entity.
   *
   * @param[in]  entity  The entity
   *
   * @return   The speed.
   */
  double speedCalulate(Entity entities);

  /**
   * @brief    Gets the number of entities.
   *
   * @param[in]  matriz  The matriz, frame segmented
   *
   * @return   The number of entities.
   */
  int getNumberOfEntities(const unsigned char *matriz);

  /**
   * @brief getParam get a value by it's name
   * @param var the name of value
   * @return value
   */
  int getParam(std::string var);

  /**
   * @brief    Gets the number of entities with color.
   *
   * @param[in]  matriz  The matriz, frame segmented
   * @param[in]  color   Color of entity
   *
   * @return   The number of entities with color.
   */
  int getNumberOfEntitiesWithColor(const unsigned char *matriz,int color);

  /**
   * @brief    Initialize the blob with default values
   *
   * @param    blob  The object
   */
  void initBlob(Blob &blob);

  /**
   * @brief    Initialize the default param
   */
  void initDefault();

  // retorna a maxima distancia entre blobs para serem um robo
  int blobMaxDist();

  int newId(int oldId);

  std::vector<int> idGenerated = {GREEN_CYAN, GREEN_PINK, CYAN_PINK, CYAN_RED, GREEN_RED, PINK_RED};
  std::vector<int> idGeneratedAlt = {GREEN_CYAN_ALT, GREEN_PINK_ALT, CYAN_PINK_ALT, CYAN_RED_ALT, GREEN_RED_ALT, PINK_RED_ALT};

  std::mutex _frameLocker;
  std::map<std::string,int> param;
  cv::Scalar _colorCar[ColorStrange+1];
  cv::Vec3b segColor[ColorStrange+1];
  cv::Mat debugSrc;
  Blob blob[NUMBEROFCOLOR][CLUSTERSPERCOLOR];
  int colorPresent[CLUSTERSPERCOLOR];
  int _colorIndex[NUMBEROFCOLOR];
  enum enemy{Nothing,Primary,Secundary,Both};
  int _teamColor;
  int _minSize, _maxSize, _minSizeBall, _maxSizeBall, _blobMaxDist, _teamId, _enemyTeam , _enemySearch, _showElement;
  KalmanFilter _kalmanFilterRobots[2][MAX_ROBOTS];
  KalmanFilter _dirFilteRobots[2][MAX_ROBOTS];
  KalmanFilter _kalmanFilterBall[1][1];
  KalmanFilter _dirFilterBall[1][1];
  Point _ballLastPosition;
  Float _ballLastTime;
  static const bool USE_PATTERN_FOR_ENEMIES = true;
  static const bool USE_OLD_PATTERN = false;

};

#endif
