# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

find_package(Python3 COMPONENTS Interpreter REQUIRED)

# HUH?
set(LLVM_DEFAULT_EXTERNAL_LIT "${LLVM_DIR}/../../../build/utils/lit/lit.py")

if(NOT DEFINED CLANG_TIDY_ENABLE_STATIC_ANALYZER)
  set(CLANG_TIDY_ENABLE_STATIC_ANALYZER False)
endif()

if(NOT DEFINED CLANG_PLUGIN_SUPPORT)
  set(CLANG_PLUGIN_SUPPORT False)
endif()

if(NOT DEFINED LLVM_INSTALL_TOOLCHAIN_ONLY)
  set(LLVM_INSTALL_TOOLCHAIN_ONLY False)
endif()

set(CLANG_TOOLS_SOURCE_DIR "${CMAKE_SOURCE_DIR}")

set(CLANG_TOOLS_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR "${CMAKE_BINARY_DIR}")

configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.py.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg.py
  MAIN_CONFIG
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.cfg.py
)

add_lit_testsuite(check "Running tests"
  ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${CLANG_TOOLS_TEST_DEPS}
)

add_test(NAME check COMMAND "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" -- check)
