# Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set(LLVM_LINK_COMPONENTS
  Support
  )

add_clang_library(clangTidyRawSpeedModule
  StdArrayNoOperatorAtCheck.cpp
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
