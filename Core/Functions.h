#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Audio.h>

class GlitchEffectBase;

const char* toBin (int x)
{
    static char b[sizeof(int)*8+1] = {0};
    int y;
    long long z;
    for (z=1LL<<sizeof(int)*8-1,y=0; z>0; z>>=1,y++)
    {
        b[y] = ( ((x & z) == z) ? '1' : '0');
    }

    b[y] = 0;

    return b;
}

void DEBUG(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.println(buf);
}

void setMixer8Levels (AudioMixer8 *mixer, float level)
{
    mixer->gain(0,level);
    mixer->gain(1,level);
    mixer->gain(2,level);
    mixer->gain(3,level);
    mixer->gain(4,level);
    mixer->gain(5,level);
    mixer->gain(6,level);
    mixer->gain(7,level);
}

void setMixer16Levels (AudioMixer16 *mixer, float level)
{
    mixer->gain(0,level);
    mixer->gain(1,level);
    mixer->gain(2,level);
    mixer->gain(3,level);
    mixer->gain(4,level);
    mixer->gain(5,level);
    mixer->gain(6,level);
    mixer->gain(7,level);
    mixer->gain(8,level);
    mixer->gain(9,level);
    mixer->gain(10,level);
    mixer->gain(11,level);
    mixer->gain(12,level);
    mixer->gain(13,level);
    mixer->gain(14,level);
    mixer->gain(15,level);
}

void glitch_register_effect(const char *name, GlitchEffectBase *effect)
{
    
}

int readAnaloPot(uint8_t pin)
{
    return ((analogRead(pin) / 1024.0)  * 255.0);
}
#endif
