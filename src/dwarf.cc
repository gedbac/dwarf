#include <stdio.h>
#include <stdlib.h>

#include "clock.h"

using namespace dwarf;

int main() {
  printf("Dwarf 2015\n");

  const I32 fps = 1;
  Clock clock(fps);
  clock.Start();
  while (true) {
    if (clock.ReadyForNextFrame()) {
      printf("%lli\n", clock.GetFrameCount());
    }
  }
  clock.Stop();

  exit(0);
}