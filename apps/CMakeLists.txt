add_executable(ray-tracer ray_tracer.cpp)
target_link_libraries(ray-tracer PRIVATE oingo-integrators oingo-utils oingo-assimp oingo-embree)