#ifndef GLITCH_STORAGE_H
#define GLITCH_STORAGE_H

#define BUFFPIXEL 128

class GlitchStorage
{
    public:
        GlitchStorage() : cardOk(false)
        {
        }
        bool init()
        {
            boolean status;
            float size;
            SPI.setMOSI(7);  // Audio shield has MOSI on pin 7
            SPI.setSCK(14);  // Audio shield has SCK on pin 14

            cardOk = card.init(10); // Audio shield has SD card SD on pin 10
            if (cardOk)
            {
                DEBUG("SD card is connected :-)");
            }
            else
            {
                DEBUG("SD card is not connected or unusable :-(");
            }

            if (cardOk)
            {
                cardOk = volume.init(card);
                if (!cardOk)
                {
                    DEBUG("Unable to access the filesystem on this card. :-(");
                }
            }

            if (cardOk)
            {
                size = volume.blocksPerCluster() * volume.clusterCount();
                size = size * (512.0 / 1e6); // convert blocks to millions of bytes
                DEBUG("File system space is %d size MBytes", size);

                cardOk = SD.begin(10); // Audio shield has SD card CS on pin 10
                if (cardOk)
                {
                    DEBUG("SD library is able to access the filesystem");
                }
                else
                {
                    DEBUG("SD library can not access the filesystem!");
                }

                root = SD.open("/");
            }
            
            return (cardOk);
        }

        void showDir(File dir, uint8_t tabs)
        {
            while (true)
            {
                File entry =  root.openNextFile();
                if (! entry)
                    break;
                for (uint8_t i = 0; i < tabs; i++)
                {
                    Serial.print('\t');
                }
                Serial.print(entry.name());
                if (entry.isDirectory())
                {
                    Serial.println("/");
                    showDir(entry, tabs + 1);
                }
                else
                {
                    Serial.print(" - ");
                    Serial.println(entry.size(), DEC);
                }
                entry.close();
            }
        }

        File &getRoot() { return (root); }
        
     private:
        File root;
        boolean cardOk;
        Sd2Card card;
        SdVolume volume;
};

GlitchStorage glitchStorage;
#endif
