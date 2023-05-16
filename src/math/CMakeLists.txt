add_library(oingo-math INTERFACE)
target_include_directories(oingo-math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_compile_features(oingo-math INTERFACE cxx_std_20)
