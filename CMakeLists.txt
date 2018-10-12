cmake_minimum_required(VERSION 2.8)
project(Mountebank)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
endif( ZLIB_FOUND )

include_directories($ENV{BASE_INCL})
include_directories($ENV{TP_LIBCURL_INC_DIR})

add_library(base STATIC IMPORTED)
set_property(TARGET base PROPERTY IMPORTED_LOCATION $ENV{DEV_LOCAL_LIB}/libbase.a)

add_library(cppbase STATIC IMPORTED)
set_property(TARGET cppbase PROPERTY IMPORTED_LOCATION $ENV{DEV_LOCAL_LIB}/libcppbase.a)

add_library(curl STATIC IMPORTED)
set_property(TARGET curl PROPERTY IMPORTED_LOCATION $ENV{TP_LIBCURL_LIB_DIR}/libcurl.a)

add_library (ivrHttp ivrHttp.cpp ivrHttp.h)
target_link_libraries(ivrHttp cppbase base curl ${ZLIB_LIBRARIES})
set_target_properties(ivrHttp PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")


add_library (jParse parser.cpp parser.h json.hpp)
set_target_properties(jParse PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")


add_executable (${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} ivrHttp jParse)
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
