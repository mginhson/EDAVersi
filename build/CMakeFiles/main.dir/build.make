# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mginhson/Desktop/EDA/EDAVersi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mginhson/Desktop/EDA/EDAVersi/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: ../main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mginhson/Desktop/EDA/EDAVersi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /home/mginhson/Desktop/EDA/EDAVersi/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mginhson/Desktop/EDA/EDAVersi/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mginhson/Desktop/EDA/EDAVersi/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/model.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/model.cpp.o: ../model.cpp
CMakeFiles/main.dir/model.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mginhson/Desktop/EDA/EDAVersi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/model.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/model.cpp.o -MF CMakeFiles/main.dir/model.cpp.o.d -o CMakeFiles/main.dir/model.cpp.o -c /home/mginhson/Desktop/EDA/EDAVersi/model.cpp

CMakeFiles/main.dir/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mginhson/Desktop/EDA/EDAVersi/model.cpp > CMakeFiles/main.dir/model.cpp.i

CMakeFiles/main.dir/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mginhson/Desktop/EDA/EDAVersi/model.cpp -o CMakeFiles/main.dir/model.cpp.s

CMakeFiles/main.dir/view.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/view.cpp.o: ../view.cpp
CMakeFiles/main.dir/view.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mginhson/Desktop/EDA/EDAVersi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/view.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/view.cpp.o -MF CMakeFiles/main.dir/view.cpp.o.d -o CMakeFiles/main.dir/view.cpp.o -c /home/mginhson/Desktop/EDA/EDAVersi/view.cpp

CMakeFiles/main.dir/view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/view.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mginhson/Desktop/EDA/EDAVersi/view.cpp > CMakeFiles/main.dir/view.cpp.i

CMakeFiles/main.dir/view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/view.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mginhson/Desktop/EDA/EDAVersi/view.cpp -o CMakeFiles/main.dir/view.cpp.s

CMakeFiles/main.dir/controller.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/controller.cpp.o: ../controller.cpp
CMakeFiles/main.dir/controller.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mginhson/Desktop/EDA/EDAVersi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/controller.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/controller.cpp.o -MF CMakeFiles/main.dir/controller.cpp.o.d -o CMakeFiles/main.dir/controller.cpp.o -c /home/mginhson/Desktop/EDA/EDAVersi/controller.cpp

CMakeFiles/main.dir/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mginhson/Desktop/EDA/EDAVersi/controller.cpp > CMakeFiles/main.dir/controller.cpp.i

CMakeFiles/main.dir/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mginhson/Desktop/EDA/EDAVersi/controller.cpp -o CMakeFiles/main.dir/controller.cpp.s

CMakeFiles/main.dir/ai.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/ai.cpp.o: ../ai.cpp
CMakeFiles/main.dir/ai.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mginhson/Desktop/EDA/EDAVersi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/ai.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/ai.cpp.o -MF CMakeFiles/main.dir/ai.cpp.o.d -o CMakeFiles/main.dir/ai.cpp.o -c /home/mginhson/Desktop/EDA/EDAVersi/ai.cpp

CMakeFiles/main.dir/ai.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/ai.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mginhson/Desktop/EDA/EDAVersi/ai.cpp > CMakeFiles/main.dir/ai.cpp.i

CMakeFiles/main.dir/ai.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/ai.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mginhson/Desktop/EDA/EDAVersi/ai.cpp -o CMakeFiles/main.dir/ai.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/model.cpp.o" \
"CMakeFiles/main.dir/view.cpp.o" \
"CMakeFiles/main.dir/controller.cpp.o" \
"CMakeFiles/main.dir/ai.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/model.cpp.o
main: CMakeFiles/main.dir/view.cpp.o
main: CMakeFiles/main.dir/controller.cpp.o
main: CMakeFiles/main.dir/ai.cpp.o
main: CMakeFiles/main.dir/build.make
main: /home/mginhson/dev/vcpkg/installed/x64-linux/debug/lib/libraylib.a
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mginhson/Desktop/EDA/EDAVersi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/mginhson/Desktop/EDA/EDAVersi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mginhson/Desktop/EDA/EDAVersi /home/mginhson/Desktop/EDA/EDAVersi /home/mginhson/Desktop/EDA/EDAVersi/build /home/mginhson/Desktop/EDA/EDAVersi/build /home/mginhson/Desktop/EDA/EDAVersi/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

