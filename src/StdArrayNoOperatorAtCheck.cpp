//===--- StdArrayNoOperatorAtCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "StdArrayNoOperatorAtCheck.h"
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

using namespace clang;
using namespace clang::ast_matchers;

namespace {

AST_MATCHER(CXXMethodDecl, isSubscriptOperator) {
  return Node.getOverloadedOperator() == OO_Subscript;
}

AST_MATCHER_P(CXXOperatorCallExpr, onObjectArgument,
              clang::ast_matchers::internal::Matcher<Expr>, InnerMatcher) {
  const Expr *const Object = Node.getArg(0);
  return (Object != nullptr && InnerMatcher.matches(*Object, Finder, Builder));
}

}; // namespace

namespace clang::tidy::rawspeed {

StdArrayNoOperatorAtCheck::StdArrayNoOperatorAtCheck(StringRef Name,
                                                     ClangTidyContext *Context)
    : ClangTidyCheck(Name, Context) {}

void StdArrayNoOperatorAtCheck::registerMatchers(MatchFinder *Finder) {
  auto ArrayClass = isSameOrDerivedFrom(cxxRecordDecl(hasName("::std::array")));
  auto SugaredClass = hasType(namedDecl().bind("sugared_class"));
  auto ArraySubscript = callExpr(
      callee(cxxMethodDecl(
          isSubscriptOperator(),
          ofClass(cxxRecordDecl(ArrayClass, namedDecl().bind("class"))),
          namedDecl().bind("method"))),
      optionally(
          anyOf(cxxOperatorCallExpr(onObjectArgument(SugaredClass)),
                cxxMemberCallExpr(onImplicitObjectArgument(SugaredClass)))));
  Finder->addMatcher(ArraySubscript.bind("call"), this);
}

void StdArrayNoOperatorAtCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *CE = Result.Nodes.getNodeAs<CallExpr>("call");
  const auto *MD = Result.Nodes.getNodeAs<NamedDecl>("method");
  const auto *RD = Result.Nodes.getNodeAs<NamedDecl>("class");
  if (!CE || !MD || !RD)
    return;

  const NamedDecl *C = RD;
  if (const auto *SC = Result.Nodes.getNodeAs<NamedDecl>("sugared_class"))
    C = SC;

  diag(CE->getBeginLoc(), "Do not access elements of '%0' via '%1', use "
                          "'Array1DRef' / 'Array2DRef' abstractions")
      << C->getQualifiedNameAsString() << MD->getNameAsString();
}

} // namespace clang::tidy::rawspeed
