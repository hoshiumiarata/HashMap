find_package(CMOCKA REQUIRED)
include_directories(${CMOCKA_INCLUDE_DIR})

add_executable(hashmap_test hashmap_test.c)
add_test(hashmap_test hashmap_test)
target_link_libraries(hashmap_test hashmap ${CMOCKA_LIBRARIES})