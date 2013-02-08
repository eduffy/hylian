
#include <string>
#include <iostream>
using  std::cout; using  std::endl;
#include "callgraph.h"

void HylianASTConsumer::writeCallgraph() {
   graphWriter.nodeMap("label", nodeLabels);
   graphWriter.run();
}

void HylianASTConsumer::processFunction(const clang::Decl *decl) {
  const clang::FunctionDecl *function = 
        clang::dyn_cast<const clang::FunctionDecl>(decl);
  std::string funDecl;
  funDecl += function->getResultType().getAsString();
  funDecl += " "+function->getQualifiedNameAsString();
  funDecl+= "(";
  bool first = true;
  clang::FunctionDecl::param_const_iterator paramIterate;
  for (paramIterate = function->param_begin();
       paramIterate != function->param_end();
       ++paramIterate) {
    if (!first) funDecl += ",";
    funDecl += (*paramIterate)->getType().getAsString() + " ";
    if ( (*paramIterate)->getIdentifier() ) {
      funDecl += (*paramIterate)->getIdentifier()->getName().str();
    }
    first = false;
  }
  funDecl += ")";
  if(clang::CXXMethodDecl::classof(decl)) 
  {
    const clang::CXXMethodDecl *method = 
          clang::dyn_cast<const clang::CXXMethodDecl>(decl);
    clang::ASTContext& context = method->getParentASTContext();
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
      funDecl += " const";
    }
  }
  lemon::ListDigraph::Node funcNode = graph.addNode();
  nodeLabels[funcNode] = funDecl;
} // end of processFunction

// The following Visitor gives all namespace declarations.
void HylianASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
   lemon::ListDigraph::NodeMap<std::string> nodeLabels(graph);
   for(clang::DeclGroupRef::iterator 
       declGroupIterate = declGroup.begin(); 
       declGroupIterate != declGroup.end(); 
       ++declGroupIterate)
   {
      const clang::Decl *decl = 
            clang::dyn_cast<clang::Decl>(*declGroupIterate);
      if(clang::FunctionDecl::classof(decl)) {
        // This is a function in the global anonymous namespace:
        processFunction(decl);
      }
      else {
        // A Namespace, CXXRecord, Typedef, LinkageSpec, Enum, or ...
        //if ( decl->isNamespace() ) {
        if ( strcmp(decl->getDeclKindName(), "CXXRecord") == 0 ) {
  const clang::CXXRecordDecl *thisClass = 
        clang::dyn_cast<const clang::CXXRecordDecl>(decl);             
          cout << "Class: " << thisClass->getNameAsString() << endl;
        }
        if ( strcmp(decl->getDeclKindName(), "Namespace") == 0 ) {
  const clang::NamespaceDecl *space = 
        clang::dyn_cast<const clang::NamespaceDecl>(decl);             
          cout << "Namespace: " << space->getNameAsString() << endl;
        }
      }
   }
}

