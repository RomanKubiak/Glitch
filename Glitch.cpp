#include <Bounce.h>
#include <Keypad.h>
#include <Keypad_MC17.h>
#include <Button.h>
#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <font_Arial.h>
#include <font_ArialBold.h>
#include <ILI9341_t3.h>
#include <stdarg.h>

// this is a change

#include "Core/Functions.h"

#include "Effects/GlitchEffectBase.h"

#include "Core/Constants.h"
#include "Core/Types.h"
#include "Core/Globals.h"

#include "Effects/GlitchChorus.h"
#include "Effects/GlitchFlanger.h"
#include "Effects/GlitchBitcrusher.h"
#include "Effects/GlitchModulator.h"
#include "Effects/GlitchDistortClip.h"
#include "Display/GlitchDisplayILI9341.h"
#include "Storage/GlitchStorage.h"

void glitch_selectNextTrack(void);
void glitch_selectTrack(const byte trackToSelect);
void glitch_toggleStep(const uint8_t stepToToggle);
void glitch_initTracks();
void positionTimerCallback();
void debugCallback();

IntervalTimer posTimer;
IntervalTimer debugTimer;

static unsigned long lastMillis;

void setup()
{
    Serial.begin(115200); // open the serial
    DEBUG ("Serial port started");

    AudioMemory(40);

    audioShield.enable();
    audioShield.volume(0.4);

    glitch_initTracks();

    pinMode(KPD_PIN_SELECT, INPUT_PULLUP);
    pinMode(KPD_PIN_MODE, INPUT_PULLUP);
    pinMode(KPD_PIN_OPT, INPUT_PULLUP);
    pinMode(POT0_PIN, INPUT);

    setMixer16Levels(&fxMixer, 0);
    fxMixer.gain(3,0.5);
    trackButtons.begin();
    trackButtons.setDebounceTime(1);

    ledPosStrip.begin();
    ledPosStrip.setBrightness(10);
    ledStepStrip.begin();
    ledStepStrip.setBrightness(10);

    initDisplay();
    glitchStorage.init();
    glitchStorage.showDir(glitchStorage.getRoot(), 0);

    posTimer.begin(positionTimerCallback, 150000);
    debugTimer.begin(debugCallback, 50000);
    glitch_selectTrack(0);
}

void loop()
{
    if (currentMillis > lastMillis + 250)
    {
        DEBUG("POT CHANGED: %d", readAnaloPot(POT0_PIN));
        lastMillis = currentMillis;
    }

    if (lastPosition != currentPosition)
    {
        lastPosition = currentPosition;
    }

    if (selectButton.update() && selectButton.risingEdge())
    {
        glitch_selectNextTrack();
    }

    if (trackButtons.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)
        {
            if (trackButtons.key[i].stateChanged)
            {
                if (trackButtons.key[i].kstate == PRESSED)
                {
                    glitch_toggleStep((uint8_t)trackButtons.key[i].kchar);
                }
            }
        }
    }
}

/* glitch functions */
void glitch_selectTrack(const byte trackToSelect)
{
  DEBUG("glitch_selectTrack %d", trackToSelect);
  ledStepStrip.clear();

  /* set the select led to the current track color */
  ledStepStrip.setPixelColor (0, glitchTracks[trackToSelect].color);

  /* read the track state for each step and light them up */
  for (int i=0; i<glitchTracks[trackToSelect].length; i++)
  {
    if (bitRead(glitchTracks[trackToSelect].state, i))
      ledStepStrip.setPixelColor (i+1, glitchTracks[trackToSelect].color);
  }

  /* show the state now */
  ledStepStrip.show();
}

void glitch_selectNextTrack()
{
  if (currentTrack == G_MAX_TRACKS-1)
    currentTrack = 0;
  else
    currentTrack++;

  glitch_selectTrack(currentTrack);
}

void glitch_toggleStep(const uint8_t stepToToggle)
{
  if (bitRead(glitchTracks[currentTrack].state, stepToToggle))
  {
    bitClear (glitchTracks[currentTrack].state, stepToToggle);
    ledStepStrip.setPixelColor (stepToToggle+1, 0x0);
  }
  else
  {
    bitSet (glitchTracks[currentTrack].state, stepToToggle);
    ledStepStrip.setPixelColor (stepToToggle+1, glitchTracks[currentTrack].color);
  }

  ledStepStrip.show();
}

void glitch_initTracks()
{
  glitchTracks[0].color = Adafruit_NeoPixel::Color(255,0,0);
  glitchTracks[1].color = Adafruit_NeoPixel::Color(0,255,0);
  glitchTracks[2].color = Adafruit_NeoPixel::Color(0,0,255);
  glitchTracks[3].color = Adafruit_NeoPixel::Color(255,255,0);
  glitchTracks[4].color = Adafruit_NeoPixel::Color(255,0,255);
  glitchTracks[5].color = Adafruit_NeoPixel::Color(255,255,255);
}

void positionTimerCallback()
{
    ledPosStrip.clear();
    ledPosStrip.setPixelColor(currentPosition+1, Adafruit_NeoPixel::Color(255,0,0));
    ledPosStrip.show();

    if (currentPosition == 15)
        currentPosition = 0;
    else
        currentPosition++;
}

void debugCallback()
{
    lastMem = AudioMemoryUsage();
    lastCpu = AudioProcessorUsage();
    currentMillis = millis();
    printDebug();
}

