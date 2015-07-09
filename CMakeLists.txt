cmake_minimum_required(VERSION 3.2)
project(QC_machine)
project(QC_tester)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTOMOC ON)
set(TEST_FILES tester.cpp videoplayer.h videoplayer.cpp player2.h player2.cpp)
set(SOURCE_FILES
    avmodel.cpp
    avmodel.h
    filetreemodel.cpp
    filetreemodel.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    MediaInfoDLL.h
    treeitem.cpp
    treeitem.h
    treemodel.cpp
    treemodel.h
    videoplayer.h
    videoplayer.cpp
    player2.h
    player2.cpp
    AV_Item.cpp
    AV_Item.h)

add_executable(QC_machine ${SOURCE_FILES} VideoObject.cpp VideoObject.h AudioObject.cpp AudioObject.h delegate.cpp single_item_proxy.cpp single_item_proxy.h MediaPlayer.cpp MediaPlayer.h)
add_executable(QC_tester ${TEST_FILES} MediaPlayer.cpp MediaPlayer.h)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(ffmpeg REQUIRED)
find_package(SDL2 REQUIRED)

target_link_libraries(QC_machine Qt5::Widgets)
target_link_libraries(QC_machine Qt5::Core)

if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(QC_tester ${SDL2_LIBRARY})
    target_link_libraries(QC_machine ${SDL2_LIBRARY})
else()
    message(ERROR "SDL2 not found")
endif(SDL2_FOUND)

if(FFMPEG_FOUND)
    include_directories(${FFMPEG_INCLUDE_DIR})
    target_link_libraries(QC_tester ${FFMPEG_LIBRARIES})
    target_link_libraries(QC_machine ${FFMPEG_LIBRARIES})
else()
    message(ERROR "FFMPEG not found")
endif(FFMPEG_FOUND)


if(${WIN32})
    # Release specific DLLS
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        message("Debug mode")
            list( APPEND ExternalSharedLibraries ${CMAKE_SOURCE_DIR}/DLL/debug/)
                    if( DEFINED EXE_DIR )
                        set( exeDir "${EXE_DIR}" )
                    else()
                        set( exeDir "${CMAKE_CURRENT_BINARY_DIR}" )
                    endif()
                    message( INFO "\tCopying DEBUG shared libraries." )
                    file( COPY ${ExternalSharedLibraries} DESTINATION "${exeDir}" NO_SOURCE_PERMISSIONS )
    else()
        message("Release mode")
        list( APPEND ExternalSharedLibraries ${CMAKE_SOURCE_DIR}/DLL/release/)
                            if( DEFINED EXE_DIR )
                                set( exeDir "${EXE_DIR}" )
                            else()
                                set( exeDir "${CMAKE_CURRENT_BINARY_DIR}" )
                            endif()
                            message( INFO "\tCopying Release shared libraries." )
                            file( COPY ${ExternalSharedLibraries} DESTINATION "${exeDir}" NO_SOURCE_PERMISSIONS )
    endif (CMAKE_BUILD_TYPE MATCHES Debug)
    # General DLLS
    list( APPEND ExternalSharedLibraries ${CMAKE_SOURCE_DIR}/DLL/general/)
            # Where will the executables be located?
#                message(WARNING ${ExternalSharedLibraries})
            if( DEFINED EXE_DIR )
                set( exeDir "${EXE_DIR}" )
            else()
                set( exeDir "${CMAKE_CURRENT_BINARY_DIR}" )
            endif()
            message( INFO "\tCopying general shared libraries." )
            file( COPY ${ExternalSharedLibraries} DESTINATION "${exeDir}" NO_SOURCE_PERMISSIONS )

endif(${WIN32})