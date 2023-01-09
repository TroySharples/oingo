add_library(oingo-materials STATIC test_materials.cpp test_materials.hpp material.hpp)
target_include_directories(oingo-materials INTERFACE ${PROJECT_SOURCE_DIR}/src/materials)
target_link_libraries(oingo-materials PUBLIC Oingo::Common)
add_library(Oingo::Materials ALIAS oingo-materials)