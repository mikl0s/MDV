cmake_minimum_required(VERSION 3.15)
project(MDV VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set static linking
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Add executable
add_executable(mdv WIN32
    src/main.cpp
    src/gui/MainWindow.cpp
)

# Include directories
target_include_directories(mdv PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Add definitions
add_definitions(-DwxDEBUG_LEVEL=0)
add_definitions(-DWXWIN_COMPATIBILITY_2_8=0)
add_definitions(-DwxUSE_PNG=0)

# Link libraries
target_link_libraries(mdv PRIVATE
    ${wxWidgets_LIBRARIES}
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