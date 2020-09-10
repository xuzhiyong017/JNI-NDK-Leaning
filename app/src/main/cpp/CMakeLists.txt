# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 支持C++11标准和GNU扩展特性
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(thirdLib ${CMAKE_SOURCE_DIR}/thirdLib)

link_directories(${thirdLib}/lib)

include_directories(thirdLib/include)
include_directories(${CMAKE_SOURCE_DIR}/common/)


file(GLOB src-files
        native-lib.cpp
        ${CMAKE_SOURCE_DIR}/src/decode/*.cpp
        ${CMAKE_SOURCE_DIR}/src/utils/*.c
       )

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${src-files} )


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.


set(third-party-libs
        avformat
        avcodec
        avfilter
        swresample
        swscale
        avutil
        x264
        )

set(native-libs
        android
        EGL
        GLESv1_CM
        GLESv2
        GLESv3
        OpenSLES
        log
        m
        z
        )


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.

        ${third-party-libs}
        ${native-libs}
)
