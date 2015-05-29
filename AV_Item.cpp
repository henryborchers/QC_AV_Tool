//
// Created by Henry on 5/24/2015.
//

#include "AV_Item.h"
#include "MediaInfoDLL.h"

AV_Item::AV_Item(const std::string filename, AV_Item::MediaType type): fileName(filename), format(type){

    using namespace MediaInfoDLL;

    MediaInfo Mi;
    Mi.Open(filename);
//    std::printf("the answer is %s\n",mi.Inform().c_str());
    if(Mi.Inform() != "") {

        std::printf("Ready\n");
        fileSize = (unsigned int) std::stoi(Mi.Get(Stream_General, 0, __T("FileSize"), Info_Text, Info_Name));;
        duration = std::stoi(Mi.Get(Stream_General, 0, __T("Duration"), Info_Text, Info_Name));
        durationString = Mi.Get(Stream_General, 0, __T("Duration/String3"), Info_Text, Info_Name);

    }
    Mi.Close();



    std::printf("filename: %s\nduration: %d, %s\nfileSize: %d\nFormat: %d\n", fileName.c_str(), duration, durationString.c_str(), fileSize, format);
}

const std::string &AV_Item::getFileName() {
    return this->fileName;
}

const std::string &AV_Item::getDurationString() {
    return this->durationString;
}
