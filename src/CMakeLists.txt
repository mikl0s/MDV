# Collect all source files
file(GLOB_RECURSE SOURCES
    "*.cpp"
    "*.hpp"
)

# Create executable
add_executable(mdv ${SOURCES})

# Link with dependencies
target_link_libraries(mdv PRIVATE
    fltk
    fltk_gl
    libcmark-gfm
    hpdf
    CURL::libcurl
)

# Include directories
target_include_directories(mdv PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
    ${CMAKE_CURRENT_SOURCE_DIR}/markdown
    ${CMAKE_CURRENT_SOURCE_DIR}/pdf
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# Set properties for Windows
if(WIN32)
    set_target_properties(mdv PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()