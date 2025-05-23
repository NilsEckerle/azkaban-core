cmake_minimum_required(VERSION 3.14)
# Project name and version
project(azkaban-core VERSION 1.0.0 LANGUAGES C)

# Export compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" OFF)
option(USE_SYSTEM_SQLCIPHER "Use system-installed SQLCipher" OFF)

# Platform detection and setup
if(WIN32)
    set(PLATFORM_NAME "windows")
    add_definitions(-D_WIN32_WINNT=0x0601)  # Windows 7 minimum
elseif(APPLE)
    set(PLATFORM_NAME "macos")
elseif(UNIX)
    set(PLATFORM_NAME "linux")
endif()

message(STATUS "Building for platform: ${PLATFORM_NAME}")

# Find required packages based on platform
if(WIN32)
    find_package(OpenSSL REQUIRED)
elseif(UNIX AND NOT APPLE)
    find_package(OpenSSL REQUIRED)
endif()

# Handle SQLCipher
if(USE_SYSTEM_SQLCIPHER)
    # Use system SQLCipher
    find_library(SQLCIPHER_LIB sqlcipher REQUIRED)
    find_path(SQLCIPHER_INCLUDE sqlite3.h REQUIRED)
    
    add_library(sqlcipher INTERFACE)
    target_link_libraries(sqlcipher INTERFACE ${SQLCIPHER_LIB})
    target_include_directories(sqlcipher INTERFACE ${SQLCIPHER_INCLUDE})
else()
    # Use our prebuilt SQLCipher
    set(SQLCIPHER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third/sqlcipher)
    
    add_library(sqlcipher STATIC IMPORTED)
    set_target_properties(sqlcipher PROPERTIES
        IMPORTED_LOCATION ${SQLCIPHER_DIR}/lib/libsqlcipher.a
        INTERFACE_INCLUDE_DIRECTORIES ${SQLCIPHER_DIR}/include
    )
    
    # Platform-specific dependencies for SQLCipher
    if(WIN32)
        target_link_libraries(sqlcipher INTERFACE
            OpenSSL::SSL
            OpenSSL::Crypto
            ws2_32
        )
    elseif(APPLE)
        target_link_libraries(sqlcipher INTERFACE
            "-framework Security"
            "-framework Foundation"
        )
    elseif(UNIX)
        target_link_libraries(sqlcipher INTERFACE
            OpenSSL::SSL
            OpenSSL::Crypto
            pthread
            dl
            m
        )
    endif()
endif()

# Create the library (build own library)
add_library(azkaban-core
		src/linked_list.c
		src/database.c
		src/entry_repository.c
		src/entry_detail_repository.c
	)

# Set include directories for the library
target_include_directories(azkaban-core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries (Use third party libraries)
target_link_libraries(azkaban-core
    PRIVATE
        sqlcipher
)

# Platform-specific compile definitions
if(WIN32)
    target_compile_definitions(azkaban-core PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(azkaban-core PRIVATE PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(azkaban-core PRIVATE PLATFORM_LINUX)
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(azkaban-core PRIVATE /W4)
else()
    target_compile_options(azkaban-core PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Enable testing if requested
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Build examples if requested
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation rules (cross-platform)
include(GNUInstallDirs)

install(TARGETS azkaban-core
    EXPORT AzkabanCoreTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/azkaban-core
    FILES_MATCHING PATTERN "*.h"
)

# Export targets
install(EXPORT AzkabanCoreTargets
    FILE AzkabanCoreTargets.cmake
    NAMESPACE AzkabanCore::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AzkabanCore
)

# Package configuration files
include(CMakePackageConfigHelpers)

# Create version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/AzkabanCoreConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Create config file (you'll need to create this template)
configure_file(cmake/AzkabanCoreConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/AzkabanCoreConfig.cmake"
    @ONLY
)

# Install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/AzkabanCoreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/AzkabanCoreConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AzkabanCore
)
