#ifndef GLITCH_DISTORT_CLIP_H
#define GLITCH_DISTORT_CLIP_H


class FxDistortionClip : public GlitchEffectBase
{
    public:
        FxDistortionClip() 
            :   GlitchEffectBase("DIST CLIP"),
                toMixer(eff,0,fxMixer,FX_INDEX_DIST_CLIP),
                fromInput(audioInput,0,eff,0)
        {
        }
        enum Params
        {
            Thres,
            nParams
        };
        AudioEffectDistortionClipper eff;
        AudioConnection toMixer;
        AudioConnection fromInput;
};
#endif
