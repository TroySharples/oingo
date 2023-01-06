add_library(oingo-scene INTERFACE)
target_link_libraries(oingo-scene INTERFACE Oingo::Objects Oingo::Cameras)
add_library(Oingo::Scene ALIAS oingo-scene)