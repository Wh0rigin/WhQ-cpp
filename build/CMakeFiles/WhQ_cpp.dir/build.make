# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hsensei/myfile/WhQ-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hsensei/myfile/WhQ-cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/WhQ_cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WhQ_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WhQ_cpp.dir/flags.make

CMakeFiles/WhQ_cpp.dir/src/Server.cpp.o: CMakeFiles/WhQ_cpp.dir/flags.make
CMakeFiles/WhQ_cpp.dir/src/Server.cpp.o: ../src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsensei/myfile/WhQ-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WhQ_cpp.dir/src/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WhQ_cpp.dir/src/Server.cpp.o -c /home/hsensei/myfile/WhQ-cpp/src/Server.cpp

CMakeFiles/WhQ_cpp.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WhQ_cpp.dir/src/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsensei/myfile/WhQ-cpp/src/Server.cpp > CMakeFiles/WhQ_cpp.dir/src/Server.cpp.i

CMakeFiles/WhQ_cpp.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WhQ_cpp.dir/src/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsensei/myfile/WhQ-cpp/src/Server.cpp -o CMakeFiles/WhQ_cpp.dir/src/Server.cpp.s

# Object files for target WhQ_cpp
WhQ_cpp_OBJECTS = \
"CMakeFiles/WhQ_cpp.dir/src/Server.cpp.o"

# External object files for target WhQ_cpp
WhQ_cpp_EXTERNAL_OBJECTS =

libWhQ_cpp.a: CMakeFiles/WhQ_cpp.dir/src/Server.cpp.o
libWhQ_cpp.a: CMakeFiles/WhQ_cpp.dir/build.make
libWhQ_cpp.a: CMakeFiles/WhQ_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hsensei/myfile/WhQ-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libWhQ_cpp.a"
	$(CMAKE_COMMAND) -P CMakeFiles/WhQ_cpp.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WhQ_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WhQ_cpp.dir/build: libWhQ_cpp.a

.PHONY : CMakeFiles/WhQ_cpp.dir/build

CMakeFiles/WhQ_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WhQ_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WhQ_cpp.dir/clean

CMakeFiles/WhQ_cpp.dir/depend:
	cd /home/hsensei/myfile/WhQ-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hsensei/myfile/WhQ-cpp /home/hsensei/myfile/WhQ-cpp /home/hsensei/myfile/WhQ-cpp/build /home/hsensei/myfile/WhQ-cpp/build /home/hsensei/myfile/WhQ-cpp/build/CMakeFiles/WhQ_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WhQ_cpp.dir/depend

