//===--- NoStdOptionalCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoStdOptionalCheck.h"
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

using namespace clang;
using namespace clang::ast_matchers;

namespace {

AST_MATCHER(clang::TypeLoc, hasValidBeginLoc) {
  return Node.getBeginLoc().isValid();
}

} // namespace

namespace clang::tidy::rawspeed {

NoStdOptionalCheck::NoStdOptionalCheck(StringRef Name,
                                       ClangTidyContext *Context)
    : ClangTidyCheck(Name, Context) {}

void NoStdOptionalCheck::registerMatchers(MatchFinder *Finder) {
  auto StdOptionalClass = cxxRecordDecl(isSameOrDerivedFrom(
      cxxRecordDecl(isInStdNamespace(), hasName("::std::optional"))));
  auto Matcher = elaboratedTypeLoc(
      hasValidBeginLoc(), loc(hasUnqualifiedDesugaredType(
                              recordType(hasDeclaration(StdOptionalClass)))));
  Finder->addMatcher(Matcher.bind("type"), this);
}

void NoStdOptionalCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *TL = Result.Nodes.getNodeAs<TypeLoc>("type");
  if (!TL)
    return;

  diag(TL->getBeginLoc(),
       "Do not use 'std::optional' directly, use 'Optional' wrapper")
      << TL->getSourceRange();
}

} // namespace clang::tidy::rawspeed
