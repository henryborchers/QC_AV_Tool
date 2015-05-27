//
// Created by Henry on 5/26/2015.
//
#include "VideoObject.h"
#include <iostream>
#include "MediaInfoDLL.h"


VideoObject::VideoObject(const std::string &filename): AudioObject(filename, VIDEO) {
    using namespace MediaInfoDLL;
    MediaInfo vMi;
    vMi.Open(fileName);
    this->videoCodec = vMi.Get(Stream_Video, 0, __T("CodecID"), Info_Text, Info_Name);
    vMi.Close();
    std::cout << "Video Codec: " << videoCodec << std::endl;

}
