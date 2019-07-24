#ifndef _H_TIMER_
#define _H_TIMER_
#include <chrono>

class Timer {
private:
  bool paused;
  std::chrono::high_resolution_clock::time_point timebegin, timeend;
  std::chrono::nanoseconds::rep nanoseconds;
public:
  Timer(); // Starts automatically on construction
  double getSeconds();
  double getMilliseconds();
  double getMicroseconds();
  double getNanoseconds();
  double getInFPS();
  void start();
  void stop();
  void resume();
  bool isPaused();
};

#endif
