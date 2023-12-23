//===--- RawSpeedTidyModule.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <clang-tidy/ClangTidy.h>
#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

#include "HelloWorldCheck.h"

using namespace clang::ast_matchers;

namespace clang::tidy {
namespace rawspeed {

/// This module is for RawSpeed-specific checks.
class RawSpeedModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<HelloWorldCheck>("rawspeed-hello-world");
  }
};

// Register the RawSpeedTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<RawSpeedModule>
    X("rawspeed-module", "Adds RawSpeed custom checks.");
} // namespace rawspeed

// This anchor is used to force the linker to link in the generated object file
// and thus register the RawSpeedModule.
volatile int RawSpeedModuleAnchorSource = 0;

} // namespace clang::tidy
