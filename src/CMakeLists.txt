cmake_minimum_required(VERSION 3.6)
set(SRC
       BloomFilter.cc
       MurmurHash3.cc
)
add_library(${PROJECT_NAME} SHARED ${SRC})
add_library(sub::bloomfilter ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)