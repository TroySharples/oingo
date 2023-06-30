add_library(oingo-utils STATIC timer.cpp)
target_include_directories(oingo-utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})