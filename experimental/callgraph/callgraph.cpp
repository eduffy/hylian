
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
              << ": "
              << "Returns " << fun->getResultType().getAsString()
              << ", Name: "
              << fun->getQualifiedNameAsString()
              << std::endl;
         clang::FunctionDecl::param_const_iterator it;
         cout << "\tParameters: ";
         for (it = fun->param_begin();
              it != fun->param_end();
              ++it) {
           cout << (*it)->getType().getAsString() << " "
                << (*it)->getIdentifier()->getName().str()
                << ",\t";
         }
         cout << endl;
      }
      else {
        // Usually a Namespace, CXXRecord, Typedef, LinkageSpec, or Enum...
        //cout << "Not a fn: " << decl->getDeclKindName() << endl;
      }
   }
}

