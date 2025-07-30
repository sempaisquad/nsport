cmake_minimum_required(VERSION 3.5)
project(NetSurf)

# Enable Carbon support
set(CMAKE_OSX_ARCHITECTURES "ppc")
set(TARGET_API_MAC_CARBON 1)

# Add Carbon framework
find_library(CARBON_FRAMEWORK Carbon)
find_library(TOOLBOX_FRAMEWORK ToolboxEssentials)

# NetSurf source files
set(NETSURF_SOURCES
    src/main.c
    src/gui.c
    src/window.c
    src/bitmap.c
    src/fetch.c
    src/schedule.c
    src/misc.c
    src/layout.c
    src/utf8.c
    src/file.c
    src/download.c
    src/clipboard.c
    src/search.c
    src/local_history.c
    src/plotters.c
    src/font.c
)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libnetsurf/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libcss/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libdom/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libhubbub/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libparserutils/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libwapcaplet/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libnsgif/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libnsbmp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libnsutils/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libsvgtiny/include
)

# Create the NetSurf executable
add_executable(NetSurf ${NETSURF_SOURCES})

# Link libraries
target_link_libraries(NetSurf 
    ${CARBON_FRAMEWORK}
    ${TOOLBOX_FRAMEWORK}
    netsurf
    css
    dom
    hubbub
    parserutils
    wapcaplet
    nsgif
    nsbmp
    nsutils
    svgtiny
)

# Set compiler flags for Mac OS 9 compatibility
target_compile_definitions(NetSurf PRIVATE
    TARGET_API_MAC_CARBON=1
    NETSURF_MACOS9=1
    NSLOG_LEVEL=NSLOG_LEVEL_INFO
)
