add_library(oingo-materials STATIC test_materials.cpp)
target_include_directories(oingo-materials INTERFACE ${PROJECT_SOURCE_DIR}/src/materials)
target_link_libraries(oingo-materials PUBLIC oingo-common)