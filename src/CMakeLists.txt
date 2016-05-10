# Add include directory

include_directories(../include)



# Find all the *.cpp files

file(GLOB SRCS *.cpp)



# Make the executable based on all the .cpp files.

add_executable(RobbyTheRobot ${SRCS})

# Tell cmake to use OpenCV. This is untested for now. Uncomment next line if using OpenCV.
# This line found: http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_gcc_cmake/linux_gcc_cmake.html
target_link_libraries( RobbyTheRobot ${OpenCV_LIBS} )



# Build the executable in /bin

# Use this by typing cmake install.

install(TARGETS RobbyTheRobot DESTINATION ${CMAKE_BINARY_DIR}/../bin)
