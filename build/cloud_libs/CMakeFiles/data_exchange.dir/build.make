# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mosca/Dropbox/Code/modular_system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mosca/Dropbox/Code/modular_system/build

# Include any dependencies generated for this target.
include cloud_libs/CMakeFiles/data_exchange.dir/depend.make

# Include the progress variables for this target.
include cloud_libs/CMakeFiles/data_exchange.dir/progress.make

# Include the compile flags for this target's objects.
include cloud_libs/CMakeFiles/data_exchange.dir/flags.make

cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o: cloud_libs/CMakeFiles/data_exchange.dir/flags.make
cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o: ../cloud_libs/data_exchange.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mosca/Dropbox/Code/modular_system/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/data_exchange.dir/data_exchange.c.o   -c /home/mosca/Dropbox/Code/modular_system/cloud_libs/data_exchange.c

cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/data_exchange.dir/data_exchange.c.i"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/mosca/Dropbox/Code/modular_system/cloud_libs/data_exchange.c > CMakeFiles/data_exchange.dir/data_exchange.c.i

cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/data_exchange.dir/data_exchange.c.s"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/mosca/Dropbox/Code/modular_system/cloud_libs/data_exchange.c -o CMakeFiles/data_exchange.dir/data_exchange.c.s

cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.requires:
.PHONY : cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.requires

cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.provides: cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.requires
	$(MAKE) -f cloud_libs/CMakeFiles/data_exchange.dir/build.make cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.provides.build
.PHONY : cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.provides

cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.provides.build: cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o

# Object files for target data_exchange
data_exchange_OBJECTS = \
"CMakeFiles/data_exchange.dir/data_exchange.c.o"

# External object files for target data_exchange
data_exchange_EXTERNAL_OBJECTS =

cloud_libs/libdata_exchange.so: cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o
cloud_libs/libdata_exchange.so: cloud_libs/CMakeFiles/data_exchange.dir/build.make
cloud_libs/libdata_exchange.so: cloud_libs/CMakeFiles/data_exchange.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libdata_exchange.so"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/data_exchange.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cloud_libs/CMakeFiles/data_exchange.dir/build: cloud_libs/libdata_exchange.so
.PHONY : cloud_libs/CMakeFiles/data_exchange.dir/build

cloud_libs/CMakeFiles/data_exchange.dir/requires: cloud_libs/CMakeFiles/data_exchange.dir/data_exchange.c.o.requires
.PHONY : cloud_libs/CMakeFiles/data_exchange.dir/requires

cloud_libs/CMakeFiles/data_exchange.dir/clean:
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && $(CMAKE_COMMAND) -P CMakeFiles/data_exchange.dir/cmake_clean.cmake
.PHONY : cloud_libs/CMakeFiles/data_exchange.dir/clean

cloud_libs/CMakeFiles/data_exchange.dir/depend:
	cd /home/mosca/Dropbox/Code/modular_system/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mosca/Dropbox/Code/modular_system /home/mosca/Dropbox/Code/modular_system/cloud_libs /home/mosca/Dropbox/Code/modular_system/build /home/mosca/Dropbox/Code/modular_system/build/cloud_libs /home/mosca/Dropbox/Code/modular_system/build/cloud_libs/CMakeFiles/data_exchange.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cloud_libs/CMakeFiles/data_exchange.dir/depend
