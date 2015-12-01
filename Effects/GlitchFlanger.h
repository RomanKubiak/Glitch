#ifndef GLITCH_FLANGER_H
#define GLITCH_FLANGER_H


class FxFlanger : public GlitchEffectBase
{
    public:
        FxFlanger() 
            :   GlitchEffectBase("FLANGER"),
                toMixer(eff,0,fxMixer,FX_INDEX_FLANGER),
                fromInput(audioInput,0,eff,0)
        {
            eff.begin(fxFlangerDelayLine, FX_FLANGER_LENGTH, FX_FLANGER_OFFSET, FX_FLANGER_DEPTH, FX_FLANGER_RATE);
        }
        enum Params
        {
            Depth,
            Rate,
            nParams
        };
        AudioEffectFlange eff;
        AudioConnection toMixer;
        AudioConnection fromInput;
};
#endif
