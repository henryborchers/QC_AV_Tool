//
// Created by Henry on 5/26/2015.
//

#ifndef VIDEOOBJECT_H
#define VIDEOOBJECT_H
#include <string>
//#include "AV_Item.h"
#include "AudioObject.h"


class VideoObject : public AudioObject {
public:
    VideoObject(const std::string &filename);
    std::string getVideoCodec();
private:
    std::string videoCodec;
    std::string colorSpace;
    std::string chromaSubsampling;
    int videoBitRate;
    int videoColorDepth;
    int frameRate;
    int resolutionX;
    int resolutionY;
    bool progressive;
    bool videoCodecLossy;
};


#endif //VIDEOOBJECT_H
