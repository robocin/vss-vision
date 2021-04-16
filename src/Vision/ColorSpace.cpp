#include "ColorSpace.h"

RGB ColorSpace::markerColors[NUMBEROFCOLOR] = {
        //order: blue, green, red
        {0,0,0},//NoCOL
        {0,128,255},//OrangeCOL
        {255,0,0},//BlueCOL
        {0,255,255},//YellowCOL
        {0,0,255},//RedCOL
        {0,255,0},//GreenCOL
        {255,0,255},//PinkCOL
        {255,255,0},//LightBlueCOL
        {191,15,179},//PurpleCOL
        {25,0,51},//BrownCOL
        {0,0,0}//ColorStrange
};

// LEGACY
/*
RGB ColorSpace::markerColors[NUMBEROFCOLOR] = {
        //order: blue, green, red
        {0,0,0},//NoCOL
        {20,147,255},//OrangeCOL
        {255,0,0},//BlueCOL
        {0,255,255},//YellowCOL
        {0,0,255},//RedCOL
        {0,255,0},//GreenCOL
        {164,0,255},//PinkCOL
        {206,250,135},//LightBlueCOL
        {191,15,179},//PurpleCOL
        {25,0,51},//BrownCOL
        {0,0,0}//ColorStrange
};*/
