
#ifndef HYLIAN_CONSUMER_H
#define HYLIAN_CONSUMER_H

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/GlobalDecl.h>
#include <clang/AST/ASTConsumer.h>
#include <sqlite3.h>

#include "HylianASG.h"

class HylianASTConsumer : public clang::ASTConsumer
{
public:
   HylianASTConsumer(std::string const& fn);
   virtual void HandleTopLevelDecl(clang::DeclGroupRef declGroup);

private:
   void HandleNamespaceDecl(const clang::NamespaceDecl *);
   void HandleFunctionDecl(const clang::FunctionDecl *);
   void HandleCXXMethodDecl(const clang::CXXMethodDecl *);

   HylianASG asg;
};

#endif  /* HYLIAN_CONSUMER_H */
