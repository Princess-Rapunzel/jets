# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Ariel\anaconda3\Library\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Ariel\anaconda3\Library\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ariel\Desktop\jets-main

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ariel\Desktop\jets-main\build

# Include any dependencies generated for this target.
include test/test1/CMakeFiles/test1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/test1/CMakeFiles/test1.dir/compiler_depend.make

# Include the progress variables for this target.
include test/test1/CMakeFiles/test1.dir/progress.make

# Include the compile flags for this target's objects.
include test/test1/CMakeFiles/test1.dir/flags.make

test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj: test/test1/CMakeFiles/test1.dir/flags.make
test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj: test/test1/CMakeFiles/test1.dir/includes_CXX.rsp
test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj: C:/Users/Ariel/Desktop/jets-main/src/common/getpot.C
test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj: test/test1/CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ariel\Desktop\jets-main\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj -MF CMakeFiles\test1.dir\__\__\src\common\getpot.C.obj.d -o CMakeFiles\test1.dir\__\__\src\common\getpot.C.obj -c C:\Users\Ariel\Desktop\jets-main\src\common\getpot.C

test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/__/__/src/common/getpot.C.i"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ariel\Desktop\jets-main\src\common\getpot.C > CMakeFiles\test1.dir\__\__\src\common\getpot.C.i

test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/__/__/src/common/getpot.C.s"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ariel\Desktop\jets-main\src\common\getpot.C -o CMakeFiles\test1.dir\__\__\src\common\getpot.C.s

test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.obj: test/test1/CMakeFiles/test1.dir/flags.make
test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.obj: test/test1/CMakeFiles/test1.dir/includes_CXX.rsp
test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.obj: C:/Users/Ariel/Desktop/jets-main/src/common/jets.C
test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.obj: test/test1/CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ariel\Desktop\jets-main\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.obj"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.obj -MF CMakeFiles\test1.dir\__\__\src\common\jets.C.obj.d -o CMakeFiles\test1.dir\__\__\src\common\jets.C.obj -c C:\Users\Ariel\Desktop\jets-main\src\common\jets.C

test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/__/__/src/common/jets.C.i"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ariel\Desktop\jets-main\src\common\jets.C > CMakeFiles\test1.dir\__\__\src\common\jets.C.i

test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/__/__/src/common/jets.C.s"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ariel\Desktop\jets-main\src\common\jets.C -o CMakeFiles\test1.dir\__\__\src\common\jets.C.s

test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj: test/test1/CMakeFiles/test1.dir/flags.make
test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj: test/test1/CMakeFiles/test1.dir/includes_CXX.rsp
test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj: C:/Users/Ariel/Desktop/jets-main/src/common/jetscomm.C
test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj: test/test1/CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ariel\Desktop\jets-main\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj -MF CMakeFiles\test1.dir\__\__\src\common\jetscomm.C.obj.d -o CMakeFiles\test1.dir\__\__\src\common\jetscomm.C.obj -c C:\Users\Ariel\Desktop\jets-main\src\common\jetscomm.C

test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.i"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ariel\Desktop\jets-main\src\common\jetscomm.C > CMakeFiles\test1.dir\__\__\src\common\jetscomm.C.i

test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.s"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ariel\Desktop\jets-main\src\common\jetscomm.C -o CMakeFiles\test1.dir\__\__\src\common\jetscomm.C.s

test/test1/CMakeFiles/test1.dir/test1.C.obj: test/test1/CMakeFiles/test1.dir/flags.make
test/test1/CMakeFiles/test1.dir/test1.C.obj: test/test1/CMakeFiles/test1.dir/includes_CXX.rsp
test/test1/CMakeFiles/test1.dir/test1.C.obj: C:/Users/Ariel/Desktop/jets-main/test/test1/test1.C
test/test1/CMakeFiles/test1.dir/test1.C.obj: test/test1/CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ariel\Desktop\jets-main\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object test/test1/CMakeFiles/test1.dir/test1.C.obj"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/test1/CMakeFiles/test1.dir/test1.C.obj -MF CMakeFiles\test1.dir\test1.C.obj.d -o CMakeFiles\test1.dir\test1.C.obj -c C:\Users\Ariel\Desktop\jets-main\test\test1\test1.C

