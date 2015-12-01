#ifndef TYPES_H
#define TYPES_H

struct glitchTrack
{
  uint32_t color;
  uint16_t state = 0x0;
  bool forward = true;
  byte length = 16;
  byte currentPosition = 0;
} glitchTracks[G_MAX_TRACKS];

#endif
