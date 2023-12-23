# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required(VERSION 3.25)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(RawSpeedClangTidyModule VERSION 17 LANGUAGES C CXX)

include(FeatureSummary)
include(GNUInstallDirs)

if((NOT (CMAKE_C_COMPILER_ID STREQUAL "Clang" AND CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 17 AND CMAKE_C_COMPILER_VERSION VERSION_LESS 18)) OR
   (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 17 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18)))
  message(SEND_ERROR "LLVM Clang compiler version 17 is required.")
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL Release)
  message(WARNING "Overriding CMAKE_BUILD_TYPE to Release!")
  set(CMAKE_BUILD_TYPE "Release" CACHE BOOL "build type" FORCE)
endif()

if(NOT BUILD_SHARED_LIBS)
  message(WARNING "Overriding BUILD_SHARED_LIBS to ON!")
  set(BUILD_SHARED_LIBS ON CACHE BOOL "create shared libraries" FORCE)
endif()

find_package(Clang 17.0.0...<18.0.0 REQUIRED CONFIG)

include(${LLVM_DIR}/AddLLVM.cmake)
include(${Clang_DIR}/AddClang.cmake)

add_subdirectory(src)

feature_summary(WHAT ALL)
