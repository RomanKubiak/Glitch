#ifndef GLITCH_CHORUS_H
#define GLITCH_CHORUS_H

#include "GlitchEffectBase.h"

class FxChorus : public GlitchEffectBase
{
    public:
        FxChorus() 
            :   GlitchEffectBase("CHORUS"),
                toMixer(eff,0,fxMixer,FX_INDEX_CHORUS),
                fromInput(audioInput,0,eff,0)
        {
            eff.begin(fxChorusDelayLine, FX_CHORUS_LENGTH, FX_CHORUS_VOICES);
        }
        enum Params
        {
            Voices,
            nParams  
        };
        AudioEffectChorus eff;
        AudioConnection toMixer;
        AudioConnection fromInput;
};

#endif
