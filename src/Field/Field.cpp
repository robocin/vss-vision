#include "Field.h"

/*
Point(170.0, 130.0), // size
Point(10.0, 0.0),  // min
Point(160.0, 130.0),   // max
Point(85.0, 65.0),   // middle
Point(160.0, 65.0),  // goal_center
Point(10.0, 65.0)  // enemy_goal_center
*/

void Field::set(Point t_size,
                float t_offsetX,
                float t_offsetY,
                float t_goalSize,
                float t_goalAreaWidth,
                float t_goalAreaHeight) {
  m_size = t_size;//Point(170.0, 130.0)
  m_offsetX = t_offsetX; // 10
  m_offsetY = t_offsetY; //0
  m_min = Point(t_offsetX, t_offsetY); //10,0
  m_max = Point(t_size.x - t_offsetX, size().y - t_offsetY);//160,130
  m_middle = t_size / 2.0;//85,65
  m_goalCenter = Point(max().x + offsetX(), middle().y); //170,65
  m_enemyGoalCenter = Point(min().x - offsetX(), middle().y);//0,65
  //-------------------------------------------
  //m_goalMinX = max().x;
  m_goalMin = Point(max().x,middle().y - t_goalSize / 2.0);//160 45
  //--------------------------------------------------
  //m_goalMaxX = max().x + offsetX();//170
  m_goalMax = Point(max().x + offsetX(),middle().y + t_goalSize / 2.0);//170 85
  //-----------------------------------------------------
  m_goalAreaWidth = t_goalAreaWidth;    //15
  m_goalAreaHeight = t_goalAreaHeight;  //70
  //------------------
  //m_goalAreaMinX = max().x - goalAreaWidth(); //135     não subtraio offset por que o max já é sem o offset(acredito que esteja errado)
  //m_goalAreaMinY = middle().y - m_goalAreaHeight / 2.0; //30
  m_goalAreaMin = Point(max().x - goalAreaWidth(),middle().y - goalAreaHeight()/2.0);//135,30
  //-------------------
  //m_goalAreaMaxX = max().x; //160
  //m_goalAreaMaxY = middle().y + m_goalAreaHeight / 2.0; //100
  m_goalAreaMax = Point(max().x,middle().y + goalAreaHeight()/2.0);//160,100
  //--------------------------------

}

void Field::set3x3() {
  // Depois colocar direatamente para facilitar a checagem dos valores
  /*
  m_size = Point(170.0, 130.0);
  m_min  = Point( 10.0,   0.0);
  m_max  = Point(160.0, 130.0);
  ...
  */
  set(Point(170.0, 130.0), 10.0, 0.0);
}

void Field::set5x5() {
  set(Point(-1.0, -1.0), -1.0, -1.0);
}

const Point &Field::size() {
  return m_size;
}

const Point &Field::min() {
  return m_min;
}

const Point &Field::max() {
  return m_max;
}

const Point &Field::middle() {
  return m_middle;
}

const Point &Field::goalCenter() {
  return m_goalCenter;
}

const Point &Field::enemyGoalCenter() {
  return m_enemyGoalCenter;
}

const Point &Field::goalMin() {
  return m_goalMin;
}

const Point &Field::goalMax() {
  return m_goalMax;
}

const float &Field::offsetX() {
    return m_offsetX;
}

const float &Field::offsetY() {
    return m_offsetY;
}

const float &Field::goalAreaWidth() {
    return m_goalAreaWidth;
}

const float &Field::goalAreaHeight() {
    return m_goalAreaHeight;
}

const Point &Field::goalAreaMin() {
    return m_goalAreaMin;
}

const Point &Field::goalAreaMax() {
    return m_goalAreaMax;
}


// Membros 'static' precisam de uma declaracao previa;
Point Field::m_size;
Point Field::m_min;
Point Field::m_max;
Point Field::m_middle;
Point Field::m_goalCenter;
Point Field::m_enemyGoalCenter;
Point Field::m_goalMin;
Point Field::m_goalMax;
float Field::m_offsetX;
float Field::m_offsetY;
float Field::m_goalAreaWidth;
float Field::m_goalAreaHeight;
Point Field::m_goalAreaMin;
Point Field::m_goalAreaMax;
