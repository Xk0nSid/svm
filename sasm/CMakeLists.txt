cmake_minimum_required(VERSION 2.6)
project(SASM)

# Setup color encoding for pretty outputs
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColorReset "${Esc}[m")
  set(ColorBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

message ("${BoldBlue}System Family${ColorReset} -> ${BoldYellow}${CMAKE_SYSTEM_NAME}${ColorReset}")

include (CheckCXXCompilerFlag)

# NOTE: If we are to actually use C++11 features, we should either require
#       a compiler that supports the -std=c++11 flag or check for the
#       features used.
#       Relying on -std=c++0x or even -std=gnu++0x is highly volatile.

CHECK_CXX_COMPILER_FLAG("-std=c++11" _HAS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" _HAS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-std=gnu++0x" _HAS_GNU0X)

if (_HAS_CXX11)
  set (_CXX11_FLAGS "-std=c++11")
elseif (_HAS_CXX0X)
  message (WARNING "Enabling -std=c++0x draft compile flag. Your compiler does not support the standard '-std=c++11' option.  Consider upgrading.")
  set (_CXX11_FLAGS "-std=c++0x")
elseif (_HAS_GNU0X)
  message (WARNING "Enabling -std=gnu++0x draft compile flag. Your compiler does not support the standard '-std=c++11' option. Consider upgrading.")
  set (_CXX11_FLAGS "-std=gnu++0x")
else (_HAS_CXX11)
 message (FATAL_ERROR "C++11 support missing. Try upgrading your C++ compiler. If you have a good reason for using an outdated compiler, please let us know at support@taskwarrior.org.")
endif (_HAS_CXX11)

SET (CMAKE_CXX_FLAGS "${_CXX11_FLAGS} ${CMAKE_CXX_FLAGS} -Wall -Werror")
SET (CMAKE_CXX_FLAGS_DEBUG "${_CXX11_FLAGS} ${CMAKE_CXX_FLAGS} -Wall -Werror -g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_FILES
    src/lexer.h
    src/lexer.cc
    src/main.cc)

add_executable(sasm ${SOURCE_FILES})
