//
// Created by Henry on 6/10/2015.
//
// A placeholder class until a proper media player can be built.
// Adapter class to use the stupid video player

#ifndef QC_TESTER_MEDIAPLAYER_H
#define QC_TESTER_MEDIAPLAYER_H
#include <string>

class MediaPlayer {
public:
    MediaPlayer(const std::string &fileName);
    ~MediaPlayer();

private:
    std::string *sourceFile;



};


#endif //QC_TESTER_MEDIAPLAYER_H
