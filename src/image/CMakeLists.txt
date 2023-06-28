add_library(oingo-image STATIC rgb.cpp)
target_include_directories(oingo-image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Eigen3 3.3 REQUIRED)
target_link_libraries(oingo-image PRIVATE Eigen3::Eigen)