
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

//   bool VisitFunctionDecl(clang::FunctionDecl *decl);
   bool TraverseFunctionDecl(clang::FunctionDecl *decl);
   bool TraverseCXXMethodDecl(clang::CXXMethodDecl *decl);
   bool TraverseCXXConversionDecl(clang::CXXConversionDecl *decl);
   bool TraverseCXXDestructorDecl(clang::CXXDestructorDecl *decl);
   bool TraverseCXXConstructorDecl(clang::CXXConstructorDecl *decl);

   bool TraverseIfStmt(clang::IfStmt *stmt);
   bool TraverseCaseStmt(clang::CaseStmt *stmt);
   bool TraverseWhileStmt(clang::WhileStmt *stmt);
   bool TraverseDoStmt(clang::DoStmt *stmt);
   bool TraverseForStmt(clang::ForStmt *stmt);

private:
   std::string getQualifiedName(const clang::Decl *);

   unsigned complexity;
};

#endif  /* LCOM2_H */
