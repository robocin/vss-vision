#ifndef COLORSPACE_H
#define COLORSPACE_H

#include "Utils/Utils.h"
#define KMEANS_LABEL "KMEANS"
#define WHEREARE_LABEL "WHEREARETHOSE"
#define GENERIC_TRACKING_LABEL "GENERICTRACKINGLABEL"
#define SEGMENTATION_DEFAULT_FILE  "Config/Segmentation/Default.xml"

/**
 * { Structure to represent pixels in YUV color space }
 */
typedef struct YUV {
  int y;
  int u;
  int v;
} YUV;

/**
 * { Structure to represent pixels in RGB channel }
 */
typedef struct RGB {
  uchar blue;
  uchar green;
  uchar red;
} RGB;

/**
 * { Structure to represent pixels in HSV channel }
 */
typedef struct HSV {
  uchar hue;
  uchar saturation;
  uchar value;
} HSV;

/**
 * { Struct to represent a slice of colorspace. Usually used to define the segmentation intervals }
 */
typedef struct ColorInterval {
  YUV max;
  YUV min;
} ColorInterval;


namespace ColorSpace {
  extern RGB markerColors[NUMBEROFCOLOR];
  extern String colorNames[NUMBEROFCOLOR];
}

#endif // COLORSPACE_H
