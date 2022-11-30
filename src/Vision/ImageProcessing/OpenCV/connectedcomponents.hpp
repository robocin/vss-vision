#include <opencv2/opencv.hpp>

#ifndef _H_CONNECTED_COMPONENTS_
  #define _H_CONNECTED_COMPONENTS_
  #if CV_MAJOR_VERSION == 2
//#define CV_EXPORTS_AS(x)
//#define CV_EXPORTS_W(x)

namespace cv {

  //! connected components algorithm output formats
  enum ConnectedComponentsTypes {
    CC_STAT_LEFT = 0,  //!< The leftmost (x) coordinate which is the inclusive start of the bounding
                       //!< box in the horizontal direction.
    CC_STAT_TOP = 1,   //!< The topmost (y) coordinate which is the inclusive start of the bounding
                       //!< box in the vertical direction.
    CC_STAT_WIDTH = 2, //!< The horizontal size of the bounding box
    CC_STAT_HEIGHT = 3, //!< The vertical size of the bounding box
    CC_STAT_AREA = 4,   //!< The total area (in pixels) of the connected component
    CC_STAT_MAX = 5
  };

  //! connected components algorithm
  enum ConnectedComponentsAlgorithmsTypes {
    CCL_WU = 0, //!< SAUF algorithm for 8-way connectivity, SAUF algorithm for 4-way connectivity
    CCL_DEFAULT =
        -1,       //!< BBDT algortihm for 8-way connectivity, SAUF algorithm for 4-way connectivity
    CCL_GRANA = 1 //!< BBDT algorithm for 8-way connectivity, SAUF algorithm for 4-way connectivity
  };

  /** @brief computes the connected components labeled image of boolean image

  image with 4 or 8 way connectivity - returns N, the total number of labels [0, N-1] where 0
  represents the background label. ltype specifies the output label image type, an important
  consideration based on the total number of labels or alternatively the total number of pixels in
  the source image. ccltype specifies the connected components labeling algorithm to use, currently
  Grana's (BBDT) and Wu's (SAUF) algorithms are supported, see the
  cv::ConnectedComponentsAlgorithmsTypes for details. Note that SAUF algorithm forces a row major
  ordering of labels while BBDT does not.

  @param image the 8-bit single-channel image to be labeled
  @param labels destination labeled image
  @param connectivity 8 or 4 for 8-way or 4-way connectivity respectively
  @param ltype output image label type. Currently CV_32S and CV_16U are supported.
  @param ccltype connected components algorithm type (see the
  cv::ConnectedComponentsAlgorithmsTypes).
  */
  int connectedComponents(InputArray image,
                          OutputArray labels,
                          int connectivity,
                          int ltype,
                          int ccltype);

  /** @brief computes the connected components labeled image of boolean image and also produces a
  statistics output for each label

  image with 4 or 8 way connectivity - returns N, the total number of labels [0, N-1] where 0
  represents the background label. ltype specifies the output label image type, an important
  consideration based on the total number of labels or alternatively the total number of pixels in
  the source image. ccltype specifies the connected components labeling algorithm to use, currently
  Grana's (BBDT) and Wu's (SAUF) algorithms are supported, see the
  cv::ConnectedComponentsAlgorithmsTypes for details. Note that SAUF algorithm forces a row major
  ordering of labels while BBDT does not.


  @param image the 8-bit single-channel image to be labeled
  @param labels destination labeled image
  @param stats statistics output for each label, including the background label, see below for
  available statistics. Statistics are accessed via stats(label, COLUMN) where COLUMN is one of
  cv::ConnectedComponentsTypes. The data type is CV_32S.
  @param centroids centroid output for each label, including the background label. Centroids are
  accessed via centroids(label, 0) for x and centroids(label, 1) for y. The data type CV_64F.
  @param connectivity 8 or 4 for 8-way or 4-way connectivity respectively
  @param ltype output image label type. Currently CV_32S and CV_16U are supported.
  @param ccltype connected components algorithm type (see the
  cv::ConnectedComponentsAlgorithmsTypes).
  */
  CV_EXPORTS_AS(connectedComponentsWithStatsWithAlgorithm)
  int connectedComponentsWithStats(InputArray image,
                                   OutputArray labels,
                                   OutputArray stats,
                                   OutputArray centroids,
                                   int connectivity,
                                   int ltype,
                                   int ccltype);

}; // namespace cv

  #endif
#endif // _H_CONNECTED_COMPONENTS_
