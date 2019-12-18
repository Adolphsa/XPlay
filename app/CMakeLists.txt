# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#add header file
include_directories(include)

#设置ffmpeg库所在路径的变量 FF为表示路径的变量，
#CMAKE_CURRENT_SOURCE_DIR为CMake内置变量，表示CMakeLists所在的目录
#ANDROID_ABI CPU架构类型，如果gradle文件没有设置过滤，
#则会表示所有的架构，arm-v7a arm-v8a x86 x86_64
#所以FF=CMAKE_CURRENT_SOURCE_DIR/libs/armeabi-v7a
set(FF ${CMAKE_CURRENT_SOURCE_DIR}/libs/${ANDROID_ABI})

#添加avcodec SHARED表示动态库 IMPORTED表示从外部导入
add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FF}/libavcodec.so)

#avformat
add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FF}/libavformat.so)

#avutil
add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FF}/libavutil.so)

#swscale
add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${FF}/libswscale.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${FF}/libswresample.so)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp
        src/main/cpp/IDemux.cpp
        src/main/cpp/FFDemux.cpp
        src/main/cpp/XData.cpp
        src/main/cpp/XLog.cpp
        src/main/cpp/XThread.cpp
        src/main/cpp/IObserver.cpp
        src/main/cpp/IDecode.cpp
        src/main/cpp/FFDecode.cpp
        src/main/cpp/XParameter.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        GLESv2 EGL
        OpenSLES
        android
        avcodec avformat avutil swscale swresample
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})