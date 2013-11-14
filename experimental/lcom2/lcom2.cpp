
#include <string>
#include <iostream>
#include <cstdio>
#include "lcom2.h"

LCOM2Visitor::LCOM2Visitor(clang::ASTContext *context)
{
}

std::string LCOM2Visitor::getQualifiedName(const clang::Decl *decl)
{
   const clang::FunctionDecl *f = clang::dyn_cast<const clang::FunctionDecl>(decl);
   std::string result = f->getQualifiedNameAsString() + "(";
   bool first = true;
   clang::FunctionDecl::param_const_iterator pi;
   for(pi = f->param_begin(); pi != f->param_end(); ++pi)
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

bool LCOM2Visitor::TraverseFunctionDecl(clang::FunctionDecl *decl)
{
   complexity = 1;
   if(decl->getBody())
      TraverseStmt(decl->getBody());

   std::string qname = getQualifiedName(decl);
   printf("%5d |  %s\n", complexity, qname.c_str());

   complexity = 0;
   return true;
}

bool LCOM2Visitor::TraverseCXXMethodDecl(clang::CXXMethodDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool LCOM2Visitor::TraverseCXXConversionDecl(clang::CXXConversionDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool LCOM2Visitor::TraverseCXXDestructorDecl(clang::CXXDestructorDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool LCOM2Visitor::TraverseCXXConstructorDecl(clang::CXXConstructorDecl *decl)
{
   return TraverseFunctionDecl(decl);
}

bool LCOM2Visitor::TraverseIfStmt(clang::IfStmt *stmt)
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

bool LCOM2Visitor::TraverseCaseStmt(clang::CaseStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getSubStmt())
      TraverseStmt(stmt->getSubStmt());
   return true;
}

bool LCOM2Visitor::TraverseWhileStmt(clang::WhileStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getBody())
      TraverseStmt(stmt->getBody());
   return true;
}

bool LCOM2Visitor::TraverseDoStmt(clang::DoStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getBody())
      TraverseStmt(stmt->getBody());
   return true;
}

bool LCOM2Visitor::TraverseForStmt(clang::ForStmt *stmt)
{
   assert(complexity > 0);
   ++complexity;
   if(stmt->getBody())
      TraverseStmt(stmt->getBody());
   return true;
}

