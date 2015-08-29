#ifndef DWARF_SHARED_CLOCK_H_
#define DWARF_SHARED_CLOCK_H_

#include "dwarf.h"

namespace dwarf {

class Clock {
  public:
    Clock();
    Clock(const I32 fps);
    ~Clock();
    I32 fps() const;
    BOOL started() const;
    BOOL ReadyForNextFrame();
    void Start();
    void Stop();
    I64 GetCurrentTime();
    I64 GetTimeElapsed();
    I64 GetFrameTime();
    I64 GetFrameCount();

  private:
    const I32 fps_;
    BOOL started_;
    I64 frame_time_;
    I64 frame_count_;
    I64 start_time_;
    I64 current_time_;
    I64 last_time_;
    I64 next_time_;
    I64 time_elapsed_;
    I64 ReadHighResolutionTimer();
};

}

#endif