#ifndef VSS_VISION_FIELD_H
#define VSS_VISION_FIELD_H

#include "Utils/Types.h"
#include "Utils/EnumsAndConstants.h"
#include <opencv2/opencv.hpp>

// Idealizado da mesma forma que o std::numeric_limits. Sao contantes globais no projeto,
// nao precisamos instanciar, mas podemos alterar

// Todos os tipos de campo, posteirormente serao utilizadas as constantes em um switch, que
// selecionara o campo pela interface

class Field {
  static Point m_size;
  static Point m_min;
  static Point m_max;
  static Point m_middle;
  static Point m_goalCenter;
  static Point m_enemyGoalCenter;
  static Point m_goalMin;
  static Point m_goalMax;
  static float m_offsetX;        // largura do recuo atras do gol
  static float m_offsetY;        // largura do recuo nas bordas do campo, eixo Y
  static float m_goalAreaWidth;  // largura da area no eixo x
  static float m_goalAreaHeight; // altura da area eixo y
  // static float m_goalAreaMinX; //finalzinho da nossa area, saindo do gol pro meio de campo.
  // static float m_goalAreaMaxX; //fundo do gol amigo 170
  // static float m_goalAreaMinY;  //inicio da area no eixo y, de baixo pra cima
  // static float m_goalAreaMaxY; //final da area no eixo y, de baixo pra cima
  static Point m_goalAreaMin;
  static Point m_goalAreaMax;
  // static Point m_goalMin;

 public:
  Field();

  static void set(Point t_size,
                  float t_offsetX = 10.0,
                  float t_offsetY = 0.0,
                  float t_goalSize = 40.0,
                  float t_goalAreaWidth = 15.0,
                  float t_goalAreaHeight = 70);
  static void set3x3();
  static void set5x5();

  static const Point& size();
  static const Point& min();
  static const Point& max();
  static const Point& middle();
  static const Point& goalCenter();
  static const Point& enemyGoalCenter();
  static const Point& goalMin();
  static const Point& goalMax();
  static const float& offsetX();
  static const float& offsetY();
  static const float& goalAreaWidth();
  static const float& goalAreaHeight();
  static const Point& goalAreaMin();
  static const Point& goalAreaMax();
};

#endif // VSS_VISION_FIELD_H
