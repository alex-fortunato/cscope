cmake_minimum_required(VERSION 3.22)
# Set to ON to generate compile_commands.json
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#
## After the project is configured, copy the compile_commands.json file
#if(CMAKE_EXPORT_COMPILE_COMMANDS)
#  execute_process(
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#      ${CMAKE_BINARY_DIR}/compile_commands.json
#      ${CMAKE_SOURCE_DIR}/compile_commands.json
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#    RESULT_VARIABLE copy_result
#  )
#  if(NOT copy_result EQUAL 0)
#    message(WARNING "Failed to copy compile_commands.json to source directory")
#  endif()
#endif()
#
#add_custom_target(copy-compile-commands ALL DEPENDS ${CMAKE_SOURCE_DIR}/compile_commands.json)



# JUCE STUFF:

project(cscope VERSION 1.1.0)
set(CMAKE_CXX_STANDARD 17)

# Use CPM to get JUCE
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
include(cmake/cpm.cmake)

CPMAddPackage(
        NAME JUCE
        GIT_TAG 8.0.6
        VERSION 8.0.6
        GITHUB_REPOSITORY juce-framework/JUCE
        SOURCE_DIR ${LIB_DIR}/juce
)



# Set up your plugin
juce_add_plugin(${CMAKE_PROJECT_NAME}
        VERSION 1.1.0
        FORMATS AU VST3 Standalone
        PRODUCT_NAME "cscope"
        COMPANY_NAME AlexFortunatoMusic

        IS_SYNTH FALSE                       # Is this a synth or an effect?
        NEEDS_MIDI_INPUT FALSE               # Does the plugin need midi input?
        NEEDS_MIDI_OUTPUT FALSE              # Does the plugin need midi output?
        IS_MIDI_EFFECT FALSE                 # Is this plugin a MIDI effect?
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE    # Does the editor need keyboard focus?
        COPY_PLUGIN_AFTER_BUILD TRUE         # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE Fort        # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE Cscp                  # A unique four-character plugin id with exactly one upper-case character
)

# Generate JuceHeader.h
juce_generate_juce_header(cscope)

juce_add_binary_data (BinaryData SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources/interface.html
)

# Add source files
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Resources/interface.html
        # Add other source files here
)

# Link to JUCE modules
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_gui_extra
        BinaryData
        # Add other modules as needed
)

# Add include directories for source and shared headers
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources
        #${CMAKE_BINARY_DIR}/cmake-build-debug/AudioSender_artefacts/JuceLibraryCode
        #${CMAKE_CURRENT_SOURCE_DIR}/libs/juce/modules
        #"/Users/alexanderfortunato/Development/JUCE/Shared Headers"
)

# These definitions are recommended by JUCE.
target_compile_definitions(${CMAKE_PROJECT_NAME}
        PUBLIC
        JUCE_WEB_BROWSER=1
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

# Copy resources to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
)
