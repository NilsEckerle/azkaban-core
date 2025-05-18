set(TEST_SOURCES
    # test_another_feature.c
)

# Add the linked_list subdirectory for individual tests
add_subdirectory(linked_list)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE azkaban-core)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
