add_library(oingo-utility STATIC timer.cpp timer.hpp)

target_include_directories(oingo-utility PRIVATE ${PROJECT_SOURCE_DIR}/src/utility)

target_compile_features(oingo-utility PUBLIC cxx_std_20)

target_link_libraries(oingo-utility PRIVATE Oingo::Logging)

add_library(Oingo::Utility ALIAS oingo-utility)