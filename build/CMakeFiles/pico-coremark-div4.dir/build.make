# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\rpi pico\dds"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\rpi pico\dds\build"

# Include any dependencies generated for this target.
include CMakeFiles/pico-coremark-div4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pico-coremark-div4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pico-coremark-div4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pico-coremark-div4.dir/flags.make

CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.obj: CMakeFiles/pico-coremark-div4.dir/flags.make
CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.obj: C:/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\rpi pico\dds\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.obj"
	C:\VSARM\armcc\102021~1.10\bin\AR19DD~1.EXE $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles\pico-coremark-div4.dir\C_\VSARM\sdk\pico\pico-sdk\src\rp2_common\boot_stage2\compile_time_choice.S.obj   -c C:\VSARM\sdk\pico\pico-sdk\src\rp2_common\boot_stage2\compile_time_choice.S

CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.i"
	C:\VSARM\armcc\102021~1.10\bin\AR19DD~1.EXE $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E C:\VSARM\sdk\pico\pico-sdk\src\rp2_common\boot_stage2\compile_time_choice.S > CMakeFiles\pico-coremark-div4.dir\C_\VSARM\sdk\pico\pico-sdk\src\rp2_common\boot_stage2\compile_time_choice.S.i

CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.s"
	C:\VSARM\armcc\102021~1.10\bin\AR19DD~1.EXE $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S C:\VSARM\sdk\pico\pico-sdk\src\rp2_common\boot_stage2\compile_time_choice.S -o CMakeFiles\pico-coremark-div4.dir\C_\VSARM\sdk\pico\pico-sdk\src\rp2_common\boot_stage2\compile_time_choice.S.s

# Object files for target pico-coremark-div4
pico__coremark__div4_OBJECTS = \
"CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.obj"

# External object files for target pico-coremark-div4
pico__coremark__div4_EXTERNAL_OBJECTS =

pico-coremark-div4.elf: CMakeFiles/pico-coremark-div4.dir/C_/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/compile_time_choice.S.obj
pico-coremark-div4.elf: CMakeFiles/pico-coremark-div4.dir/build.make
pico-coremark-div4.elf: C:/VSARM/sdk/pico/pico-sdk/src/rp2_common/boot_stage2/boot_stage2.ld
pico-coremark-div4.elf: CMakeFiles/pico-coremark-div4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\rpi pico\dds\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking ASM executable pico-coremark-div4.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pico-coremark-div4.dir\link.txt --verbose=$(VERBOSE)
	"C:\VSARM\armcc\10 2021.10\bin\arm-none-eabi-objdump.exe" -h "C:/rpi pico/dds/build/pico-coremark-div4.elf" >pico-coremark-div4.dis
	"C:\VSARM\armcc\10 2021.10\bin\arm-none-eabi-objdump.exe" -d "C:/rpi pico/dds/build/pico-coremark-div4.elf" >>pico-coremark-div4.dis

# Rule to build all files generated by this target.
CMakeFiles/pico-coremark-div4.dir/build: pico-coremark-div4.elf
.PHONY : CMakeFiles/pico-coremark-div4.dir/build

CMakeFiles/pico-coremark-div4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\pico-coremark-div4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/pico-coremark-div4.dir/clean

CMakeFiles/pico-coremark-div4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\rpi pico\dds" "C:\rpi pico\dds" "C:\rpi pico\dds\build" "C:\rpi pico\dds\build" "C:\rpi pico\dds\build\CMakeFiles\pico-coremark-div4.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/pico-coremark-div4.dir/depend

