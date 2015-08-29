#include "clock.h"

#include <time.h>

#ifdef DWARF_OSX
#include <mach/clock.h>
#include <mach/mach.h>
#endif

namespace dwarf {

Clock::Clock()
    : fps_(15),
      started_(false),
      frame_time_(0),
      frame_count_(0),
      start_time_(0),
      last_time_(0),
      time_elapsed_(0) {
  frame_time_ = 1000000000 / static_cast<I64>(fps_);
}

Clock::Clock(const I32 fps)
    : fps_(fps),
      started_(false),
      frame_time_(0),
      frame_count_(0),
      start_time_(0),
      last_time_(0),
      time_elapsed_(0) {
  frame_time_ = 1000000000 / static_cast<I64>(fps_);
}

Clock::~Clock() {}

I32 Clock::fps() const {
  return fps_;
}

BOOL Clock::started() const {
  return started_;
}

BOOL Clock::ReadyForNextFrame() {
  if (started()) {
    current_time_ = GetCurrentTime();
    if (current_time_ > next_time_) {
      time_elapsed_ = current_time_ - last_time_;
      last_time_ = current_time_;
      next_time_ = current_time_ + frame_time_;
      frame_count_++;
      return true;
    }
  }
  return false;
}

void Clock::Start() {
  started_ = true;
  time_elapsed_ = 0;
  start_time_ = ReadHighResolutionTimer();
  next_time_ = frame_time_;
}

void Clock::Stop() {
  started_ = false;
}

I64 Clock::GetCurrentTime() {
  current_time_ = ReadHighResolutionTimer();
  return current_time_ - start_time_;
}

I64 Clock::GetTimeElapsed() {
  return time_elapsed_;
}

I64 Clock::GetFrameTime() {
  return frame_time_;
}

I64 Clock::GetFrameCount() {
  return frame_count_;
}

I64 Clock::ReadHighResolutionTimer() {
  if (started()) {
    struct timespec ts;
#ifdef DWARF_OSX
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;
#endif
#ifdef DWARF_LINUX
    clock_gettime(CLOCK_MONOTONIC, &ts);
 #endif
    return static_cast<I64>(ts.tv_sec) * 1000000000
      + static_cast<I64>(ts.tv_nsec);
  }
  return 0;
}

}