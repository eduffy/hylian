
#ifndef LCOM2_H
#define LCOM2_H

#include <map>
#include <set>
#include <string>

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>

class LCOM2Visitor
   : public clang::RecursiveASTVisitor<LCOM2Visitor>
{
public:
   LCOM2Visitor(clang::ASTContext *context);
   virtual ~LCOM2Visitor() { }

   bool TraverseCXXMethodDecl(clang::CXXMethodDecl *decl);
   bool TraverseCXXConversionDecl(clang::CXXConversionDecl *decl);
   bool TraverseCXXDestructorDecl(clang::CXXDestructorDecl *decl);
   bool TraverseCXXConstructorDecl(clang::CXXConstructorDecl *decl);

bool TraverseMemberExpr(clang::MemberExpr *expr);

private:
   std::string getQualifiedName(const clang::Decl *);

   unsigned complexity;
};

#endif  /* LCOM2_H */
