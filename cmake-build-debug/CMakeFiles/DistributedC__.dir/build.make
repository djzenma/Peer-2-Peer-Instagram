# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/DistributedC__.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DistributedC__.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DistributedC__.dir/flags.make

CMakeFiles/DistributedC__.dir/src/Client.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/Client.cpp.o: ../src/Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DistributedC__.dir/src/Client.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/Client.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Client.cpp"

CMakeFiles/DistributedC__.dir/src/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/Client.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Client.cpp" > CMakeFiles/DistributedC__.dir/src/Client.cpp.i

CMakeFiles/DistributedC__.dir/src/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/Client.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Client.cpp" -o CMakeFiles/DistributedC__.dir/src/Client.cpp.s

CMakeFiles/DistributedC__.dir/src/Message.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/Message.cpp.o: ../src/Message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/DistributedC__.dir/src/Message.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/Message.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Message.cpp"

CMakeFiles/DistributedC__.dir/src/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/Message.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Message.cpp" > CMakeFiles/DistributedC__.dir/src/Message.cpp.i

CMakeFiles/DistributedC__.dir/src/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/Message.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Message.cpp" -o CMakeFiles/DistributedC__.dir/src/Message.cpp.s

CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.o: ../src/RequestReply.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/RequestReply.cpp"

CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/RequestReply.cpp" > CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.i

CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/RequestReply.cpp" -o CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.s

CMakeFiles/DistributedC__.dir/src/Server.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/Server.cpp.o: ../src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/DistributedC__.dir/src/Server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/Server.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Server.cpp"

CMakeFiles/DistributedC__.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/Server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Server.cpp" > CMakeFiles/DistributedC__.dir/src/Server.cpp.i

CMakeFiles/DistributedC__.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/Server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/Server.cpp" -o CMakeFiles/DistributedC__.dir/src/Server.cpp.s

CMakeFiles/DistributedC__.dir/src/utils.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/utils.cpp.o: ../src/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/DistributedC__.dir/src/utils.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/utils.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/utils.cpp"

CMakeFiles/DistributedC__.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/utils.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/utils.cpp" > CMakeFiles/DistributedC__.dir/src/utils.cpp.i

CMakeFiles/DistributedC__.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/utils.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/utils.cpp" -o CMakeFiles/DistributedC__.dir/src/utils.cpp.s

CMakeFiles/DistributedC__.dir/src/main.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/DistributedC__.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/main.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/main.cpp"

CMakeFiles/DistributedC__.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/main.cpp" > CMakeFiles/DistributedC__.dir/src/main.cpp.i

CMakeFiles/DistributedC__.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/main.cpp" -o CMakeFiles/DistributedC__.dir/src/main.cpp.s

CMakeFiles/DistributedC__.dir/src/base64.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/base64.cpp.o: ../src/base64.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/DistributedC__.dir/src/base64.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/base64.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/base64.cpp"

CMakeFiles/DistributedC__.dir/src/base64.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/base64.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/base64.cpp" > CMakeFiles/DistributedC__.dir/src/base64.cpp.i

CMakeFiles/DistributedC__.dir/src/base64.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/base64.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/base64.cpp" -o CMakeFiles/DistributedC__.dir/src/base64.cpp.s

CMakeFiles/DistributedC__.dir/src/experiment.cpp.o: CMakeFiles/DistributedC__.dir/flags.make
CMakeFiles/DistributedC__.dir/src/experiment.cpp.o: ../src/experiment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/DistributedC__.dir/src/experiment.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DistributedC__.dir/src/experiment.cpp.o -c "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/experiment.cpp"

CMakeFiles/DistributedC__.dir/src/experiment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DistributedC__.dir/src/experiment.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/experiment.cpp" > CMakeFiles/DistributedC__.dir/src/experiment.cpp.i

CMakeFiles/DistributedC__.dir/src/experiment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DistributedC__.dir/src/experiment.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/src/experiment.cpp" -o CMakeFiles/DistributedC__.dir/src/experiment.cpp.s

# Object files for target DistributedC__
DistributedC___OBJECTS = \
"CMakeFiles/DistributedC__.dir/src/Client.cpp.o" \
"CMakeFiles/DistributedC__.dir/src/Message.cpp.o" \
"CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.o" \
"CMakeFiles/DistributedC__.dir/src/Server.cpp.o" \
"CMakeFiles/DistributedC__.dir/src/utils.cpp.o" \
"CMakeFiles/DistributedC__.dir/src/main.cpp.o" \
"CMakeFiles/DistributedC__.dir/src/base64.cpp.o" \
"CMakeFiles/DistributedC__.dir/src/experiment.cpp.o"

# External object files for target DistributedC__
DistributedC___EXTERNAL_OBJECTS =

DistributedC__: CMakeFiles/DistributedC__.dir/src/Client.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/src/Message.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/src/RequestReply.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/src/Server.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/src/utils.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/src/main.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/src/base64.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/src/experiment.cpp.o
DistributedC__: CMakeFiles/DistributedC__.dir/build.make
DistributedC__: CMakeFiles/DistributedC__.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable DistributedC__"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DistributedC__.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DistributedC__.dir/build: DistributedC__

.PHONY : CMakeFiles/DistributedC__.dir/build

CMakeFiles/DistributedC__.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DistributedC__.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DistributedC__.dir/clean

CMakeFiles/DistributedC__.dir/depend:
	cd "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM" "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM" "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug" "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug" "/Users/owner/CLionProjects/Distributed-Server 2.13.57 AM/cmake-build-debug/CMakeFiles/DistributedC__.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/DistributedC__.dir/depend
