
#include <string>
#include <iostream>
using  std::cout; using  std::endl;
#include "callgraph.h"

// The following Visitor gives all namespace declarations.
void HylianASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
   for(clang::DeclGroupRef::iterator declGroupIterate = declGroup.begin(); 
                                     declGroupIterate != declGroup.end(); 
                                     ++declGroupIterate)
   {
      const clang::Decl *decl = 
            clang::dyn_cast<clang::Decl>(*declGroupIterate);
      if(clang::FunctionDecl::classof(decl)) {
         const clang::FunctionDecl *function = 
               clang::dyn_cast<const clang::FunctionDecl>(decl);
         std::string caller;
         caller += function->getResultType().getAsString();
         caller += " "+function->getQualifiedNameAsString();
         caller+= "(";
         bool first = true;
         clang::FunctionDecl::param_const_iterator paramIterate;
         for (paramIterate = function->param_begin();
              paramIterate != function->param_end();
              ++paramIterate) {
           if (!first) caller += ",";
           caller += (*paramIterate)->getType().getAsString() + " ";
           if ( (*paramIterate)->getIdentifier() ) {
             caller += (*paramIterate)->getIdentifier()->getName().str();
           }
           first = false;
         }
         caller += ")";
         if(clang::CXXMethodDecl::classof(decl)) 
         {
           const clang::CXXMethodDecl *method = 
                 clang::dyn_cast<const clang::CXXMethodDecl>(decl);
           clang::ASTContext& context = method->getParentASTContext();
           cout << "THIS: " << method->getThisType(context).getAsString() 
                << endl;
           if ( method->isCopyAssignmentOperator() ) 
           {
             cout<<"FUNCTION IS overloaded Assignment!\n";
           }
           // The next function seems to be implemented incorrectly;
           // i.e., clang marks it false, but doesn't mark it true?
           if ( method->hasInlineBody() ) 
           {
             cout << "FUNCTION " << function->getQualifiedNameAsString()
                  << " IS not INLINED!\n";
           }
           if ( method->getThisType(context).isConstQualified() ) 
           {
             caller += " const";
           }
         }

         cout << caller << endl;
      }
      else {
        // Usually a Namespace, CXXRecord, Typedef, LinkageSpec, or Enum...
        cout << "Construct in global namespace, other than a fn: " 
             << decl->getDeclKindName() << endl;
      }
   }
}

