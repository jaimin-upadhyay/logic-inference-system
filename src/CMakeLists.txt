project(homework3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(HEADER_FILES input.h output.h predicate.h term.h literal.h knowledge_base.h sentence.h)

set(SOURCE_FILES input.cc output.cc predicate.cc term.cc literal.cc knowledge_base.cc sentence.cc)

add_library(homework3 ${SOURCE_FILES} ${HEADER_FILES})