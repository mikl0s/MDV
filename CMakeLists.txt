cmake_minimum_required(VERSION 3.15)
project(MDV VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Full static linking
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Use static wxWidgets
set(wxWidgets_CONFIG_OPTIONS --static)
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
target_compile_definitions(mdv PRIVATE
    wxDEBUG_LEVEL=0
    WXWIN_COMPATIBILITY_2_8=0
)

# Link libraries
target_link_libraries(mdv PRIVATE
    ${wxWidgets_LIBRARIES}
)

# Windows specific settings
if(WIN32)
    set_target_properties(mdv PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Installation rules
install(TARGETS mdv
    RUNTIME DESTINATION bin
)