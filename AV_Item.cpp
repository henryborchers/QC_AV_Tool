//
// Created by Henry on 5/24/2015.
//

#include "AV_Item.h"
#include "MediaInfoDLL.h"

AV_Item::AV_Item(const std::string filename, AV_Item::MediaType type)
        : fileName(filename),
          mediaType(type){

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

    progressStatus = TO_BE_CHECKED;
    priority = NORMAL_PRIORITY;
    qualityValue = UNKNOWN_QUALITY;
    std::printf("filename: %s\nDURATION: %d, %s\nfileSize: %d\nFormat: %d\n", fileName.c_str(), duration, durationString.c_str(), fileSize,
                mediaType);
}

const std::string &AV_Item::getFileName() {
    return this->fileName;
}

const std::string &AV_Item::getDurationString() {
    return this->durationString;
}

const char *AV_Item::getMediaTypeString() {

    switch(this->mediaType){
        case UNKNOWN_TYPE:
            return "Unknown type";

        case AUDIO:
            return "Audio";

        case VIDEO:
            return "Video";

        case OTHER:
            return "Other";

        default:
            return "Error";
    }
}

AV_Item::MediaType AV_Item::getMediaType() {
    return this->mediaType;
}

AV_Item::QCPriority AV_Item::getPriority() {
    return this->priority;
}

void AV_Item::setPriority(AV_Item::QCPriority newPriority) {
    this->priority = newPriority;
}

AV_Item::QualityValue AV_Item::getQuality() {
    return this->qualityValue;
}

AV_Item::ProgressStatus AV_Item::getProgress() {
    return this->progressStatus;
}

void AV_Item::setProgress(AV_Item::ProgressStatus value) {
    this->progressStatus = value;
}

void AV_Item::setQuality(AV_Item::QualityValue value) {
    this->qualityValue = value;
}
