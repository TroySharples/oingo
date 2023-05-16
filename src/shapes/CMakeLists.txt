add_library(oingo-shapes STATIC sphere.cpp cylinder.cpp tube.cpp disk.cpp)
target_include_directories(oingo-shapes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(oingo-shapes PUBLIC oingo-common)