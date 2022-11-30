/**
 * Mainpage Utils class made by the RoboCIn for the project IEEE - VSS
 * @author Carlos Henrique / Cristiano Oliveira
 *
 * This class have a group of mathematical methods to the general interest of the Vision and
 * Strategy use.
 *
 */

#ifndef UTILS_H
#define UTILS_H

// Open CV
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

// TALVEZ APAGAR!
#include "Logging/logging.h"

// C++ Libs
#include <bits/stdc++.h>

// Definicoes utilizadas no programa
#include "Defines.h"

// Enumerações e constantes utlizadas no codigo
#include "EnumsAndConstants.h"

// Variaveis globais, e modificaveis
#include "Global.h"

// Timer
#include "Timer/Timer.h"

// Types
#include "Types.h"

// Constantes do Campo, que podem ser alteradas de acordo com a quantidade de jogadores
#include "Field/Field.h"

#include "Draw.h"

#include "Geometry.h"

// A ideia eh manter todos os arquivos de include aqui, na utils. Porem, isso gera cross reference.
// Verificar como ajustar depois.
//#include "GameInfo.h"

// INCLUIR OS BEHAVIORS TODOS AQUI NA UTILS
//#include "Behavior/AttackerIronCup2019.h"

/*
 * Structure with the indices of each job
 * VAI SUMIR!!
 */
typedef struct Job {
  struct player_t {
    int index;
  };
  player_t goalkeeper;
  player_t forward;
  player_t defender;
} Job;

// Falta separar a Utils em: Math, Geometry, ..., cvUtils, e realmente Utils

namespace Utils {
  /*
   * Receve an angle and return the same, but converted to positive scale
   * @param angle Angle
   * @return Positive scale of the input angle. Range is [0, 360] degrees
   */
  double to_positive_angle(double angle);
  /*
   * Return a lower diference between two angles and put in a range of [-PI..PI]
   * @param target First angle
   * @param source Second angle
   * @return The lower diference between the two angles
   */
  double smallestAngleDiff(double target, double source);
  /*
   * The input radian angle is put in a range of [-M_PI, M_PI]
   * @param angle Input angle
   * @return Angle in a range of [-PI, PI]
   */
  double to180range(double angle);
  /*
   * Square of the diference,
   * @param x First number (double)
   * @param y Second number (double)
   * @return ((x*x)-(y*y))
   */
  double double_dif(double x, double y);

  /**
   * Reflects the projection of the ball when near the walls or just leaves the projection on the
   * wall.
   * @param ball_estimate actual position of projection of the ball
   * @param reflected bool to define if the projection of the ball is reflected(true) or leaves on
   * the wall(false)
   */
  cv::Point reflect(cv::Point ball_estimate, bool reflected);

  /**
   * Estimate ball position given the distance between the ball and the robot
   * @param pos_robot robot position
   * @param pos_ball ball position
   * @param ball_speed ball speed
   */
  cv::Point estimateBallPos(cv::Point pos_robot,
                            cv::Point pos_ball,
                            cv::Point ball_speed,
                            double rob_speed = 100);

  /**
   * @brief    Sum of Squares, deltaX^2 + deltaY^2
   *
   * @param[in]  alfa  coordinates of first point (pixel).
   * @param[in]  beta  coordinates of second point (pixel).
   *
   * @return   Sum of squares between the two points
   */
  double sumOfSquares(cv::Point alfa, cv::Point beta);

  /**
   * @brief    Return the ajusted angle
   *
   * @param[in]  alfa  coordinates of first point (pixel).
   * @param[in]  beta  coordinates of second point (pixel).
   *
   * @return   double, Ajusted atan2
   */
  double angle(cv::Point alfa, cv::Point beta);

  double angleDouble(cv::Point2d alfa, cv::Point2d beta);

  /**
   * @brief    Median of a list
   *
   * @param[in]  list  List of Points
   *
   * @return   Median value
   */
  double median(std::vector<double> list);

