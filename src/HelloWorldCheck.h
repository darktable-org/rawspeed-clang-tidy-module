//===--- HelloWorldCheck.h - clang-tidy -------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_RAWSPEED_HELLOWORLD_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_RAWSPEED_HELLOWORLD_H

#include <clang-tidy/ClangTidyCheck.h>

namespace clang::tidy::rawspeed {

/// Hello world check.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/rawspeed/hello-world.html
class HelloWorldCheck : public ClangTidyCheck {
public:
  HelloWorldCheck(StringRef Name, ClangTidyContext *Context);
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;

  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace clang::tidy::rawspeed

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_RAWSPEED_HELLOWORLD_H
