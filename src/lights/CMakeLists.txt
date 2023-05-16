add_library(oingo-lights INTERFACE)
target_include_directories(oingo-lights INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(oingo-lights INTERFACE oingo-common)