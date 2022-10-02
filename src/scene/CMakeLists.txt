add_library(oingo-scene INTERFACE)

target_link_libraries(oingo-scene INTERFACE Oingo::Objects)

add_library(Oingo::Scene ALIAS oingo-scene)