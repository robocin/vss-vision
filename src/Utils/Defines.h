#ifndef DEFINES_H
#define DEFINES_H

#include <cstdarg>

#define stringizer(args) std::string(#args)

#define emplaceInterfaceParameter(foo, bar) {                       \
  std::string str(#bar);                                            \
  size_t sz = str.size();                                           \
  size_t idx = 0;                                                   \
  for (size_t i = 0; i < sz; i++) {                                 \
    if (str[i] == '_' || std::isalnum(str[i])) {                    \
      continue;                                                     \
    }                                                               \
    idx = i + 1;                                                    \
  }                                                                 \
  foo.emplace_back(str.substr(idx), bar);                           \
}

// Matriz vazia, com os tamanhos utilizados em todo o programa
// Nao pode ser um static const pois eh utilizada sua referencia
#define EMPTY_MATRIX cv::Mat::zeros(480, 640, CV_8UC3)

#endif // DEFINES_H
