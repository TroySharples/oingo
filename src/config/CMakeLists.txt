add_library(oingo-config STATIC config.cpp)
target_include_directories(oingo-config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(oingo-config PUBLIC cxx_std_17)