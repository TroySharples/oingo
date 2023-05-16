add_library(oingo-scene STATIC test_scenes.cpp)
target_include_directories(oingo-scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(oingo-scene PUBLIC oingo-materials oingo-lights oingo-cameras oingo-shapes)