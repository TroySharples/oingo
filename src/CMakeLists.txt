add_library(oingo-common INTERFACE)
target_link_libraries(oingo-common INTERFACE Oingo::Math)
# target_compile_definitions(oingo-common INTERFACE DOUBLE_PRECISION)
add_library(Oingo::Common ALIAS oingo-common)

add_library(oingo-ppm STATIC ppm.cpp ppm.hpp)
target_link_libraries(oingo-ppm PUBLIC Oingo::Math)
add_library(Oingo::PPM ALIAS oingo-ppm)

add_library(oingo-options STATIC options.cpp options.hpp)
target_link_libraries(oingo-options PRIVATE Oingo::Math Oingo::Scene)
add_library(Oingo::Options ALIAS oingo-options)

add_library(oingo-logging INTERFACE)
target_include_directories(oingo-logging INTERFACE ${PROJECT_SOURCE_DIR}/src)
add_library(Oingo::Logging ALIAS oingo-logging)

add_subdirectory(cameras)
add_subdirectory(integrators)
add_subdirectory(lights)
add_subdirectory(materials)
add_subdirectory(math)
add_subdirectory(scene)
add_subdirectory(shapes)