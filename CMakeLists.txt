cmake_minimum_required(VERSION 3.16)
project(VulkanTriangle LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

qt_standard_project_setup()

qt_add_executable(VulkanTriangle
    RenderWindow.cpp RenderWindow.h
    main.cpp
)

# Define the shader files
set(SHADER_FILES
    color.frag
    color.vert
)

# Add the shader files to the project
add_custom_target(Shaders
    SOURCES ${SHADER_FILES}
)

set_target_properties(VulkanTriangle PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(VulkanTriangle PRIVATE
    Qt6::Core
    Qt6::Gui
)

# Resources:
set_source_files_properties("color_frag.spv"
    PROPERTIES QT_RESOURCE_ALIAS "color_frag.spv"
)

set_source_files_properties("color_vert.spv"
    PROPERTIES QT_RESOURCE_ALIAS "color_vert.spv"
)

set(VulkanTriangle_resource_files
    "color_frag.spv"
    "color_vert.spv"
)

qt_add_resources(VulkanTriangle "VulkanTriangle"
    PREFIX
        "/"
    FILES
        ${VulkanTriangle_resource_files}
)

install(TARGETS VulkanTriangle
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET VulkanTriangle
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
