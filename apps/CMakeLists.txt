add_executable(ray-tracer ray_tracer.cpp)
target_link_libraries(ray-tracer PRIVATE Oingo::Integrators Oingo::Options Oingo::Logging Oingo::PPM)