#ifndef FIELD_H
#define FIELD_H

#include "Utils/Types.h"
#include "Utils/EnumsAndConstants.h"
#include <opencv2/opencv.hpp>

// Idealizado da mesma forma que o std::numeric_limits. Sao contantes globais no projeto,
// nao precisamos instanciar, mas podemos alterar

// Todos os tipos de campo, posteirormente serao utilizadas as constantes em um switch, que selecionara
// o campo pela interface

class Field {
  static Point m_size;
  static Point m_min;
  static Point m_max;
  static Point m_middle;
  static Point m_goalCenter;
  static Point m_enemyGoalCenter;
  static Point m_goalMin;
  static Point m_goalMax;
  static Float m_offsetX; //largura do recuo atras do gol
  static Float m_offsetY; //largura do recuo nas bordas do campo, eixo Y
  static Float m_goalAreaWidth; //largura da area no eixo x
  static Float m_goalAreaHeight; //altura da area eixo y
  //static Float m_goalAreaMinX; //finalzinho da nossa area, saindo do gol pro meio de campo.
  //static Float m_goalAreaMaxX; //fundo do gol amigo 170
  //static Float m_goalAreaMinY;  //inicio da area no eixo y, de baixo pra cima
  //static Float m_goalAreaMaxY; //final da area no eixo y, de baixo pra cima
  static Point m_goalAreaMin;
  static Point m_goalAreaMax;
  //static Point m_goalMin;

public:
  Field();

  static void set(Point t_size,
                  Float t_offsetX  = 10.0,
                  Float t_offsetY  =  0.0,
                  Float t_goalSize = 40.0,
                  Float t_goalAreaWidth = 15.0,
                  Float t_goalAreaHeight = 70);
  static void set3x3();
  static void set5x5();

  static const Point &size();
  static const Point &min();
  static const Point &max();
  static const Point &middle();
  static const Point &goalCenter();
  static const Point &enemyGoalCenter();
  static const Point &goalMin();
  static const Point &goalMax();
  static const Point &convertRatio();
  static const Float &offsetX();
  static const Float &offsetY();
  static const Float &goalAreaWidth();
  static const Float &goalAreaHeight();
  static const Point &goalAreaMin();
  static const Point &goalAreaMax();
};

#endif // FIELD_H
