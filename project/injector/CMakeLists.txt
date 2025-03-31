# Create the test executable
add_executable( injector WIN32 )

# First grab our source files so we can add it to the executable!
file( GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" )

# Add sources to the target
target_sources( injector PRIVATE ${SOURCE_FILES} )
