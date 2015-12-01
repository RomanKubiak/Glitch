#ifndef GLITCH_FILTER_H
#define GLITCH_FILTER_H

#ifndef GLITCH_DISTORT_CLIP_H
#define GLITCH_DISTORT_CLIP_H


class FxFilter : public GlitchEffectBase
{
    public:
        FxDistortionClip() 
            :   GlitchEffectBase("FILTER"),
                toMixerLp(eff,0,fxMixer,FX_INDEX_FILTER_LP),
                toMixerHp(eff,2,fxMixer,FX_INDEX_FILTER_HP),
                toMixerBp(eff,1,fxMixer,FX_INDEX_FILTER_BP),
                fromInput(audioInput,0,eff,0),
                fromMod(shapeSine,0,eff,1)
        {
            shapeSine.begin(0, 120, WAVEFORM_SINE);
        }
        enum Params
        {
            Cutoff,
            Resonance,
            ModAmount,
            nParams
        };
        AudioFilterStateVariable eff;
        AudioConnection toMixerLp, toMixerHp, toMixerBp;
        AudioConnection fromInput;
        AudioSynthWaveform shapeSine;
};

#endif
