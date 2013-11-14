
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

/*
bool LCOM2Visitor::TraverseFunctionDecl(clang::FunctionDecl *decl)
{
   complexity = 1;

   std::string qname = getQualifiedName(decl);
   printf("%5d |  %s\n", complexity, qname.c_str());

   complexity = 0;
   return true;
}*/

bool LCOM2Visitor::TraverseMemberExpr(clang::MemberExpr *expr)
{
  clang::ValueDecl *v = expr->getMemberDecl();
  std::cout << "member expression: " << v->getQualifiedNameAsString() << std::endl;
  return true;
}

bool LCOM2Visitor::TraverseCXXMethodDecl(clang::CXXMethodDecl *decl)
{
   if(decl->getBody())
      TraverseStmt(decl->getBody());
   return true;
}

bool LCOM2Visitor::TraverseCXXConversionDecl(clang::CXXConversionDecl *decl)
{
   return TraverseCXXMethodDecl(decl);
}

bool LCOM2Visitor::TraverseCXXDestructorDecl(clang::CXXDestructorDecl *decl)
{
   return TraverseCXXMethodDecl(decl);
}

bool LCOM2Visitor::TraverseCXXConstructorDecl(clang::CXXConstructorDecl *decl)
{
   return TraverseCXXMethodDecl(decl);
}


