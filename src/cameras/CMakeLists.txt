add_library(oingo-cameras STATIC digital.cpp film.cpp digital.hpp pinhole.hpp camera.hpp film.hpp)
target_include_directories(oingo-cameras PRIVATE ${PROJECT_SOURCE_DIR}/src/cameras)
target_link_libraries(oingo-cameras PUBLIC Oingo::Common)
add_library(Oingo::Cameras ALIAS oingo-cameras)