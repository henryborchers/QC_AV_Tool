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
    this->colorSpace = vMi.Get(Stream_Video, 0, __T("ColorSpace"), Info_Text, Info_Name);
    this->chromaSubsampling = vMi.Get(Stream_Video, 0, __T("ChromaSubsampling"), Info_Text, Info_Name);
    this->videoBitRate = (int)std::stoi(vMi.Get(Stream_Video, 0, __T("BitRate"), Info_Text, Info_Name));
    this->videoColorDepth = (int)std::stoi(vMi.Get(Stream_Video, 0, __T("BitDepth"), Info_Text, Info_Name));
    this->frameRate = (int)std::stoi(vMi.Get(Stream_Video, 0, __T("FrameRate"), Info_Text, Info_Name));
    this->resolutionX = (int)std::stoi(vMi.Get(Stream_Video, 0, __T("Width"), Info_Text, Info_Name));
    this->resolutionY = (int)std::stoi(vMi.Get(Stream_Video, 0, __T("Height"), Info_Text, Info_Name));
    if(vMi.Get(Stream_Video, 0, __T("ScanType"), Info_Text, Info_Name) == "Progressive"){
        this->progressive=true;
    } // TODO: find an interlaced video
//    std::cout << "progressive: " << vMi.Get(Stream_Video, 0, __T("ScanType"), Info_Text, Info_Name)<< std::endl;

    vMi.Close();
    std::cout << "Video Codec: " << videoCodec << std::endl;
    std::cout << "color space: " << colorSpace << std::endl;
    std::cout << "ChromaSubsampling: " << chromaSubsampling << std::endl;
    std::cout << "videoBitRate: " << videoBitRate << std::endl;
    std::cout << "videoColorDepth: " << videoColorDepth << std::endl;
    std::cout << "frameRate: " << frameRate << std::endl;
    std::cout << "resolutionX: " << resolutionX << std::endl;
    std::cout << "resolutionY: " << resolutionY << std::endl;
    std::cout << "progressive: " << progressive << std::endl;


}

const std::string &VideoObject::getVideoCodec() {
    return this->videoCodec;
}


const std::string &VideoObject::getColorSpace() {
    return this->colorSpace;
}
