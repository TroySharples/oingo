add_library(oingo-cameras STATIC digital.cpp pinhole.cpp film.cpp)
target_include_directories(oingo-cameras PRIVATE ${PROJECT_SOURCE_DIR}/src/cameras)
target_link_libraries(oingo-cameras PUBLIC oingo-common)