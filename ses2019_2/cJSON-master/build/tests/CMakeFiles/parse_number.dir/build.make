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
CMAKE_SOURCE_DIR = /home/owner/Desktop/programming/ses2019_2/cJSON-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/owner/Desktop/programming/ses2019_2/cJSON-master/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/parse_number.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/parse_number.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/parse_number.dir/flags.make

tests/CMakeFiles/parse_number.dir/parse_number.c.o: tests/CMakeFiles/parse_number.dir/flags.make
tests/CMakeFiles/parse_number.dir/parse_number.c.o: ../tests/parse_number.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/owner/Desktop/programming/ses2019_2/cJSON-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/parse_number.dir/parse_number.c.o"
	cd /home/owner/Desktop/programming/ses2019_2/cJSON-master/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/parse_number.dir/parse_number.c.o   -c /home/owner/Desktop/programming/ses2019_2/cJSON-master/tests/parse_number.c

tests/CMakeFiles/parse_number.dir/parse_number.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parse_number.dir/parse_number.c.i"
	cd /home/owner/Desktop/programming/ses2019_2/cJSON-master/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/owner/Desktop/programming/ses2019_2/cJSON-master/tests/parse_number.c > CMakeFiles/parse_number.dir/parse_number.c.i

tests/CMakeFiles/parse_number.dir/parse_number.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parse_number.dir/parse_number.c.s"
	cd /home/owner/Desktop/programming/ses2019_2/cJSON-master/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/owner/Desktop/programming/ses2019_2/cJSON-master/tests/parse_number.c -o CMakeFiles/parse_number.dir/parse_number.c.s

# Object files for target parse_number
parse_number_OBJECTS = \
"CMakeFiles/parse_number.dir/parse_number.c.o"

# External object files for target parse_number
parse_number_EXTERNAL_OBJECTS =

tests/parse_number: tests/CMakeFiles/parse_number.dir/parse_number.c.o
tests/parse_number: tests/CMakeFiles/parse_number.dir/build.make
tests/parse_number: libcjson.so.1.7.14
tests/parse_number: tests/libunity.a
tests/parse_number: tests/CMakeFiles/parse_number.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/owner/Desktop/programming/ses2019_2/cJSON-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable parse_number"
	cd /home/owner/Desktop/programming/ses2019_2/cJSON-master/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parse_number.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/parse_number.dir/build: tests/parse_number

.PHONY : tests/CMakeFiles/parse_number.dir/build

tests/CMakeFiles/parse_number.dir/clean:
	cd /home/owner/Desktop/programming/ses2019_2/cJSON-master/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/parse_number.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/parse_number.dir/clean

tests/CMakeFiles/parse_number.dir/depend:
	cd /home/owner/Desktop/programming/ses2019_2/cJSON-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/owner/Desktop/programming/ses2019_2/cJSON-master /home/owner/Desktop/programming/ses2019_2/cJSON-master/tests /home/owner/Desktop/programming/ses2019_2/cJSON-master/build /home/owner/Desktop/programming/ses2019_2/cJSON-master/build/tests /home/owner/Desktop/programming/ses2019_2/cJSON-master/build/tests/CMakeFiles/parse_number.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/parse_number.dir/depend

