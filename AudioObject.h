//
// Created by Henry on 5/26/2015.
//

#ifndef AUDIOOBJECT_H
#define AUDIOOBJECT_H

#include <string>
#include "AV_Item.h"

class AudioObject : public AV_Item {
public:
    AudioObject(const std::string &filename, AV_Item::MediaType = MT_AUDIO);
    int getAudioBitRate();
    int getAudioBitDepth();
    int getAudioSampleRate();
    const std::string &getAudioCodec();
    int getAudioChannels();

protected:
    virtual const std::string &getVideoCodec(){};
    int audioBitRate;
    int audioBitDepth;
    int audioSampleRate;
    std::string audioCodec;
    int audioChannels;
    bool initAudio();
};


#endif //AUDIOOBJECT_H
