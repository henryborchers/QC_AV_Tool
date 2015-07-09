//
// Created by Henry on 6/10/2015.
//

#include <iostream>
#include "MediaPlayer.h"
#include "player2.h"
//#include "videoplayer.h"


MediaPlayer::MediaPlayer(const std::string &fileName){
    this->sourceFile = new std::string(fileName);

    std::cout << *this->sourceFile << std::endl;
    ffmpeg_player2(sourceFile->c_str());

//    playerVersion();
//    printf("PLAYER VERSION %d.%d.%d\n", playerVersion.major, playerVersion.minor, playerVersion.micro);
//    ffmpeg_player2(sourceFile->c_str());
//    videoPlayer(sourceFile->c_str());

}


MediaPlayer::~MediaPlayer() {
    delete this->sourceFile;
}
