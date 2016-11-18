project(homework3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(HEADER_FILES input.h output.h predicate.h term.h)

set(SOURCE_FILES input.cc output.cc predicate.cc term.cc)

add_library(homework3 ${SOURCE_FILES} ${HEADER_FILES})