add_library(oingo-common INTERFACE)

target_include_directories(oingo-common INTERFACE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(oingo-common INTERFACE Oingo::Math)

add_library(Oingo::Common ALIAS oingo-common)

add_subdirectory(math)
add_subdirectory(logging)
add_subdirectory(utility)
add_subdirectory(objects)