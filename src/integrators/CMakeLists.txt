add_library(oingo-integrators STATIC simple_sampler.cpp simple_sampler.hpp integrator.hpp)
target_include_directories(oingo-integrators PRIVATE ${PROJECT_SOURCE_DIR}/src/integrators)
target_link_libraries(oingo-integrators PUBLIC Oingo::Scene Oingo::PPM)
add_library(Oingo::Integrators ALIAS oingo-integrators)