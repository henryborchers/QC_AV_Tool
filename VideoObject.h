//
// Created by Henry on 5/26/2015.
//

#ifndef VIDEOOBJECT_H
#define VIDEOOBJECT_H
#include <string>
//#include "AV_Item.h"
#include "AudioObject.h"


class VideoObject : public AudioObject {

private:
    std::string videoCodec;
    std::string colorSpace;
    std::string chromaSubsampling;
    int videoBitRate;
    int videoColorDepth;
    float frameRate;
    int resolutionX;
    int resolutionY;
    bool progressive;
    bool videoCodecLossy;
    bool hasSoundTrack;

public:
    VideoObject(const std::string &filename);
    const std::string &getVideoCodec();
    const std::string &getColorSpace();
    const std::string &getChromaSubsampling();
    int getVideoBitRate();
    int getVideoColorDepth();
    float getFrameRate();
    int getResolutionX();
    int getResolutionY();
    bool isProgressive();
    bool isVideoCodecLossy();
};


#endif //VIDEOOBJECT_H
