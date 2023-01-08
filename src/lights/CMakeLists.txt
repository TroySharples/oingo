add_library(oingo-lights INTERFACE)
target_link_libraries(oingo-lights INTERFACE Oingo::Common)
add_library(Oingo::Lights ALIAS oingo-lights)