# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.28
cmake_policy(SET CMP0009 NEW)

# SRC_FILES at CMakeLists.txt:11 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/sehwanahn/atmega128_workspace/atmega128a/*.c")
set(OLD_GLOB
  "/home/sehwanahn/atmega128_workspace/atmega128a/main.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/sehwanahn/atmega128_workspace/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES at CMakeLists.txt:11 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/sehwanahn/atmega128_workspace/atmega128a/*.cpp")
set(OLD_GLOB
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/sehwanahn/atmega128_workspace/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES_RECURSE at CMakeLists.txt:17 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/sehwanahn/atmega128_workspace/atmega128a/src/*.c")
set(OLD_GLOB
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/ap.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/RGB.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/btn.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/buzz.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/sensor.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/stepMotor.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/time.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/uart1.c"
  "/home/sehwanahn/atmega128_workspace/atmega128a/src/driver/ultrasonic_int.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/sehwanahn/atmega128_workspace/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES_RECURSE at CMakeLists.txt:17 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/sehwanahn/atmega128_workspace/atmega128a/src/*.cpp")
set(OLD_GLOB
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/sehwanahn/atmega128_workspace/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()
