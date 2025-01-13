cmake_minimum_required(VERSION 3.15)
project(MDV VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set static linking
set(FLTK_USE_STATIC ON)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

# Find FLTK package
find_package(FLTK REQUIRED)

# Add executable
add_executable(mdv
    src/main.cpp
    src/gui/MainWindow.cpp
)

# Include directories
target_include_directories(mdv PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${FLTK_INCLUDE_DIR}
)

# Link libraries statically
target_link_libraries(mdv PRIVATE
    -static
    ${FLTK_LIBRARIES}
    gdi32
    comdlg32
    oleaut32
    ole32
    uuid
    shell32
    advapi32
    opengl32
    gdiplus
)

# Windows specific settings
if(WIN32)
    target_link_libraries(mdv PRIVATE
        ws2_32
        comctl32
        ole32
    )
    
    # Set Windows subsystem
    set_target_properties(mdv PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Installation rules
install(TARGETS mdv
    RUNTIME DESTINATION bin
)