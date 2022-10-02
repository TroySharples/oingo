add_library(oingo-objects STATIC sphere.cpp sphere.hpp object.hpp)
target_include_directories(oingo-objects PRIVATE ${PROJECT_SOURCE_DIR}/src/objects)
target_link_libraries(oingo-objects PUBLIC Oingo::Common)
add_library(Oingo::Objects ALIAS oingo-objects)