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
include cloud_libs/CMakeFiles/gest_module.dir/depend.make

# Include the progress variables for this target.
include cloud_libs/CMakeFiles/gest_module.dir/progress.make

# Include the compile flags for this target's objects.
include cloud_libs/CMakeFiles/gest_module.dir/flags.make

cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o: cloud_libs/CMakeFiles/gest_module.dir/flags.make
cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o: ../cloud_libs/gest_module.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mosca/Dropbox/Code/modular_system/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/gest_module.dir/gest_module.c.o   -c /home/mosca/Dropbox/Code/modular_system/cloud_libs/gest_module.c

cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gest_module.dir/gest_module.c.i"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/mosca/Dropbox/Code/modular_system/cloud_libs/gest_module.c > CMakeFiles/gest_module.dir/gest_module.c.i

cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gest_module.dir/gest_module.c.s"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/mosca/Dropbox/Code/modular_system/cloud_libs/gest_module.c -o CMakeFiles/gest_module.dir/gest_module.c.s

cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.requires:
.PHONY : cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.requires

cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.provides: cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.requires
	$(MAKE) -f cloud_libs/CMakeFiles/gest_module.dir/build.make cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.provides.build
.PHONY : cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.provides

cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.provides.build: cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o

# Object files for target gest_module
gest_module_OBJECTS = \
"CMakeFiles/gest_module.dir/gest_module.c.o"

# External object files for target gest_module
gest_module_EXTERNAL_OBJECTS =

cloud_libs/libgest_module.so: cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o
cloud_libs/libgest_module.so: cloud_libs/CMakeFiles/gest_module.dir/build.make
cloud_libs/libgest_module.so: cloud_libs/CMakeFiles/gest_module.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libgest_module.so"
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gest_module.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cloud_libs/CMakeFiles/gest_module.dir/build: cloud_libs/libgest_module.so
.PHONY : cloud_libs/CMakeFiles/gest_module.dir/build

cloud_libs/CMakeFiles/gest_module.dir/requires: cloud_libs/CMakeFiles/gest_module.dir/gest_module.c.o.requires
.PHONY : cloud_libs/CMakeFiles/gest_module.dir/requires

cloud_libs/CMakeFiles/gest_module.dir/clean:
	cd /home/mosca/Dropbox/Code/modular_system/build/cloud_libs && $(CMAKE_COMMAND) -P CMakeFiles/gest_module.dir/cmake_clean.cmake
.PHONY : cloud_libs/CMakeFiles/gest_module.dir/clean

cloud_libs/CMakeFiles/gest_module.dir/depend:
	cd /home/mosca/Dropbox/Code/modular_system/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mosca/Dropbox/Code/modular_system /home/mosca/Dropbox/Code/modular_system/cloud_libs /home/mosca/Dropbox/Code/modular_system/build /home/mosca/Dropbox/Code/modular_system/build/cloud_libs /home/mosca/Dropbox/Code/modular_system/build/cloud_libs/CMakeFiles/gest_module.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cloud_libs/CMakeFiles/gest_module.dir/depend
