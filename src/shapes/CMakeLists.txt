add_library(oingo-shapes STATIC sphere.cpp sphere.hpp shape.hpp)
target_include_directories(oingo-shapes PRIVATE ${PROJECT_SOURCE_DIR}/src/shapes)
target_link_libraries(oingo-shapes PUBLIC Oingo::Common)
add_library(Oingo::Shapes ALIAS oingo-shapes)