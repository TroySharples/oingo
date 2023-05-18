add_library(oingo-cameras STATIC digital.cpp pinhole.cpp)
target_include_directories(oingo-cameras PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(oingo-cameras PUBLIC oingo-common)