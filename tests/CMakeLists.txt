add_test(NAME sphere    COMMAND ray-tracer -f png -o ${CMAKE_SOURCE_DIR}/renders/test-sphere.png    -r 1920x1080 -s sphere)
add_test(NAME 4k-sphere COMMAND ray-tracer -f png -o ${CMAKE_SOURCE_DIR}/renders/test-4k-sphere.png -r 3840x2160 -s sphere)
add_test(NAME cylinders COMMAND ray-tracer -f png -o ${CMAKE_SOURCE_DIR}/renders/test-cylinders.png -r 1920x1080 -s cylinders)