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
        UNKNOWN_TYPE    = 0,
        AUDIO           = 1,
        VIDEO           = 2,
        OTHER           = 3
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
    struct TimeBasedNote {
        unsigned int startTime;
        unsigned int endTime;
        std::string note;
    };

    AV_Item(const std::string, AV_Item::MediaType mediaType);

    const std::string &getFileName();
    unsigned int getFileSize();
    AV_Item::MediaType getFormat();
    int getDuration();
    const std::string getDurationString();

    AV_Item::ItemProgress getProgress();
    void setProgress(AV_Item::QCStatus status);

    AV_Item::QCStatus *getQCStatus();
    void setQCStatus(AV_Item::QCStatus status);

    const std::string &getNotes();
    void setGeneral_QCnotes(const std::string *text);
    void addTimeBasedNote(const TimeBasedNote *note);
    const std::vector<TimeBasedNote> &getTimeBasedNotes();


protected:
    const std::string   fileName;
    unsigned int        fileSize;
    AV_Item::MediaType  format;
    int                 duration;
    std::string         durationString;

    std::string                    general_QCNotes;
    AV_Item::ItemProgress          QC_status;
    AV_Item::QCStatus              item_status;
    std::vector<TimeBasedNote>     TimeBasedNotes;

};




#endif //QC_MACHINE_AV_ITEM_H
