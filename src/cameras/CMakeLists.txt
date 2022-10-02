add_library(oingo-cameras STATIC digital.cpp digital.hpp pinhole.hpp camera.hpp)
target_include_directories(oingo-cameras PRIVATE ${PROJECT_SOURCE_DIR}/src/cameras)
target_link_libraries(oingo-cameras PUBLIC Oingo::Common Oingo::Film)
add_library(Oingo::Cameras ALIAS oingo-cameras)