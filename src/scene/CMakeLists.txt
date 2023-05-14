add_library(oingo-scene STATIC test_scenes.cpp)
target_include_directories(oingo-scene PRIVATE ${PROJECT_SOURCE_DIR}/src/scene)
target_link_libraries(oingo-scene PUBLIC oingo-materials oingo-lights oingo-cameras oingo-shapes)