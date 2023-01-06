add_library(oingo-test-scenes STATIC test_scenes.cpp test_scenes.hpp)
target_link_libraries(oingo-test-scenes PUBLIC oingo-scene)
add_library(Oingo::Test-Scenes ALIAS oingo-test-scenes)