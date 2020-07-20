cmake_minimum_required(VERSION 3.16)
project(Ray-Tracer VERSION 0.1)

################ Standard Project Settings
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # useful for clang tools

################ Prevent builds in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed.")
endif()

################ compiler flags
add_library(my_compiler_flags INTERFACE)

# add language standard (e.g. C++20) to my_compiler_flags
target_compile_features(my_compiler_flags INTERFACE cxx_std_20)

################ Warnings
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" TRUE)

set(MSVC_WARNINGS
  /W4 # Baseline reasonable warnings
  /w14242 # 'identifier': conversion from 'type1' to 'type1', possible loss
  # of data
  /w14254 # 'operator': conversion from 'type1:field_bits' to
  # 'type2:field_bits', possible loss of data
  /w14263 # 'function': member function does not override any base class
  # virtual member function
  /w14265 # 'classname': class has virtual functions, but destructor is not
  # virtual instances of this class may not be destructed correctly
  /w14287 # 'operator': unsigned/negative constant mismatch
  /we4289 # nonstandard extension used: 'variable': loop control variable
  # declared in the for-loop is used outside the for-loop scope
  /w14296 # 'operator': expression is always 'boolean_value'
  /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
  /w14545 # expression before comma evaluates to a function which is missing
  # an argument list
  /w14546 # function call before comma missing argument list
  /w14547 # 'operator': operator before comma has no effect; expected
  # operator with side-effect
  /w14549 # 'operator': operator before comma has no effect; did you intend
  # 'operator'?
  /w14555 # expression has no effect; expected expression with side- effect
  /w14619 # pragma warning: there is no warning number 'number'
  /w14640 # Enable warning on thread un-safe static member initialization
  /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may
  # cause unexpected runtime behavior.
  /w14905 # wide string literal cast to 'LPSTR'
  /w14906 # string literal cast to 'LPWSTR'
  /w14928 # illegal copy-initialization; more than one user-defined
  # conversion has been implicitly applied
  /permissive- # standards conformance mode for MSVC compiler.
  )

set(CLANG_WARNINGS
  -Wall
  -Wextra # reasonable and standard
  -Wshadow # warn the user if a variable declaration shadows one from a
  # parent context
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
  # non-virtual destructor. This helps catch hard to
  # track down memory errors
  -Wold-style-cast # warn for c-style casts
  -Wcast-align # warn for potential performance problem casts
  -Wunused # warn on anything being unused
  -Woverloaded-virtual # warn if you overload (not override) a virtual
  # function
  -Wpedantic # warn if non-standard C++ is used
  -Wconversion # warn on type conversions that may lose data
  -Wsign-conversion # warn on sign conversions
  -Wnull-dereference # warn if a null dereference is detected
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wformat=2 # warn on security issues around functions that format output
  # (ie printf)
  )

if (WARNINGS_AS_ERRORS)
  set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
  set(MSVC_WARNINGS ${MSVC_WARNINGS} -WX)
endif()

set(GCC_WARNINGS
  ${CLANG_WARNINGS}
  -Wmisleading-indentation # warn if indentation implies blocks where blocks
  # do not exist
  -Wduplicated-cond # warn if if / else chain has duplicated conditions
  -Wduplicated-branches # warn if if / else branches have duplicated code
  -Wlogical-op # warn about logical operations being used where bitwise were
  # probably wanted
  -Wuseless-cast # warn if you perform a cast to the same type
  )


# see https://github.com/Kitware/CMake/blob/master/Help/guide/tutorial/Complete/CMakeLists.txt

set(gcc_cxx "$<COMPILE_LANG_AND_ID:CXX,GNU>")
set(clang_cxx "$<COMPILE_LANG_AND_ID:CXX,CLANG>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(my_compiler_flags INTERFACE
  "$<${gcc_cxx}:${GCC_WARNINGS}>"
  "$<${clang_cxx}:${CLANG_WARNINGS}>"
  "$<${msvc_cxx}:${MSVC_WARNINGS}>"
  )

################ Clang specific time tracing

if ($<CXX_COMPILER_ID:AppleClang,Clang>)
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if (ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(my_compiler_flags INTERFACE -ftime-trace)
  endif()
endif()

################ Compiler cache system

# TODO see Jason Turner's CMake config

################ Sanitizers

# TODO see Jason Turner's CMake config

################ Doxygen

option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" OFF)
if(ENABLE_DOXYGEN)
  set(DOXYGEN_CALLER_GRAPH YES)
  set(DOXYGEN_CALL_GRAPH YES)
  set(DOXYGEN_EXTRACT_ALL YES)
  find_package(Doxygen REQUIRED dot)
  doxygen_add_docs(doxygen-docs ${PROJECT_SOURCE_DIR})
endif()

################ Static Analysis

option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)

if(ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --suppress=missingInclude --enable=all
                           --inline-suppr --inconclusive -i ${CMAKE_SOURCE_DIR}/imgui/lib)
  else()
    message(SEND_ERROR "cppcheck requested but executable not found")
  endif()
endif()

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
  else()
    message(SEND_ERROR "clang-tidy requested but executable not found")
  endif()
endif()

if(ENABLE_INCLUDE_WHAT_YOU_USE)
  find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
  if(INCLUDE_WHAT_YOU_USE)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
  else()
    message(SEND_ERROR "include-what-you-use requested but executable not found")
  endif()
endif()

################ Dependencies

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

find_package(docopt.cpp)
find_package(fmt)
find_package(spdlog)
find_package(doctest REQUIRED)

################ Testing

add_executable(ray-tests test/tests.cpp)
target_compile_features(ray-tests PRIVATE cxx_std_20)
target_link_libraries(ray-tests PRIVATE raylib doctest::doctest)

# TODO fuzz testing

################ The Program

include_directories(${PROJECT_SOURCE_DIR}/src)
set(SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/factorial.cpp
  ${PROJECT_SOURCE_DIR}/src/geometry.cpp
  )
add_library(raylib ${SOURCE_FILES})
target_link_libraries(raylib my_compiler_flags docopt.cpp::docopt.cpp fmt::fmt spdlog::spdlog)

add_executable(ray ${SOURCE_FILES})
target_link_libraries(ray my_compiler_flags raylib docopt.cpp::docopt.cpp fmt::fmt spdlog::spdlog)
