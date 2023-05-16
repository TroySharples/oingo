add_library(oingo-materials STATIC test_materials.cpp)
target_include_directories(oingo-materials PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.. PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(oingo-materials PUBLIC oingo-common)