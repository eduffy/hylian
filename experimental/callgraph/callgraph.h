
#ifndef HYLIAN_CONSUMER_H
#define HYLIAN_CONSUMER_H

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/GlobalDecl.h>
#include <clang/AST/ASTConsumer.h>

class HylianASTConsumer : public clang::ASTConsumer
{
public:
   virtual void HandleTopLevelDecl(clang::DeclGroupRef declGroup);

private:
   void HandleNamespaceDecl(const clang::NamespaceDecl *);
   void HandleFunctionDecl(const clang::FunctionDecl *);
   void HandleCXXMethodDecl(const clang::CXXMethodDecl *);

};

#endif  /* HYLIAN_CONSUMER_H */