  /**
   * Function used to compare the second element of two pairs <int, double>
   * @param firstElem first element to compare
   * @param secondElem second element to compare
   * @return true if the first is less than the second, false otherwise
   */
  bool pairCompareSecond(const std::pair<int, double>& firstElem,
                         const std::pair<int, double>& secondElem);

  /**
   * Calculate the parameters of one line, given two points
   * @param x1 X coordinate of the first point
   * @param y1 Y coordinate of the first point
   * @param x2 X coordinate of the second point
   * @param y2 Y coordinate of the second point
   * @return the parameter of the line
   */
  cv::Point2d getLineParameters(double x1, double y1, double x2, double y2);

  cv::Point2d getLineParameters(cv::Point2d p1, cv::Point2d p2);
  /**
   * Given parameters of one line and a X coordinate, calculate the Y coordinate in that line
   * @param param Parameters of the line
   * @param x X coordinate of the point
   * @return Y coordinate in that line
   */
  double yInLine(cv::Point2d param, double x);

  /**
   * Given parameters of one line and a Y coordinate, calculate the X coordinate in that line
   * @param param Parameters of the line
   * @param y Y coordinate of the point
   * @return X coordinate in that line
   */
  double xInLine(cv::Point2d param, double y);

  double localToGlobalX(double dx, double theta);

  double localToGlobalY(double dx, double theta);
  /**
   * The function calculates the line that makes the bisector between the straight lines from the
   * poles to the vertex
   * @param vertex_center Vertex coordinates
   * @param pole1 First pole coordinates
   * @param pole2 Second pole coordinates
   * @return Pair containing the parameters of the line (coefficient of angular, linear coefficient)
   */
  cv::Point2d bisectorLine(cv::Point2d vertex_center, cv::Point2d pole1, cv::Point2d pole2);

  /**
   * The function corrects points that are set outside the field
   * @param objective pair of coordinates containing the objective
   * @return pair of coordinates containing the goal inside of the field
   */
  cv::Point setInside(cv::Point objective);

  /**
   * Function that calculates the points of intersection between a line and a circumference /
   * ellipse
   * @param line Pair containing the parameters of the line
   * @param h X coordinate of the center of the curve
   * @param a semi-axis X
   * @param k Y coordinate of the center of the curve
   * @param b semi-axis Y
   * @return Pair of pairs containing the coordinates of the two points of intersection.
   */
  std::pair<cv::Point2d, cv::Point2d>
  intersectionArc(cv::Point2d line, double h, double a, double k, double b);

  /**
   * Function that calculates the complement of an angle.
   * @param input angle
   * @return inverse angle
   */
  double inverseAngle(double angle);
  /**
   * Function to convert position in cm's from strategy to position in pixels
   * @param Point - pair of int (position x and y in cm's)
   * @param Point convert - first: wConvert - Width , second: hConvert - Height
   * @return Point - pair of int (position in pixels)
   */
  Point convertPositionCmToPixel(const Point& position);

  Point convertPositionPixelToCm(const Point& position);

  bool between(double number, double min_limit, double range);
  double map(double x, double in_min, double in_max, double out_min, double out_max);
  double bound(double x, double low, double high);

  double linearEquationY(double x_in, cv::Point2d xCoord, cv::Point2d yCoord);

  double mod_vec(cv::Point2d vec);

  cv::Point2d desloc_vec(cv::Point2d v1, cv::Point2d v2);

  double scale_prod_vec(cv::Point2d v1, cv::Point2d v2);

  double angleBetweenTwoVectors(cv::Point2d v1, cv::Point2d v2);

  double reverseAngle(double angle);

  double sign(double value);

  double gaussian(double r, double delta);

  double crossProduct(cv::Point2d& alpha, cv::Point2d& beta);

  // Retorna se uma cor identifica um time
  bool isTeamColor(const int& t_color);

  // Retorna se uma cor eh identificacao de robo
  bool isRobotColor(const int& t_color);

  int convertOldColorToNewColor(int t_oldColor);

}; // namespace Utils

#endif /* UTILS_H */
