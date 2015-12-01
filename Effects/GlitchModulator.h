#ifndef GLITCH_MODULATOR_H
#define GLITCH_MODULATOR_H

class FxModulator : public GlitchEffectBase
{
    public:
        FxModulator() 
            :   GlitchEffectBase("MODULATOR"),
                toMixer(eff,0,fxMixer,FX_INDEX_MODULATOR),
                fromInput(audioInput,0,eff,0),
                sineToFx(shapeSine, 0, shapeMixer, 0),
                sawToFx(shapeSaw, 0, shapeMixer, 1),
                squareToFx(shapeSquare, 0, shapeMixer,  2),
                pulseToFx(shapePulse, 0, shapeMixer, 3),
                triToFx(shapeTriangle, 0, shapeMixer, 4),
                whiteToFx(shapeNoiseWhite, 0,  shapeMixer, 5),
                pinkToFx(shapeNoisePink, 0, shapeMixer, 6),
                shapeMixerToFx(shapeMixer, 0, eff, 1)
        {
            shapeSine.begin(FX_MODULATOR_LEVEL, FX_MODULATOR_FREQ, WAVEFORM_SINE);
            shapeSaw.begin(FX_MODULATOR_LEVEL, FX_MODULATOR_FREQ, WAVEFORM_SAWTOOTH);
            shapeSquare.begin(FX_MODULATOR_LEVEL, FX_MODULATOR_FREQ, WAVEFORM_SQUARE);
            shapePulse.begin(FX_MODULATOR_LEVEL, FX_MODULATOR_FREQ, WAVEFORM_PULSE);
            shapeTriangle.begin(FX_MODULATOR_LEVEL, FX_MODULATOR_FREQ, WAVEFORM_TRIANGLE);
            shapeMixer.gain(0,FX_MODULATOR_MIX_LEVEL);
            shapeMixer.gain(1,0);
            shapeMixer.gain(2,0);
            shapeMixer.gain(3,0);
            shapeMixer.gain(4,0);
            shapeMixer.gain(5,0);
            shapeMixer.gain(6,0);
            shapeMixer.gain(7,0);
        }
        enum Params
        {
            Shape,
            Freq,
            Amount,
            nParams
        };
        enum Shape
        {
            Sine,
            Saw,
            Square,
            Pulse,
            Tri,
            WhiteNoise,
            PinkNoise,
            nShapes  
        };
        uint8_t getNumParams() { return (nParams); }
        char *getParamName(uint8_t index)
        {
            switch (index)
            {
                case Shape:
                    return ("Mod Shape");
                case Freq:
                    return ("Mod Freq");
                case Amount:
                    return ("Amount");
                default:
                    return ("?");
            }
        }
        void getParamText(uint8_t index, char *textToDisplay)
        {
            switch (index)
            {
                case Shape:
                    sprintf (textToDisplay, "%s", getShapeName());
                    break;
                default:
                    sprintf (textToDisplay, "?");
                    break;
            }
        }
        const char *getShapeName()
        {
            return ("Sine");
        }
        void setState(void *data){}
        void *getState()
        {
            return nullptr;
        }
        void setValue(uint8_t index, int16_t value)
        {
            switch (index)
            {
                case Shape:
                    setCurrentShape(value);
                    break;
                case Freq:
                    freq = value;
                    break;
                case Amount:
                    amount = value;
                    break;
                default:
                    break;
            }
        }
        int16_t getValue(uint8_t index)
        {
            switch (index)
            {
                case Shape:
                    return (shape);
                case Freq:
                    return (freq);
                case Amount:
                    return (amount);
                default:
                    return (0);
            }
        }
        void setCurrentShape(int16_t index)
        {
        }
        AudioEffectMultiply             eff;
        AudioConnection                 toMixer;
        AudioConnection                 fromInput;
        AudioMixer8                     shapeMixer;
        AudioSynthWaveform              shapeSine;
        AudioSynthWaveform              shapeSaw;
        AudioSynthWaveform              shapeSquare;
        AudioSynthWaveform              shapePulse;
        AudioSynthWaveform              shapeTriangle;
        AudioSynthNoiseWhite            shapeNoiseWhite;
        AudioSynthNoisePink             shapeNoisePink;
        AudioConnection                 sineToFx;
        AudioConnection                 sawToFx;
        AudioConnection                 squareToFx;
        AudioConnection                 pulseToFx;
        AudioConnection                 triToFx;
        AudioConnection                 whiteToFx;
        AudioConnection                 pinkToFx;
        AudioConnection                 shapeMixerToFx;
        private:
            int16_t amount, freq;
            uint8_t shape;
};

FxModulator fxModulator;

#endif
