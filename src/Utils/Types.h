#ifndef TYPES_H
#define TYPES_H

#include <array>
#include <deque>
#include <vector>
#include <limits>
#include "EnumsAndConstants.h"
#include <opencv2/opencv.hpp>

struct Parameters;
// Namespace que contem os tipos comuns utilizados no programa fora as classes,
// criado para facilitar a busca por tipos
namespace Types {
    using Bool         = bool;
    using Int          = int;
    using Void         = void;
    using Float        = double;
    using String       = std::string;
    using Strings      = std::vector<String>;

    template <class M, class N>
    using Pair = std::pair<M, N>;

    template <class T>
    using Vector       = std::vector<T>;

    template <class T>
    using Reference  = std::reference_wrapper<T>;

    // Vector de referencias, que serao pegas da table original
    template <class T>
    using References = std::vector<Reference<T>>;

    template <class T, size_t N>
    using Array = std::array<T, N>;

    template <class T>
    using Deque        = std::deque<T>;
    using Point          = cv::Point_<Float>;
    using Polygon        = Vector<Point>;
    using Points         = Vector<Point>;
}

using namespace Types;

#endif // TYPES_H
