cmake_minimum_required(VERSION 3.15)
project(MDV VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Full static linking
set(CMAKE_EXE_LINKER_FLAGS "-static")

# Use static wxWidgets
set(wxWidgets_CONFIG_OPTIONS --static)
find_package(wxWidgets REQUIRED COMPONENTS core base adv richtext html xml)
include(${wxWidgets_USE_FILE})

# Fetch md4c
include(FetchContent)
FetchContent_Declare(
    md4c
    GIT_REPOSITORY https://github.com/mity/md4c.git
    GIT_TAG        release-0.4.8
)
FetchContent_MakeAvailable(md4c)

# Add executable
add_executable(mdv WIN32
    src/main.cpp
    src/gui/MainWindow.cpp
    src/gui/SettingsDialog.cpp
    src/utils/FontManager.cpp
    src/markdown/MarkdownRenderer.cpp
)

# Include directories
target_include_directories(mdv PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/markdown
    ${md4c_SOURCE_DIR}/src
    ${md4c_BINARY_DIR}/src
)

# Add definitions
target_compile_definitions(mdv PRIVATE
    wxDEBUG_LEVEL=0
    WXWIN_COMPATIBILITY_2_8=0
    MD4C_USE_UTF8
)

# Link libraries
target_link_libraries(mdv PRIVATE
    ${wxWidgets_LIBRARIES}
    dwmapi
    uxtheme
    md4c
    md4c-html
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

# Copy fonts directory to build directory
add_custom_command(TARGET mdv POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/fonts
    $<TARGET_FILE_DIR:mdv>/fonts
)