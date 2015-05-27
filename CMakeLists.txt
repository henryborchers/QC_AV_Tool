cmake_minimum_required(VERSION 3.2)
project(QC_machine)
project(QC_tester)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTOMOC ON)
set(TEST_FILES tester.cpp AV_Item.cpp AV_Item.h)
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
    treemodel.h)

add_executable(QC_machine ${SOURCE_FILES} VideoObject.cpp VideoObject.h AudioObject.cpp AudioObject.h)
add_executable(QC_tester ${TEST_FILES} VideoObject.cpp VideoObject.h AudioObject.cpp AudioObject.h)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

target_link_libraries(QC_machine Qt5::Widgets)
target_link_libraries(QC_machine Qt5::Core)

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