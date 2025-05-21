# CMakeLists.txt for linked_list tests
file(GLOB LL_TEST_SOURCES "*.c")

# Process each linked list test file
foreach(test_src ${LL_TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})

		# Add src directory to include paths for test targets only
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/src)

    target_link_libraries(${test_name} PRIVATE azkaban-core)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Optional: Add a custom target to run all linked list tests
# add_custom_target(run_all_ll_tests
#     COMMAND ${CMAKE_CTEST_COMMAND} -R "test_fnLinkedList*"
#     COMMENT "Running all linked list tests"
# )
