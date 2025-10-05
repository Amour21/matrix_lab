set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest ${MP2_LIBRARY})
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/gtest ${MP2_INCLUDE})
# $<TARGET_FILE:target> 
add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
