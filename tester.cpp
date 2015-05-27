//
// Created by Henry on 5/24/2015.
//

#include <cstdio>
#include <iostream>
#include <string>
#include "AV_Item.h"
#include "VideoObject.h"
#include "AudioObject.h"


int main(){
    std::puts("\nTesting VideoObject ()");
//    AV_Item dummy("D:\\media\\tv\\15.mp4");
    VideoObject video("D:\\media\\tv\\15.mp4");
    std::puts("\nTesting AudioObject ()");
    AudioObject audio("D:\\Users\\Henry\\Documents\\workspace\\qt\\QC_machine\\03 Stranger.mp3");



    return 0;
}