#
# Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
#
# Permission is hereby granted, free of charge, to any
# person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the
# Software without restriction, including without
# limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software
# is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice
# shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
# ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
# SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
# IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#

# Set the cmake minimum version to 3.14
cmake_minimum_required(VERSION 3.14)

# Define the project name
project(sdl2-pointerless)

# Add SDL3 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add all c source files under the src directory
file(GLOB SOURCES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>)


# Add SDL3 library
find_package(SDL3 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL3 "m" "pthread")
# Add SDL3_image library
#find_package(SDL3_image REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL3::Image)

# Add SDL3_ttf library
#find_package(SDL3_ttf REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL3::TTF)

# Add SDL3_net library
#find_package(SDL3_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL3::Net)

# Add SDL3_mixer library
#find_package(SDL3_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL3::Mixer)

# Add SDL3_gfx library
#find_package(SDL3_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL3::GFX)

