# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.
#工程路径
set(pathToProject /Users/ren/AndroidStudioProjects/ExpressAssistant)
#OpenCV-android-sdk路径
set(pathToOpenCv /Users/ren/Downloads/OpenCV-android-sdk/sdk)
cmake_minimum_required(VERSION 3.4.1)


#支持-std=gnu++11
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

#配置加载native依赖
include_directories(/Users/ren/Downloads/OpenCV-android-sdk/sdk/native/jni/include)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp )



#动态方式加载
add_library( lib_opencv SHARED IMPORTED )

#引入libopencv_java3.so文件
set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION /Users/ren/AndroidStudioProjects/ExpressAssistant/app/src/main/jniLibs/${ANDROID_ABI}/libopencv_java3.so)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( native-lib $\{log-lib} lib_opencv)
