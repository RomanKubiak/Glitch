#ifndef GLITCH_EFFECT_BASE_H
#define GLITCH_EFFECT_BASE_H

class GlitchEffectBase
{
    public:
        GlitchEffectBase(const char *_name) : name(_name)
        {
            glitch_register_effect (name, this);
        }
        virtual ~GlitchEffectBase() {}
        virtual const char *getName() { return (name); }
        virtual uint8_t getNumParams() = 0;
        virtual char *getParamName(uint8_t index) = 0;
        virtual void getParamText(uint8_t index, char *textToDisplay) = 0;
        virtual void setState(void *data) = 0;
        virtual void *getState() = 0;
        virtual void setValue(uint8_t index, int16_t value) = 0;
        virtual int16_t getValue(uint8_t index) = 0;
        virtual void processMidi() {}
    private:
        const char *name;
};

#endif
