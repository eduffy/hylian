
#ifndef CPP_TO_JSON_H
#define CPP_TO_JSON_H

#include <map>
#include <set>
#include <string>

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>

class CppToJsonVisitor
   : public clang::RecursiveASTVisitor<CppToJsonVisitor>
{
public:
   CppToJsonVisitor(clang::ASTContext *context);
   virtual ~CppToJsonVisitor() { }

//   bool VisitFunctionDecl(clang::FunctionDecl *decl);
/*
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
*/
//   bool TraverseStmt(clang::Stmt *stmt);
bool TraverseNullStmt(clang::NullStmt *stmt);
bool TraverseReturnStmt(clang::ReturnStmt *stmt);
bool TraverseIfStmt(clang::IfStmt *stmt);
bool TraverseCompoundStmt(clang::CompoundStmt *stmt);
bool TraverseFunctionDecl(clang::FunctionDecl *decl);
bool TraverseDeclRefExpr(clang::DeclRefExpr *expr);
bool TraverseBinaryOperator(clang::BinaryOperator *expr);

private:
   std::string getQualifiedName(const clang::Decl *);
};

#endif  /* CPP_TO_JSON_H */
