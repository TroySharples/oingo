add_executable(ray-tracer ray_tracer.cpp)
target_link_libraries(ray-tracer PRIVATE Oingo::Render Oingo::Options Oingo::Test-Scenes)