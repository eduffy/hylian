
#include <string>
#include <cstdio>
#include <iostream>
#include "cpp2json.h"

CppToJsonVisitor::CppToJsonVisitor(clang::ASTContext *context)
{
}

std::string CppToJsonVisitor::getQualifiedName(const clang::Decl *decl)
{
   const clang::FunctionDecl *f = clang::dyn_cast<const clang::FunctionDecl>(decl);
   std::string result = f->getQualifiedNameAsString() + "(";
   bool first = true;
   clang::FunctionDecl::param_const_iterator pi;
   for (pi = f->param_begin(); pi != f->param_end(); ++pi)
   {
      if(!first)
         result += ", ";
      result += (*pi)->getType().getAsString();
      first = false;
   }
   if(f->isVariadic())
      result += ", ...";
   result += ")";

   if(clang::CXXMethodDecl::classof(f)) 
   {
      const clang::CXXMethodDecl *method = 
         clang::dyn_cast<const clang::CXXMethodDecl>(f);
      clang::ASTContext &context = method->getParentASTContext();
      if(method->isStatic())
         result = "static " + result;
      if(method->isVolatile())
         result += " volatile";
      if(method->isConst())
         result += " const";
   }

   return result;
}

/*
bool CppToJsonVisitor::TraverseStmt(clang::Stmt *stmt)
{
  if(stmt)
    std::cout << "Statememtn: " << stmt->getStmtClassName() << std::endl;
  else std::cout << "null stmtate" << std::endl;
  return true;
}*/

bool CppToJsonVisitor::TraverseNullStmt(clang::NullStmt *stmt)
{
  std::cout << "\"NullStmt\"";
  return true;
}

bool CppToJsonVisitor::TraverseIfStmt(clang::IfStmt *stmt)
{
  std::cout << "\"IfStmt\":{\"condition\":";
  std::cout << "<<" << stmt->getCond()->getStmtClassName() << std::endl;
  TraverseStmt(stmt->getCond());
  std::cout << stmt->getCond()->getStmtClassName() << ">>" << std::endl;
  std::cout << ",\"then\":";
  TraverseStmt(stmt->getThen());
  std::cout << ",\"else\":";
  if(stmt->getElse()) {
    TraverseStmt(stmt->getElse());
  }
  else {
    std::cout << "null";
  }
  std::cout << "}";
  return true;
}

bool CppToJsonVisitor::TraverseReturnStmt(clang::ReturnStmt *stmt)
{
  std::cout << "\"ReturnStmt\":{\"retValue\":";
  TraverseStmt(stmt->getRetValue());
  std::cout << "}";
  return true;
}

bool CppToJsonVisitor::TraverseCompoundStmt(clang::CompoundStmt *stmt)
{
  clang::CompoundStmt::body_iterator i;
  std::cout << "\"CompountStmt\":[";
  for(i = stmt->body_begin(); i != stmt->body_end(); i++) {
    if(i != stmt->body_begin()) std::cout << ",";
    TraverseStmt(*i);
  }
  std::cout << "]";
  return true;
}

bool CppToJsonVisitor::TraverseDeclRefExpr(clang::DeclRefExpr *expr)
{
   std::cout << "\"DeclRefExpr\":{\"name\":" << expr->getFoundDecl()->getNameAsString() << "\"}";
   return true;
}

bool CppToJsonVisitor::TraverseFunctionDecl(clang::FunctionDecl *decl)
{
  clang::FunctionDecl::param_const_iterator p;
  std::cout << "\"FunctionDecl\":{\"body\":";
  if(decl->getBody())
     TraverseStmt(decl->getBody());
  std::cout << "}, \"params\":[";
  for(p = decl->param_begin(); p != decl->param_end(); p++) {
    if(p != decl->param_begin()) std::cout << ",";
    std::cout << "{\"name\":\"\",\"type\":\"" << (*p)->getType().getAsString() << "\"}";
  }
  std::cout << "]";
  return true;
}

bool CppToJsonVisitor::TraverseBinaryOperator(clang::BinaryOperator *expr)
{
  std::cout << "\"BinaryOperator\":{";
/*
            << "\"op\":\""  << clang::BinaryOperator::getOpcodeStr(expr->getOpcode()).str() << "\"";
  std::cout << ",\"lhs\":";
  TraverseStmt(expr->getLHS());
  std::cout << ",\"rhs\":";
  TraverseStmt(expr->getRHS());
  std::cout << "}";
*/
  return true;
}
