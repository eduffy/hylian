
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
         std::string caller;
         caller += fun->getResultType().getAsString();
         caller += " "+fun->getQualifiedNameAsString();
         caller+= "(";
         bool first = true;
         clang::FunctionDecl::param_const_iterator it;
         for (it = fun->param_begin();
              it != fun->param_end();
              ++it) {
           if (!first) caller += ",";
           caller += (*it)->getType().getAsString() + " ";
           if ( (*it)->getIdentifier() ) {
             caller += (*it)->getIdentifier()->getName().str();
           }
           first = false;
         }
         caller += ")";
         if(clang::CXXMethodDecl::classof(decl)) 
         {
           const clang::CXXMethodDecl *fun = 
                 clang::dyn_cast<const clang::CXXMethodDecl>(decl);
           clang::ASTContext& context = fun->getParentASTContext();
           cout << "THIS: " << fun->getThisType(context).getAsString() << endl;
           if ( fun->getThisType(context).isConstQualified() ) 
           {
             caller += " const";
           }
         }

         cout << caller << endl;
      }
      else {
        // Usually a Namespace, CXXRecord, Typedef, LinkageSpec, or Enum...
        //cout << "Not a fn: " << decl->getDeclKindName() << endl;
      }
   }
}

