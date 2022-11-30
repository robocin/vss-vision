#include <Timer/Timer.h>

Timer::Timer() {
  this->timebegin = std::chrono::high_resolution_clock::now();
  this->paused = false;
}

double Timer::getSeconds() {
  if (!this->paused)
    this->timeend = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::seconds>(this->timeend - this->timebegin).count();
}

double Timer::getMilliseconds() {
  if (!this->paused)
    this->timeend = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(this->timeend - this->timebegin)
      .count();
}

double Timer::getMicroseconds() {
  if (!this->paused)
    this->timeend = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(this->timeend - this->timebegin)
      .count();
}

double Timer::getNanoseconds() {
  if (!this->paused)
    this->timeend = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(this->timeend - this->timebegin)
      .count();
}

double Timer::getInFPS() {
  double times = static_cast<double>(this->getNanoseconds() / 1000LL);
  return 1000000.0 / (times > 0.0 ? times : 1.0);
}

void Timer::start() {
  this->paused = false;
  this->timebegin = std::chrono::high_resolution_clock::now();
}
void Timer::stop() {
  this->paused = true;
  this->timeend = std::chrono::high_resolution_clock::now();
}

void Timer::resume() {
  this->paused = false;
}

bool Timer::isPaused() {
  return this->paused;
}
