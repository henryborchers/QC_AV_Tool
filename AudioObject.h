//
// Created by Henry on 5/26/2015.
//

#ifndef QC_TESTER_AUDIOOBJECT_H
#define QC_TESTER_AUDIOOBJECT_H

#include <string>
#include "AV_Item.h"

class AudioObject : public AV_Item {
public:
    AudioObject(const std::string &filename, AV_Item::MediaType type=AV_Item::AUDIO);

protected:
    int audioBitRate;
    int audioBitDepth;
    int audioSampleRate;
    std::string audioCodec;
    int audioChannels;
};


#endif //QC_TESTER_AUDIOOBJECT_H
