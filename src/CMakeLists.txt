project(homework3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(HEADER_FILES output.h predicate.h term.h literal.h knowledge_base.h sentence.h node.h multi_node.h knowledge_base_index.h)

set(SOURCE_FILES predicate.cc term.cc sentence.cc knowledge_base.cc)

add_library(homework3 ${SOURCE_FILES} ${HEADER_FILES})