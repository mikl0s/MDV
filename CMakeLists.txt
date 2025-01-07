cmake_minimum_required(VERSION 3.15)

# Project configuration
project(MDV VERSION 0.0.1 LANGUAGES CXX)

# Set C++17 as standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Windows-specific settings
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_definitions(-DWIN32_LEAN_AND_MEAN)
add_definitions(-DUNICODE -D_UNICODE)  # Unicode support

# Include FetchContent for dependencies
include(FetchContent)

# Fetch FLTK 1.4.1
FetchContent_Declare(
    fltk
    GIT_REPOSITORY https://github.com/fltk/fltk
    GIT_TAG release-1.4.1
    GIT_SHALLOW TRUE
)

# Configure FLTK options
set(FLTK_BUILD_TEST OFF CACHE BOOL "")
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL "")
set(OPTION_USE_SYSTEM_LIBJPEG OFF CACHE BOOL "")
set(OPTION_USE_SYSTEM_LIBPNG OFF CACHE BOOL "")
set(OPTION_USE_SYSTEM_ZLIB OFF CACHE BOOL "")

# Make FLTK available
FetchContent_MakeAvailable(fltk)

# Fetch md4c
FetchContent_Declare(
    md4c
    GIT_REPOSITORY https://github.com/mity/md4c
    GIT_TAG release-0.4.8
    GIT_SHALLOW TRUE
)

# Configure md4c options
set(MD4C_BUILD_TESTS OFF CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")

# Make md4c available
FetchContent_MakeAvailable(md4c)

# Fetch libharu (PDF generation)
FetchContent_Declare(
    libharu
    GIT_REPOSITORY https://github.com/libharu/libharu
    GIT_TAG master
    GIT_SHALLOW TRUE
)

# Configure libharu options
set(LIBHARU_STATIC ON CACHE BOOL "")
set(LIBHARU_EXAMPLES OFF CACHE BOOL "")
set(LIBHARU_TESTS OFF CACHE BOOL "")

# Make dependencies available
FetchContent_MakeAvailable(libharu)

# Add source directories
add_subdirectory(src)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Set output name to mdv.exe for all configurations
set_target_properties(mdv PROPERTIES
    OUTPUT_NAME "mdv"
    SUFFIX ".exe"
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"  # Static runtime
)

# Install rules
install(DIRECTORY ${CMAKE_SOURCE_DIR}/fonts DESTINATION share/mdv)
install(TARGETS mdv 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
