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
CMAKE_SOURCE_DIR = /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build

# Include any dependencies generated for this target.
include IOTServer/CMakeFiles/IOTServer.dir/depend.make

# Include the progress variables for this target.
include IOTServer/CMakeFiles/IOTServer.dir/progress.make

# Include the compile flags for this target's objects.
include IOTServer/CMakeFiles/IOTServer.dir/flags.make

IOTServer/CMakeFiles/IOTServer.dir/main.cpp.o: IOTServer/CMakeFiles/IOTServer.dir/flags.make
IOTServer/CMakeFiles/IOTServer.dir/main.cpp.o: ../IOTServer/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object IOTServer/CMakeFiles/IOTServer.dir/main.cpp.o"
	cd /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/IOTServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IOTServer.dir/main.cpp.o -c /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/IOTServer/main.cpp

IOTServer/CMakeFiles/IOTServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IOTServer.dir/main.cpp.i"
	cd /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/IOTServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/IOTServer/main.cpp > CMakeFiles/IOTServer.dir/main.cpp.i

IOTServer/CMakeFiles/IOTServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IOTServer.dir/main.cpp.s"
	cd /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/IOTServer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/IOTServer/main.cpp -o CMakeFiles/IOTServer.dir/main.cpp.s

# Object files for target IOTServer
IOTServer_OBJECTS = \
"CMakeFiles/IOTServer.dir/main.cpp.o"

# External object files for target IOTServer
IOTServer_EXTERNAL_OBJECTS =

IOTServer/IOTServer: IOTServer/CMakeFiles/IOTServer.dir/main.cpp.o
IOTServer/IOTServer: IOTServer/CMakeFiles/IOTServer.dir/build.make
IOTServer/IOTServer: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.71.0
IOTServer/IOTServer: IOTServer/CMakeFiles/IOTServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IOTServer"
	cd /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/IOTServer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IOTServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
IOTServer/CMakeFiles/IOTServer.dir/build: IOTServer/IOTServer

.PHONY : IOTServer/CMakeFiles/IOTServer.dir/build

IOTServer/CMakeFiles/IOTServer.dir/clean:
	cd /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/IOTServer && $(CMAKE_COMMAND) -P CMakeFiles/IOTServer.dir/cmake_clean.cmake
.PHONY : IOTServer/CMakeFiles/IOTServer.dir/clean

IOTServer/CMakeFiles/IOTServer.dir/depend:
	cd /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/IOTServer /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/IOTServer /home/ks/Desktop/gitRepos/ESP32TemperaturSensorDHT22/LinuxServer/build/IOTServer/CMakeFiles/IOTServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : IOTServer/CMakeFiles/IOTServer.dir/depend

