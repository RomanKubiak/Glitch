#ifndef GLITCH_BITCRUSHER_H
#define GLITCH_BITCRUSHER_H

#include "GlitchEffectBase.h"

class FxBitcrusher : public GlitchEffectBase
{
    public:
        FxBitcrusher() 
            :   GlitchEffectBase("BITCRUSH"),
                toMixer(eff,0,fxMixer,FX_INDEX_BITCRUSHER),
                fromInput(audioInput,0,eff,0)
        {
            eff.bits(FX_BITCRUSHER_BITS);
            eff.sampleRate(FX_BITCRUSHER_RATE);
        }
        enum Params
        {
            Bits,
            Rate,
            nParams
        };
        AudioEffectBitcrusher eff;
        AudioConnection toMixer;
        AudioConnection fromInput;
};
#endif
