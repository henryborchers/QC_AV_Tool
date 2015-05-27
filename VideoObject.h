//
// Created by Henry on 5/26/2015.
//

#ifndef QC_TESTER_VIDEOOBJECT_H
#define QC_TESTER_VIDEOOBJECT_H
#include <string>
//#include "AV_Item.h"
#include "AudioObject.h"

class VideoObject : public AudioObject {
public:
    VideoObject(const std::string &filename);
    std::string getVideoCodec();
private:
    const std::string &videoCodec;
    const std::string &colorSpace;
    const std::string &chromaSubsampling;
    int videoBitRate = NULL;
    int videoColorDepth = NULL;
    int frameRate = NULL;
    int resolutionX = NULL;
    int resolutionY = NULL;
};


#endif //QC_TESTER_VIDEOOBJECT_H
