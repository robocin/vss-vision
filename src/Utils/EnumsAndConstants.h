#ifndef ENUMSANDCONSTANTS_H
#define ENUMSANDCONSTANTS_H

#include "Defines.h"
#include "BetterEnum.h"
#include <cstddef>
#include <vector>
#include <cstring>

// Sempre que um grupo de objetos fizer parte do mesmo tipo,
// colocar em um list initialization e agrupar. Criar uma funcao na
// Utils que retorna se eh valido ou n

namespace Constants {
  // Quantidade maxima de jogadores, dado qualquer campo
  static constexpr size_t MAX_PLAYERS = 20;

  // Quantidade maxima de iteracoes anteriosres que serao salvas, TALVEZ PRECISE SER DINAMICO! A CONTRIBUICAO
  // IDEAL DE FRAMES ANTERIORES DEPENDE DA CAMERA E DE OUTROS FATORES
  static constexpr size_t MAX_ITERATIONS = 7;

  static constexpr size_t MAX_PARAMETERS = 50; // valor bem alto

  // Definicoes do valor de PI
  static constexpr double PI   = 3.14159265358979323846;
  static constexpr double PI_2 = 1.57079632679489661923;
  static constexpr double PI_4 = 0.78539816339744830962;

  // Index invalido
  static const size_t INVALID_INDEX = static_cast<size_t>(-1);

  enum Compare {
    LESS = -1,
    EQUAL,
    GREATER
  };

  BETTER_ENUM(Fields, int, INVALID = -1, size3x3, size5x5);

  BETTER_ENUM(Color, int,
    INVALID = -1,
    ORANGE,
    BLUE,
    YELLOW,
    RED,
    GREEN,
    PINK,
    CYAN,
    PURPLE,
    BROWN
  );

  enum fieldWall {
    NONE_WALL,
    BOTTOM_WALL,
    UP_WALL,
    RIGHT_WALL,
    LEFT_WALL
  };

  // Agrupamento de todas as cores validas
  static constexpr std::initializer_list<Color::_enumerated> ALL_COLORS {
    Color::ORANGE,
    Color::BLUE,
    Color::YELLOW,
    Color::RED,
    Color::GREEN,
    Color::PINK,
    Color::CYAN,
    Color::PURPLE,
    Color::BROWN
  };

  // Agrupamento que identifica se uma cor eh de time ou nao
  static constexpr std::initializer_list<Color::_enumerated> TEAM_COLORS {
    Color::BLUE,
    Color::YELLOW
  };

  // Agrupamento que identifica que uma cor eh de robo ou nao
  static constexpr std::initializer_list<Color::_enumerated> ROBOT_COLORS {
    Color::RED,
    Color::GREEN,
    Color::PINK,
    Color::CYAN,
    Color::PURPLE,
    Color::BROWN
  };

  enum BallArea {
    INVALID_BALLAREA = -1,
    FAR,
    MIDDLE_P,
    NEAR,
    MAX_BALLAREA
  };

  /*typedef struct WallLimits {
    double yMin = 10.0;
    double yMax = 120.0;
    double goalYMax = 75.0;
    double goalYMin = 55.0;
    double ourGoalXMin = 10.0;
    double enemyGoalXMax = 160.0;
    double xMin = 20.0;
    double xMax = 150.0;
  } WallLimits;

  const WallLimits fieldLimits;*/

  /*
   * Enumerate the index of the objects (robot and ball)
   */
  enum {
    ROBOT1 = 0,
    ROBOT2 = 1,
    ROBOT3 = 2,
    ADV1 = 3,
    ADV2 = 4,
    ADV3 = 5,
    BALL = 6
  };
}

using namespace Constants;

#endif // ENUMSANDCONSTANTS_H
