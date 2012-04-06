
#include <string>
#include <iostream>
using  std::cout; using  std::endl;
#include "callgraph.h"

// The following Visitor gives all namespace declarations.
void HylianASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
   for(clang::DeclGroupRef::iterator i = declGroup.begin(); 
                                     i != declGroup.end(); 
                                     ++i)
   {
      const clang::Decl *decl = clang::dyn_cast<clang::Decl>(*i);
      if(clang::FunctionDecl::classof(decl)) {
         const clang::FunctionDecl *fun = 
                 clang::dyn_cast<const clang::FunctionDecl>(decl);
         cout << decl->getDeclKindName()
              << fun->getResultType().getAsString()
              << " "
              << fun->getQualifiedNameAsString()
              << std::endl;
      }
   }
}

