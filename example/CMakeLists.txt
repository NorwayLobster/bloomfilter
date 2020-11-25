cmake_minimum_required(VERSION 3.6)
add_executable(bloomfilter_example_bin main.cc)
target_link_libraries(bloomfilter_example_bin
  PUBLIC
    sub::bloomfilter
 )

install(TARGETS bloomfilter_example_bin DESTINATION bin)