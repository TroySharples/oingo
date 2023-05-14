add_library(oingo-shapes STATIC sphere.cpp cylinder.cpp tube.cpp disk.cpp)
target_include_directories(oingo-shapes PRIVATE ${PROJECT_SOURCE_DIR}/src/shapes)
target_link_libraries(oingo-shapes PUBLIC oingo-common)