# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_library(clangTidyRawSpeedModule
  HelloWorldCheck.cpp
  RawSpeedTidyModule.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils
  )

clang_target_link_libraries(clangTidyRawSpeedModule
  PRIVATE
  clangAST
  clangASTMatchers
  )

#-------------------------------------------------------------------------------

target_include_directories(clangTidyRawSpeedModule PRIVATE ${CLANG_INCLUDE_DIRS})

#-------------------------------------------------------------------------------

install(TARGETS clangTidyRawSpeedModule
        EXPORT  clangTidyRawSpeedModuleTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(EXPORT clangTidyRawSpeedModuleTargets
        FILE   clangTidyRawSpeedModuleTargets.cmake
        NAMESPACE clangTidyRawSpeedModule::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/clangTidyRawSpeedModule)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/clangTidyRawSpeedModuleConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/clangTidyRawSpeedModuleConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/clangTidyRawSpeedModule)

write_basic_package_version_file(
  "clangTidyRawSpeedModuleConfigVersion.cmake"
  VERSION ${clangTidyRawSpeedModule_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/clangTidyRawSpeedModuleConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/clangTidyRawSpeedModuleConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/clangTidyRawSpeedModule)
