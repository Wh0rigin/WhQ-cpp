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
CMAKE_SOURCE_DIR = /home/hsensei/myfile/WhQ-cpp/Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hsensei/myfile/WhQ-cpp/Client/build

# Include any dependencies generated for this target.
include CMakeFiles/WhQ_cpp_Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WhQ_cpp_Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WhQ_cpp_Client.dir/flags.make

CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.o: CMakeFiles/WhQ_cpp_Client.dir/flags.make
CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.o: ../src/Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsensei/myfile/WhQ-cpp/Client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.o -c /home/hsensei/myfile/WhQ-cpp/Client/src/Client.cpp

CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsensei/myfile/WhQ-cpp/Client/src/Client.cpp > CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.i

CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsensei/myfile/WhQ-cpp/Client/src/Client.cpp -o CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.s

CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.o: CMakeFiles/WhQ_cpp_Client.dir/flags.make
CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hsensei/myfile/WhQ-cpp/Client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.o -c /home/hsensei/myfile/WhQ-cpp/Client/src/main.cpp

CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hsensei/myfile/WhQ-cpp/Client/src/main.cpp > CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.i

CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hsensei/myfile/WhQ-cpp/Client/src/main.cpp -o CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.s

# Object files for target WhQ_cpp_Client
WhQ_cpp_Client_OBJECTS = \
"CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.o" \
"CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.o"

# External object files for target WhQ_cpp_Client
WhQ_cpp_Client_EXTERNAL_OBJECTS =

WhQ_cpp_Client: CMakeFiles/WhQ_cpp_Client.dir/src/Client.cpp.o
WhQ_cpp_Client: CMakeFiles/WhQ_cpp_Client.dir/src/main.cpp.o
WhQ_cpp_Client: CMakeFiles/WhQ_cpp_Client.dir/build.make
WhQ_cpp_Client: CMakeFiles/WhQ_cpp_Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hsensei/myfile/WhQ-cpp/Client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable WhQ_cpp_Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WhQ_cpp_Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WhQ_cpp_Client.dir/build: WhQ_cpp_Client

.PHONY : CMakeFiles/WhQ_cpp_Client.dir/build

CMakeFiles/WhQ_cpp_Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WhQ_cpp_Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WhQ_cpp_Client.dir/clean

CMakeFiles/WhQ_cpp_Client.dir/depend:
	cd /home/hsensei/myfile/WhQ-cpp/Client/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hsensei/myfile/WhQ-cpp/Client /home/hsensei/myfile/WhQ-cpp/Client /home/hsensei/myfile/WhQ-cpp/Client/build /home/hsensei/myfile/WhQ-cpp/Client/build /home/hsensei/myfile/WhQ-cpp/Client/build/CMakeFiles/WhQ_cpp_Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WhQ_cpp_Client.dir/depend
