# Create the test executable
add_library( mod SHARED )

# First grab our source files so we can add it to the executable!
file( GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp" )

# Add sources to the target
target_sources( mod PRIVATE ${SOURCE_FILES} )

# Find our packages
find_package( minhook CONFIG REQUIRED )

# Link against the library
target_link_libraries( mod PRIVATE minhook::minhook )