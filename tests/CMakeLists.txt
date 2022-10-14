add_library(oingo-test-scenes STATIC test_scenes.cpp test_scenes.hpp)
target_include_directories(oingo-test-scenes PUBLIC ${PROJECT_SOURCE_DIR}/tests)
target_link_libraries(oingo-test-scenes PUBLIC oingo-scene)
add_library(Oingo::Test-Scenes ALIAS oingo-test-scenes)