# CMakeLists.txt for linked_list tests
file(GLOB LL_TEST_SOURCES "*.c")

# Process each linked list test file
foreach(test_src ${LL_TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})

    # Add both src directory and include directory to include paths
    target_include_directories(${test_name} PRIVATE 
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
    )

    target_link_libraries(${test_name} PRIVATE azkaban-core)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
