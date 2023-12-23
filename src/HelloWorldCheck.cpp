//===--- HelloWorldCheck.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "HelloWorldCheck.h"
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

using namespace clang::ast_matchers;

namespace clang::tidy::rawspeed {

HelloWorldCheck::HelloWorldCheck(StringRef Name, ClangTidyContext *Context)
    : ClangTidyCheck(Name, Context) {}

void HelloWorldCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(namespaceDecl().bind("namespace"), this);
}

void HelloWorldCheck::check(const MatchFinder::MatchResult &Result) {
  if (const auto *D = Result.Nodes.getNodeAs<NamespaceDecl>("namespace"))
    diag(D->getLocation(), "Hello world!");
}

} // namespace clang::tidy::rawspeed
