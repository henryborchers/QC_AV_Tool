//
// Created by Henry on 5/24/2015.
//

#ifndef QC_MACHINE_AV_ITEM_H
#define QC_MACHINE_AV_ITEM_H

#include <string>
#include <vector>

class AV_Item {
public:
    enum MediaType {
        MT_NONE,
        MT_UNKNOWN,
        MT_AUDIO,
        MT_VIDEO,
        MT_OTHER
    };
    enum ProgressStatus {
        PS_NONE,
        PS_UNCHECKED,
        PS_CHECKING,
        PS_COMPLETED,
        PS_DEFERRED
    };

    enum QualityValue {
        QV_NONE = 0,
        QV_UNKNOWN = 1,
        QV_PASS = 2,
        QV_FAIL = 3
    };
    
    enum QCPriority {
        PRIORITY_NONE = 0,
        PRIORITY_LOW = 1,
        PRIORITY_NORMAL = 2,
        PRIORITY_HIGH = 3
    };
    
    struct TimeBasedNote {
        unsigned int startTime;
        unsigned int endTime;
        std::string note;
    };

    AV_Item(const std::string, AV_Item::MediaType mediaType);

    const std::string &getFileName();
    unsigned int getFileSize();
    AV_Item::MediaType getMediaType();
    int getDuration();
    const std::string &getDurationString();
    const char *getMediaTypeString();

    AV_Item::ProgressStatus getProgress();
    void setProgress(AV_Item::ProgressStatus value);

    AV_Item::QualityValue getQuality();
    void setQuality(AV_Item::QualityValue value);

    AV_Item::QCPriority getPriority();
    void setPriority(AV_Item::QCPriority newPriority);

    const std::string &getNotes();
    void setGeneral_QCNotes(const std::string *text);
    void addTimeBasedNote(const TimeBasedNote *note);
    const std::vector<TimeBasedNote> &getTimeBasedNotes();
    virtual const std::string &getAudioCodec()=0;
    virtual const std::string &getVideoCodec()=0;

protected:
    const std::string   fileName;
private:
    unsigned int        fileSize;
    AV_Item::MediaType  mediaType;
    int                 duration;
    std::string         durationString;

    std::string                     generalQCNotes;
    AV_Item::ProgressStatus         progressStatus;
    AV_Item::QualityValue           qualityValue;
    std::vector<TimeBasedNote>      timeBasedNotes;
    QCPriority                      priority;
};




#endif //QC_MACHINE_AV_ITEM_H
