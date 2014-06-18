
#ifndef CPP_TO_JSON_H
#define CPP_TO_JSON_H

#include <map>
#include <set>
#include <string>
#include <sstream>

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>

#include <stack>
#include "JsonAST.h"

#define UNARYOP_LIST()                          \
  OPERATOR(PostInc)   OPERATOR(PostDec)         \
  OPERATOR(PreInc)    OPERATOR(PreDec)          \
  OPERATOR(AddrOf)    OPERATOR(Deref)           \
  OPERATOR(Plus)      OPERATOR(Minus)           \
  OPERATOR(Not)       OPERATOR(LNot)            \
  OPERATOR(Real)      OPERATOR(Imag)            \
  OPERATOR(Extension)

// All binary operators (excluding compound assign operators).
#define BINOP_LIST() \
  OPERATOR(PtrMemD)              OPERATOR(PtrMemI)    \
  OPERATOR(Mul)   OPERATOR(Div)  OPERATOR(Rem)        \
  OPERATOR(Add)   OPERATOR(Sub)  OPERATOR(Shl)        \
  OPERATOR(Shr)                                       \
                                                      \
  OPERATOR(LT)    OPERATOR(GT)   OPERATOR(LE)         \
  OPERATOR(GE)    OPERATOR(EQ)   OPERATOR(NE)         \
  OPERATOR(And)   OPERATOR(Xor)  OPERATOR(Or)         \
  OPERATOR(LAnd)  OPERATOR(LOr)                       \
                                                      \
  OPERATOR(Assign)                                    \
  OPERATOR(Comma)

// All compound assign operators.
#define CAO_LIST()                                                      \
  OPERATOR(Mul) OPERATOR(Div) OPERATOR(Rem) OPERATOR(Add) OPERATOR(Sub) \
  OPERATOR(Shl) OPERATOR(Shr) OPERATOR(And) OPERATOR(Or)  OPERATOR(Xor)

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
   bool TraverseForStmt(clang::ForStmt *stmt);
*/
//   bool TraverseStmt(clang::Stmt *stmt);
JsonASTNode *StmtToJson(clang::Stmt *stmt);
JsonASTObject *GenericTraverseDecl(clang::Decl *decl);
bool TraverseTranslationUnitDecl(clang::TranslationUnitDecl *decl);
bool TraverseTypedefDecl(clang::TypedefDecl *decl);
bool TraverseIntegerLiteral(clang::IntegerLiteral *stmt);
bool TraverseDeclStmt(clang::DeclStmt *stmt);
bool TraverseNullStmt(clang::NullStmt *stmt);
bool TraverseReturnStmt(clang::ReturnStmt *stmt);
bool TraverseBreakStmt(clang::BreakStmt *stmt);
bool TraverseContinueStmt(clang::ContinueStmt *stmt);
bool TraverseIfStmt(clang::IfStmt *stmt);
bool TraverseForStmt(clang::ForStmt *stmt);
   bool TraverseCaseStmt(clang::CaseStmt *stmt);
bool TraverseDefaultStmt(clang::DefaultStmt *stmt);
   bool TraverseSwitchStmt(clang::SwitchStmt *stmt);
   bool TraverseWhileStmt(clang::WhileStmt *stmt);
   bool TraverseDoStmt(clang::DoStmt *stmt);
bool TraverseCompoundStmt(clang::CompoundStmt *stmt);
bool TraverseFunctionDecl(clang::FunctionDecl *decl);
bool TraverseDeclRefExpr(clang::DeclRefExpr *expr);
bool GenericTraverseStmt(clang::Stmt *stmt, ...);

  bool GenericTraverseUnaryOperator(clang::UnaryOperator *expr);
#define OPERATOR(NAME) \
  bool TraverseUnary##NAME(clang::UnaryOperator *expr);
UNARYOP_LIST()
#undef OPERATOR

  bool GenericTraverseBinaryOperator(clang::BinaryOperator *expr);
#define OPERATOR(NAME) \
  bool TraverseBin##NAME(clang::BinaryOperator *expr);
BINOP_LIST()
#undef OPERATOR

#define OPERATOR(NAME) \
  bool TraverseBin##NAME##Assign(clang::CompoundAssignOperator *expr);
CAO_LIST()
#undef OPERATOR

  bool TraverseConditionalOperator(clang::ConditionalOperator *expr);
  bool TraverseCallExpr(clang::CallExpr *expr);

   std::string getJSON() 
   {
      std::stringstream json;
//      assert(buildStack.size() == 1);
//while(!buildStack.empty()) {
      buildStack.top()->Print(json);
//buildStack.pop();}
      return json.str();
   }
   JsonASTNode *getAST() { return buildStack.top(); }

private:
   std::string getQualifiedName(const clang::Decl *);

   std::stack<JsonASTNode *> buildStack;
};

#endif  /* CPP_TO_JSON_H */
