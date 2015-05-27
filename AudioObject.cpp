//
// Created by Henry on 5/26/2015.
//

#include "AudioObject.h"
#include <iostream>
#include "MediaInfoDLL.h"

AudioObject::AudioObject(const std::string &filename, AV_Item::MediaType type): AV_Item(filename, type){
using namespace MediaInfoDLL;
    MediaInfo aMi;
    aMi.Open(fileName);
    this->audioSampleRate = std::stoi(aMi.Get(Stream_Audio, 0, __T("SamplingRate"), Info_Text, Info_Name));
    this->audioBitRate  = (int)std::stoi(aMi.Get(Stream_Audio, 0, __T("BitRate"), Info_Text, Info_Name));
//    std::cout << "Bit depth: " << aMi.Get(Stream_Audio, 0, __T("BitDepth_Stored/String"), Info_Text, Info_Name) << std::endl;
//    this->audioBitDepth  = std::stoi(aMi.Get(Stream_Audio, 0, __T("BitDepth"), Info_Text, Info_Name));
//    this->audioBitDepth = (int)
    aMi.Close();
    std::cout << "Sample rate: " <<audioSampleRate << std::endl;
    std::cout << "Audio Bit Rate: " <<audioBitRate << std::endl;



}