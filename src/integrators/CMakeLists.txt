add_library(oingo-integrators STATIC simple_sampler.cpp)
target_include_directories(oingo-integrators PRIVATE ${PROJECT_SOURCE_DIR}/src/integrators)
target_link_libraries(oingo-integrators PUBLIC oingo-scene oingo-ppm)