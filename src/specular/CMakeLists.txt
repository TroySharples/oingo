add_library(oingo-specular INTERFACE)
target_include_directories(oingo-specular INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
find_package(Eigen3 3.3 REQUIRED)
target_link_libraries(oingo-specular INTERFACE Eigen3::Eigen)