test/test1/CMakeFiles/test1.dir/test1.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/test1.C.i"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ariel\Desktop\jets-main\test\test1\test1.C > CMakeFiles\test1.dir\test1.C.i

test/test1/CMakeFiles/test1.dir/test1.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/test1.C.s"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ariel\Desktop\jets-main\test\test1\test1.C -o CMakeFiles\test1.dir\test1.C.s

test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj: test/test1/CMakeFiles/test1.dir/flags.make
test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj: test/test1/CMakeFiles/test1.dir/includes_CXX.rsp
test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj: C:/Users/Ariel/Desktop/jets-main/src/spacial/dof_obj.C
test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj: test/test1/CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ariel\Desktop\jets-main\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj -MF CMakeFiles\test1.dir\__\__\src\spacial\dof_obj.C.obj.d -o CMakeFiles\test1.dir\__\__\src\spacial\dof_obj.C.obj -c C:\Users\Ariel\Desktop\jets-main\src\spacial\dof_obj.C

test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.i"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ariel\Desktop\jets-main\src\spacial\dof_obj.C > CMakeFiles\test1.dir\__\__\src\spacial\dof_obj.C.i

test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.s"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ariel\Desktop\jets-main\src\spacial\dof_obj.C -o CMakeFiles\test1.dir\__\__\src\spacial\dof_obj.C.s

test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj: test/test1/CMakeFiles/test1.dir/flags.make
test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj: test/test1/CMakeFiles/test1.dir/includes_CXX.rsp
test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj: C:/Users/Ariel/Desktop/jets-main/src/spacial/ponit.C
test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj: test/test1/CMakeFiles/test1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ariel\Desktop\jets-main\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj -MF CMakeFiles\test1.dir\__\__\src\spacial\ponit.C.obj.d -o CMakeFiles\test1.dir\__\__\src\spacial\ponit.C.obj -c C:\Users\Ariel\Desktop\jets-main\src\spacial\ponit.C

test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.i"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ariel\Desktop\jets-main\src\spacial\ponit.C > CMakeFiles\test1.dir\__\__\src\spacial\ponit.C.i

test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.s"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ariel\Desktop\jets-main\src\spacial\ponit.C -o CMakeFiles\test1.dir\__\__\src\spacial\ponit.C.s

# Object files for target test1
test1_OBJECTS = \
"CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj" \
"CMakeFiles/test1.dir/__/__/src/common/jets.C.obj" \
"CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj" \
"CMakeFiles/test1.dir/test1.C.obj" \
"CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj" \
"CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj"

# External object files for target test1
test1_EXTERNAL_OBJECTS =

C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/__/__/src/common/getpot.C.obj
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/__/__/src/common/jets.C.obj
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/__/__/src/common/jetscomm.C.obj
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/test1.C.obj
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/__/__/src/spacial/dof_obj.C.obj
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/__/__/src/spacial/ponit.C.obj
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/build.make
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/linkLibs.rsp
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/objects1.rsp
C:/Users/Ariel/Desktop/jets-main/bin/test1.exe: test/test1/CMakeFiles/test1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ariel\Desktop\jets-main\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable C:\Users\Ariel\Desktop\jets-main\bin\test1.exe"
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/test1/CMakeFiles/test1.dir/build: C:/Users/Ariel/Desktop/jets-main/bin/test1.exe
.PHONY : test/test1/CMakeFiles/test1.dir/build

test/test1/CMakeFiles/test1.dir/clean:
	cd /d C:\Users\Ariel\Desktop\jets-main\build\test\test1 && $(CMAKE_COMMAND) -P CMakeFiles\test1.dir\cmake_clean.cmake
.PHONY : test/test1/CMakeFiles/test1.dir/clean

test/test1/CMakeFiles/test1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ariel\Desktop\jets-main C:\Users\Ariel\Desktop\jets-main\test\test1 C:\Users\Ariel\Desktop\jets-main\build C:\Users\Ariel\Desktop\jets-main\build\test\test1 C:\Users\Ariel\Desktop\jets-main\build\test\test1\CMakeFiles\test1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : test/test1/CMakeFiles/test1.dir/depend

