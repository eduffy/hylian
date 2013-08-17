
#include <string>
#include <iostream>
#include "mccabe.h"

McCabeVisitor::McCabeVisitor(clang::ASTContext *context)
{
}

std::string McCabeVisitor::getQualifiedName(const clang::Decl *decl)
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

bool McCabeVisitor::TraverseFunctionDecl(clang::FunctionDecl *decl)
{
   complexity = 1;
   if(decl->getBody())
      TraverseStmt(decl->getBody());

   std::string qname = getQualifiedName(decl);
   printf("%5d |  %s\n", complexity, qname.c_str());

   complexity = 0;
   return true;
}

bool McCabeVisitor::TraverseCXXMethodDecl(clang::CXXMethodDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool McCabeVisitor::TraverseCXXConversionDecl(clang::CXXConversionDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool McCabeVisitor::TraverseCXXDestructorDecl(clang::CXXDestructorDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool McCabeVisitor::TraverseCXXConstructorDecl(clang::CXXConstructorDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool McCabeVisitor::TraverseIfStmt(clang::IfStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   TraverseStmt(stmt->getThen());
   if(stmt->getElse() != NULL) {
      if(!clang::IfStmt::classof(stmt->getElse())) {
         //  Dont' count "else if" as two blocks
         ++complexity;
      }
      TraverseStmt(stmt->getElse());
   }
   return true;
}

bool McCabeVisitor::TraverseCaseStmt(clang::CaseStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getSubStmt())
      TraverseStmt(stmt->getSubStmt());
   return true;
}

bool McCabeVisitor::TraverseWhileStmt(clang::WhileStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getBody())
      TraverseStmt(stmt->getBody());
   return true;
}

bool McCabeVisitor::TraverseDoStmt(clang::DoStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getBody())
      TraverseStmt(stmt->getBody());
   return true;
}

bool McCabeVisitor::TraverseForStmt(clang::ForStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getBody())
      TraverseStmt(stmt->getBody());
   return true;
}

