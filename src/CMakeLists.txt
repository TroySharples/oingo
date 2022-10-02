add_library(oingo-common INTERFACE)
target_link_libraries(oingo-common INTERFACE Oingo::Math)
add_library(Oingo::Common ALIAS oingo-common)

add_library(oingo-film STATIC film.cpp film.hpp)
target_link_libraries(oingo-film PUBLIC Oingo::Math)
add_library(Oingo::Film ALIAS oingo-film)

add_subdirectory(math)
add_subdirectory(objects)
add_subdirectory(scene)
add_subdirectory(render)
add_subdirectory(cameras)