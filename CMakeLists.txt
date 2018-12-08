
cmake_minimum_required(VERSION 2.8)
project( Count )

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package( OpenCV REQUIRED core imgproc highgui flann imgcodecs)
find_package( ROOT REQUIRED )

file(GLOB COUNT_SRC
    "*.h"
    "*.cpp"
)

list(REMOVE_ITEM COUNT_SRC FiberInfo.cpp FiberInfo.h)

include(${ROOT_USE_FILE})
include_directories( ${OpenCV_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS} )

ROOT_GENERATE_DICTIONARY(
    G__FiberInfo FiberInfo.h
    LINKDEF FiberLinkDef.h
)

add_library(FiberInfo SHARED G__FiberInfo.cxx FiberInfo.cpp FiberInfo.h)
add_executable( Count ${COUNT_SRC})
target_link_libraries( Count ${OpenCV_LIBS} ${ROOT_LIBRARIES} FiberInfo)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/count.jpg
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
