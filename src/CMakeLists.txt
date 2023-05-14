add_library(oingo-common INTERFACE)
target_link_libraries(oingo-common INTERFACE oingo-math)

add_library(oingo-ppm STATIC ppm.cpp)
target_link_libraries(oingo-ppm PUBLIC oingo-math)

add_library(oingo-options STATIC options.cpp)
target_link_libraries(oingo-options PRIVATE oingo-math oingo-scene)

add_library(oingo-logging INTERFACE)
target_include_directories(oingo-logging INTERFACE ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(cameras)
add_subdirectory(integrators)
add_subdirectory(lights)
add_subdirectory(materials)
add_subdirectory(math)
add_subdirectory(scene)
add_subdirectory(shapes)