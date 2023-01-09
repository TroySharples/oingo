add_library(oingo-scene STATIC test_scenes.cpp test_scenes.hpp scene.hpp object.hpp)
target_include_directories(oingo-scene PRIVATE ${PROJECT_SOURCE_DIR}/src/scene)
target_link_libraries(oingo-scene PUBLIC Oingo::Materials Oingo::Lights Oingo::Cameras Oingo::Shapes)
add_library(Oingo::Scene ALIAS oingo-scene)