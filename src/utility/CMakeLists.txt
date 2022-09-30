add_library(oingo-utility STATIC timer.cpp timer.hpp)

target_include_directories(oingo-utility PRIVATE ${PROJECT_SOURCE_DIR}/src/utility)

target_compile_features(oingo-math INTERFACE cxx_std_17)

target_link_libraries(oingo-utility PRIVATE Oingo::Logging)

add_library(Oingo::Utility ALIAS oingo-utility)