add_library(oingo-render STATIC simple_sampler.cpp simple_sampler.hpp renderer.hpp ppm.hpp)
target_include_directories(oingo-render PRIVATE ${PROJECT_SOURCE_DIR}/src/render)
target_link_libraries(oingo-render PUBLIC Oingo::Scene Oingo::Film)
add_library(Oingo::Render ALIAS oingo-render)