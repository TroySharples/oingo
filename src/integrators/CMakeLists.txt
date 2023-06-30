add_library(oingo-integrators STATIC whitted.cpp)
target_include_directories(oingo-integrators PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(oingo-integrators PUBLIC oingo-images oingo-specular oingo-embree)