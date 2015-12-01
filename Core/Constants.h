#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Global glitch constants */
#define G_MAX_TRACKS    16

#define FX_INDEX_CHORUS     0
#define FX_INDEX_FLANGER    1
#define FX_INDEX_BITCRUSHER 2
#define FX_INDEX_DIST_CLIP  3
#define FX_INDEX_MODULATOR  4

#define FX_CHORUS           B000000000001
#define FX_FLANGER          B000000000010
#define FX_BITCRUSH         B000000000100
#define FX_DISTORTION1      B000000001000
#define FX_DISTORTION2      B000000010000
#define FX_MODULATOR        B000000100000
#define FX_FILTER1          B000001000000
#define FX_FILTER2          B000010000000
#define FX_ENVELOPE         B000100000000
#define FX_FADE             B001000000000
#define FX_REVERSE          B010000000000
#define FX_DELAY            B100000000000
#define FX_COUNT            16

/* Input keypad config */
#define KPD_I2CADDR_KEYPAD  0x27
#define KPD_PIN_SELECT      1
#define KPD_PIN_OPT         2
#define KPD_PIN_MODE        3

#define POT0_PIN            29

const byte KPD_ROWS = 4; //four rows
const byte KPD_COLS = 4; //three columns
char kpdKeymap[KPD_ROWS][KPD_COLS] = {
  {0xf,0xe,0xd,0xc},
  {0xb,0xa,9,8},
  {7,6,5,4},
  {3,2,1,0}
};
byte kpdRowPins[KPD_ROWS] = {1, 3, 5, 7};
byte kpdColPins[KPD_COLS] = {0, 2, 4, 6};

/* Global variables for input */
Keypad_MC17 trackButtons = Keypad_MC17(makeKeymap(kpdKeymap), 
                                        kpdRowPins, 
                                        kpdColPins, 
                                        KPD_ROWS, 
                                        KPD_COLS, 
                                        KPD_I2CADDR_KEYPAD);
                                        
Bounce selectButton = Bounce(KPD_PIN_SELECT, 10);
Bounce modeButton   = Bounce(KPD_PIN_MODE, 10);
Bounce optButton    = Bounce(KPD_PIN_OPT, 10);

/* Global variables for led strips */
#define PIN_LED_STEP 0
#define PIN_LED_POS  4

Adafruit_NeoPixel ledStepStrip  = Adafruit_NeoPixel(17, PIN_LED_STEP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledPosStrip   = Adafruit_NeoPixel(17, PIN_LED_POS, NEO_GRB + NEO_KHZ800);

#endif
