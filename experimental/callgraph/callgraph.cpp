
#include <string>
#include <iostream>
#include "callgraph.h"

CallgraphVisitor::CallgraphVisitor(clang::ASTContext *context)
   : graph()
   , nodeLabels(graph)
   , graphWriter(graph)
{
   // empty
}

void CallgraphVisitor::writeCallgraph()
{
   std::map<unsigned, std::set<unsigned> >::const_iterator edge;
   for(edge = connections.begin();
       edge != connections.end();
       ++edge)
   {
      std::set<unsigned>::const_iterator dest;
      for(dest = edge->second.begin();
          dest != edge->second.end();
          ++dest)
      {
         std::cout << functionNames[edge->first]
                   << "  --> "
                   << functionNames[*dest]
                   << std::endl;
      }
   }
//   graphWriter.nodeMap("label", nodeLabels);
//   graphWriter.run();
}

std::string CallgraphVisitor::getCompleteFunctionId(const clang::Decl *decl)
{
   const clang::FunctionDecl *function = 
      clang::dyn_cast<const clang::FunctionDecl>(decl);
   std::string funcId;
   funcId += function->getResultType().getAsString();
   funcId += " "+function->getQualifiedNameAsString();
   funcId+= "(";
   bool first = true;
   clang::FunctionDecl::param_const_iterator paramIterate;
   for (paramIterate = function->param_begin();
        paramIterate != function->param_end();
        ++paramIterate)
   {
      if (!first) funcId += ",";
      funcId += (*paramIterate)->getType().getAsString() + " ";
      if((*paramIterate)->getIdentifier()) {
         funcId += (*paramIterate)->getIdentifier()->getName().str();
      }
      first = false;
   }
   if(function->isVariadic())
      funcId += ", ...";
   funcId += ")";
   if(clang::CXXMethodDecl::classof(decl)) 
   {
      const clang::CXXMethodDecl *method = 
         clang::dyn_cast<const clang::CXXMethodDecl>(decl);
      clang::ASTContext &context = method->getParentASTContext();
      if(method->isCopyAssignmentOperator()) 
      {
        // std::cout << "FUNCTION IS overloaded Assignment!\n";
      }
      // The next function seems to be implemented incorrectly;
      // i.e., clang marks it false, but doesn't mark it true?
      if(method->hasInlineBody()) 
      {
       //  std::cout << "FUNCTION " << function->getQualifiedNameAsString()
       //            << " IS not INLINED!\n";
      }
      if(method->isStatic())
         funcId = "static " + funcId;
      if(method->isVolatile())
         funcId += " volatile";
      if(method->isConst())
         funcId += " const";
   }
   lemon::ListDigraph::Node funcNode = graph.addNode();
   nodeLabels[funcNode] = funcId;
   return funcId;
} // end of processFunction

bool CallgraphVisitor::VisitCallExpr(clang::CallExpr *decl)
{
   clang::FunctionDecl *func = decl->getDirectCallee();
   if(func) {
      connections[current->getLocation().getRawEncoding()]
                   .insert(func->getLocation().getRawEncoding());
#if 0
      std::cout << getCompleteFunctionId(current)
                << " [" << current->getLocation().getRawEncoding() << "]"
                << "  -->  "
                << getCompleteFunctionId(func)
                << " [" << func->getLocation().getRawEncoding() << "]"
                << std::endl;
#endif
   }
   return true;
}

bool CallgraphVisitor::VisitFunctionDecl(clang::FunctionDecl *decl)
{
   functionNames[decl->getLocation().getRawEncoding()] = getCompleteFunctionId(decl);
   /* FIXME: this assumes no nested functions, and that all expressions
    *        occur within a function scope.  Both of these are true about
    *        99% of the time.
    */
   current = decl;
   return true;
}

