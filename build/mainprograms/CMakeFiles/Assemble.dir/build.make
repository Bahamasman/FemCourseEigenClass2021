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
CMAKE_SOURCE_DIR = /home/marcolopes/programacao/FemCourseEigenClass2021

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcolopes/programacao/FemCourseEigenClass2021/build

# Include any dependencies generated for this target.
include mainprograms/CMakeFiles/Assemble.dir/depend.make

# Include the progress variables for this target.
include mainprograms/CMakeFiles/Assemble.dir/progress.make

# Include the compile flags for this target's objects.
include mainprograms/CMakeFiles/Assemble.dir/flags.make

mainprograms/CMakeFiles/Assemble.dir/mainAssemble.cpp.o: mainprograms/CMakeFiles/Assemble.dir/flags.make
mainprograms/CMakeFiles/Assemble.dir/mainAssemble.cpp.o: ../mainprograms/mainAssemble.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcolopes/programacao/FemCourseEigenClass2021/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object mainprograms/CMakeFiles/Assemble.dir/mainAssemble.cpp.o"
	cd /home/marcolopes/programacao/FemCourseEigenClass2021/build/mainprograms && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Assemble.dir/mainAssemble.cpp.o -c /home/marcolopes/programacao/FemCourseEigenClass2021/mainprograms/mainAssemble.cpp

mainprograms/CMakeFiles/Assemble.dir/mainAssemble.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assemble.dir/mainAssemble.cpp.i"
	cd /home/marcolopes/programacao/FemCourseEigenClass2021/build/mainprograms && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcolopes/programacao/FemCourseEigenClass2021/mainprograms/mainAssemble.cpp > CMakeFiles/Assemble.dir/mainAssemble.cpp.i

mainprograms/CMakeFiles/Assemble.dir/mainAssemble.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assemble.dir/mainAssemble.cpp.s"
	cd /home/marcolopes/programacao/FemCourseEigenClass2021/build/mainprograms && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcolopes/programacao/FemCourseEigenClass2021/mainprograms/mainAssemble.cpp -o CMakeFiles/Assemble.dir/mainAssemble.cpp.s

# Object files for target Assemble
Assemble_OBJECTS = \
"CMakeFiles/Assemble.dir/mainAssemble.cpp.o"

# External object files for target Assemble
Assemble_EXTERNAL_OBJECTS =

mainprograms/Assemble: mainprograms/CMakeFiles/Assemble.dir/mainAssemble.cpp.o
mainprograms/Assemble: mainprograms/CMakeFiles/Assemble.dir/build.make
mainprograms/Assemble: mainprograms/libcourse_library.a
mainprograms/Assemble: mainprograms/CMakeFiles/Assemble.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcolopes/programacao/FemCourseEigenClass2021/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Assemble"
	cd /home/marcolopes/programacao/FemCourseEigenClass2021/build/mainprograms && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assemble.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mainprograms/CMakeFiles/Assemble.dir/build: mainprograms/Assemble

.PHONY : mainprograms/CMakeFiles/Assemble.dir/build

mainprograms/CMakeFiles/Assemble.dir/clean:
	cd /home/marcolopes/programacao/FemCourseEigenClass2021/build/mainprograms && $(CMAKE_COMMAND) -P CMakeFiles/Assemble.dir/cmake_clean.cmake
.PHONY : mainprograms/CMakeFiles/Assemble.dir/clean

mainprograms/CMakeFiles/Assemble.dir/depend:
	cd /home/marcolopes/programacao/FemCourseEigenClass2021/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcolopes/programacao/FemCourseEigenClass2021 /home/marcolopes/programacao/FemCourseEigenClass2021/mainprograms /home/marcolopes/programacao/FemCourseEigenClass2021/build /home/marcolopes/programacao/FemCourseEigenClass2021/build/mainprograms /home/marcolopes/programacao/FemCourseEigenClass2021/build/mainprograms/CMakeFiles/Assemble.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mainprograms/CMakeFiles/Assemble.dir/depend

