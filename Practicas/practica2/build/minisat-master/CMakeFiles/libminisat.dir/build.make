# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/a820506/APD/Practicas/practica2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/a820506/APD/Practicas/practica2/build

# Include any dependencies generated for this target.
include minisat-master/CMakeFiles/libminisat.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include minisat-master/CMakeFiles/libminisat.dir/compiler_depend.make

# Include the progress variables for this target.
include minisat-master/CMakeFiles/libminisat.dir/progress.make

# Include the compile flags for this target's objects.
include minisat-master/CMakeFiles/libminisat.dir/flags.make

minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o: minisat-master/CMakeFiles/libminisat.dir/flags.make
minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o: ../minisat-master/minisat/core/OutOfMemoryException.cc
minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o: minisat-master/CMakeFiles/libminisat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o -MF CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o.d -o CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o -c /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/OutOfMemoryException.cc

minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.i"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/OutOfMemoryException.cc > CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.i

minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.s"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/OutOfMemoryException.cc -o CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.s

minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o: minisat-master/CMakeFiles/libminisat.dir/flags.make
minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o: ../minisat-master/minisat/core/Solver.cc
minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o: minisat-master/CMakeFiles/libminisat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o -MF CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o.d -o CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o -c /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/Solver.cc

minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libminisat.dir/minisat/core/Solver.cc.i"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/Solver.cc > CMakeFiles/libminisat.dir/minisat/core/Solver.cc.i

minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libminisat.dir/minisat/core/Solver.cc.s"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/Solver.cc -o CMakeFiles/libminisat.dir/minisat/core/Solver.cc.s

minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o: minisat-master/CMakeFiles/libminisat.dir/flags.make
minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o: ../minisat-master/minisat/core/SolverTypes.cc
minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o: minisat-master/CMakeFiles/libminisat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o -MF CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o.d -o CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o -c /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/SolverTypes.cc

minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.i"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/SolverTypes.cc > CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.i

minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.s"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/SolverTypes.cc -o CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.s

minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o: minisat-master/CMakeFiles/libminisat.dir/flags.make
minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o: ../minisat-master/minisat/core/ThrowOOMException.cc
minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o: minisat-master/CMakeFiles/libminisat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o -MF CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o.d -o CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o -c /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/ThrowOOMException.cc

minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.i"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/ThrowOOMException.cc > CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.i

minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.s"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a820506/APD/Practicas/practica2/minisat-master/minisat/core/ThrowOOMException.cc -o CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.s

minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o: minisat-master/CMakeFiles/libminisat.dir/flags.make
minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o: ../minisat-master/minisat/utils/Options.cc
minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o: minisat-master/CMakeFiles/libminisat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o -MF CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o.d -o CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o -c /home/a820506/APD/Practicas/practica2/minisat-master/minisat/utils/Options.cc

minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libminisat.dir/minisat/utils/Options.cc.i"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a820506/APD/Practicas/practica2/minisat-master/minisat/utils/Options.cc > CMakeFiles/libminisat.dir/minisat/utils/Options.cc.i

minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libminisat.dir/minisat/utils/Options.cc.s"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a820506/APD/Practicas/practica2/minisat-master/minisat/utils/Options.cc -o CMakeFiles/libminisat.dir/minisat/utils/Options.cc.s

minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.o: minisat-master/CMakeFiles/libminisat.dir/flags.make
minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.o: ../minisat-master/minisat/utils/System.cc
minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.o: minisat-master/CMakeFiles/libminisat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.o"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.o -MF CMakeFiles/libminisat.dir/minisat/utils/System.cc.o.d -o CMakeFiles/libminisat.dir/minisat/utils/System.cc.o -c /home/a820506/APD/Practicas/practica2/minisat-master/minisat/utils/System.cc

minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libminisat.dir/minisat/utils/System.cc.i"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a820506/APD/Practicas/practica2/minisat-master/minisat/utils/System.cc > CMakeFiles/libminisat.dir/minisat/utils/System.cc.i

minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libminisat.dir/minisat/utils/System.cc.s"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a820506/APD/Practicas/practica2/minisat-master/minisat/utils/System.cc -o CMakeFiles/libminisat.dir/minisat/utils/System.cc.s

minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o: minisat-master/CMakeFiles/libminisat.dir/flags.make
minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o: ../minisat-master/minisat/simp/SimpSolver.cc
minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o: minisat-master/CMakeFiles/libminisat.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o -MF CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o.d -o CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o -c /home/a820506/APD/Practicas/practica2/minisat-master/minisat/simp/SimpSolver.cc

minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.i"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a820506/APD/Practicas/practica2/minisat-master/minisat/simp/SimpSolver.cc > CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.i

minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.s"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && /usr/local/gcc/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a820506/APD/Practicas/practica2/minisat-master/minisat/simp/SimpSolver.cc -o CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.s

# Object files for target libminisat
libminisat_OBJECTS = \
"CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o" \
"CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o" \
"CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o" \
"CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o" \
"CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o" \
"CMakeFiles/libminisat.dir/minisat/utils/System.cc.o" \
"CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o"

# External object files for target libminisat
libminisat_EXTERNAL_OBJECTS =

minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/minisat/core/OutOfMemoryException.cc.o
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/minisat/core/Solver.cc.o
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/minisat/core/SolverTypes.cc.o
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/minisat/core/ThrowOOMException.cc.o
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/minisat/utils/Options.cc.o
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/minisat/utils/System.cc.o
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/minisat/simp/SimpSolver.cc.o
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/build.make
minisat-master/libminisat.a: minisat-master/CMakeFiles/libminisat.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/a820506/APD/Practicas/practica2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libminisat.a"
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && $(CMAKE_COMMAND) -P CMakeFiles/libminisat.dir/cmake_clean_target.cmake
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libminisat.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
minisat-master/CMakeFiles/libminisat.dir/build: minisat-master/libminisat.a
.PHONY : minisat-master/CMakeFiles/libminisat.dir/build

minisat-master/CMakeFiles/libminisat.dir/clean:
	cd /home/a820506/APD/Practicas/practica2/build/minisat-master && $(CMAKE_COMMAND) -P CMakeFiles/libminisat.dir/cmake_clean.cmake
.PHONY : minisat-master/CMakeFiles/libminisat.dir/clean

minisat-master/CMakeFiles/libminisat.dir/depend:
	cd /home/a820506/APD/Practicas/practica2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/a820506/APD/Practicas/practica2 /home/a820506/APD/Practicas/practica2/minisat-master /home/a820506/APD/Practicas/practica2/build /home/a820506/APD/Practicas/practica2/build/minisat-master /home/a820506/APD/Practicas/practica2/build/minisat-master/CMakeFiles/libminisat.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : minisat-master/CMakeFiles/libminisat.dir/depend

