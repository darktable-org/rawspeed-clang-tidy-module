//===--- NoStdOptionalCheck.h - clang-tidy -------------00000000-*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_RAWSPEED_NOSTDOPTIONAL_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_RAWSPEED_NOSTDOPTIONAL_H

#include <clang-tidy/ClangTidyCheck.h>

namespace clang::tidy::rawspeed {

/// Do not use `std::optional<>` directly, use `rawspeed::Optional<>`.
class NoStdOptionalCheck : public ClangTidyCheck {
public:
  NoStdOptionalCheck(StringRef Name, ClangTidyContext *Context);
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;

  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace clang::tidy::rawspeed

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_RAWSPEED_NOSTDOPTIONAL_H
