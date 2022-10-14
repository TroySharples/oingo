add_executable(ray-tracer ray_tracer.cpp)
target_link_libraries(ray-tracer PRIVATE Oingo::Render Oingo::Options Oingo::Test-Scenes)

add_custom_target(ray-tracer-test
    COMMAND ray-tracer > test.png
    DEPENDS ray-tracer)