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
        UNKNOWN_TYPE,
        AUDIO,
        VIDEO,
        OTHER
    };
        enum ItemProgress {
        TO_BE_CHECKED,
        CHECKING,
        COMPLETED,
        DEFERRED
    };

    enum QCStatus {
        UNKNOWN_STATUS,
        PASS,
        FAIL
    };
    
    enum QCPriority {
        LOW_PRIORITY    = 0,
        NORMAL_PRIORITY = 1,
        HIGH_PRIORITY   = 2
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

    AV_Item::ItemProgress getProgress();
    void setProgress(AV_Item::QCStatus status);

    AV_Item::QCStatus getQCStatus();
    void setQCStatus(AV_Item::QCStatus status);

    AV_Item::QCPriority getPriority();
    void setPriority(AV_Item::QCPriority newPriority);

    const std::string &getNotes();
    void setGeneral_QCNotes(const std::string *text);
    void addTimeBasedNote(const TimeBasedNote *note);
    const std::vector<TimeBasedNote> &getTimeBasedNotes();
    virtual const std::string &getAudioCodec()=0;
    virtual const std::string &getVideoCodec(){};

protected:
    const std::string   fileName;
private:
    unsigned int        fileSize;
    AV_Item::MediaType  mediaType;
    int                 duration;
    std::string         durationString;

    std::string                     general_QCNotes;
    AV_Item::ItemProgress           QC_status;
    AV_Item::QCStatus               item_status;
    std::vector<TimeBasedNote>      TimeBasedNotes;
    QCPriority priority;
};




#endif //QC_MACHINE_AV_ITEM_H
