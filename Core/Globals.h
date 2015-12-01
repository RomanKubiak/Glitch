#ifndef GLOBALS_H
#define GLOBALS_H

#define FX_CHORUS_LENGTH    (16*AUDIO_BLOCK_SAMPLES)
#define FX_CHORUS_VOICES    8

#define FX_FLANGER_LENGTH   (6*AUDIO_BLOCK_SAMPLES)
#define FX_FLANGER_OFFSET   FX_FLANGER_LENGTH/4
#define FX_FLANGER_DEPTH    FX_FLANGER_LENGTH/4
#define FX_FLANGER_RATE     .5

#define FX_BITCRUSHER_BITS  4
#define FX_BITCRUSHER_RATE  44100/4

#define FX_MOD_SHAPE_SIN    0
#define FX_MOD_SHAPE_SAW    1
#define FX_MOD_SHAPE_SQUARE 2
#define FX_MOD_SHAPE_PULSE  3
#define FX_MOD_SHAPE_TRI    4
#define FX_MOD_SHAPE_NWHITE 5
#define FX_MOD_SHAPE_NPINK  6

#define FX_MODULATOR_LEVEL      0.5f
#define FX_MODULATOR_MIX_LEVEL  0.9f
#define FX_MODULATOR_SHAPE      FX_MOD_SHAPE_SIN
#define FX_MODULATOR_FREQ       440

short fxChorusDelayLine     [FX_CHORUS_LENGTH];
short fxFlangerDelayLine    [FX_FLANGER_LENGTH];

int currentPosition = -1;
int lastPosition = -1;
byte currentTrack = -1;

AudioInputAnalog                audioInput;
AudioMixer16                    fxMixer;
AudioOutputI2S                  audioOutput;
AudioConnection                 fxMixerToOutputL        (fxMixer,               0,  audioOutput,    0);
AudioConnection                 fxMixerToOutputR        (fxMixer,               0,  audioOutput,    1);
AudioControlSGTL5000            audioShield;
#endif
