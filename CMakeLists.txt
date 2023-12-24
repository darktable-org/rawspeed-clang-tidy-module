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

enable_testing()

add_subdirectory(src)
add_subdirectory(test)

feature_summary(WHAT ALL)

configure_file("${CMAKE_SOURCE_DIR}/clang-tidy.in"
               "${CMAKE_BINARY_DIR}/clang-tidy.in" @ONLY)

file(GENERATE
     OUTPUT "${CMAKE_BINARY_DIR}/clang-tidy"
     INPUT  "${CMAKE_BINARY_DIR}/clang-tidy.in"
     USE_SOURCE_PERMISSIONS)

#-------------------------------------------------------------------------------

set(generated_dir "${PROJECT_BINARY_DIR}")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_to_export clangTidyRawSpeedModule)
set(targets_export_name "${PROJECT_NAME}Targets")

set(namespace "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
  ${project_config}
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${version_config}" VERSION ${GENERIC_LIB_VERSION} COMPATIBILITY SameMajorVersion
)

export(TARGETS ${targets_to_export}
       NAMESPACE "${namespace}"
       FILE ${generated_dir}/${targets_export_name}.cmake)

install(TARGETS ${targets_to_export}
        EXPORT ${targets_export_name}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES "${project_config}" "${version_config}"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

install(EXPORT "${targets_export_name}"
        NAMESPACE "${namespace}"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
