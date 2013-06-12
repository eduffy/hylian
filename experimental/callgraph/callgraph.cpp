
#include <string>
#include <iostream>
#include "callgraph.h"

CallgraphVisitor::CallgraphVisitor(clang::ASTContext *context)
   : current(NULL)
   , mainDecl(NULL)
//   : graph()
//   , nodeLabels(graph)
//   , graphWriter(graph)
   
{
   // empty
}

void CallgraphVisitor::doWriteCallgraph(unsigned f, std::set<unsigned> &seen)
{
   if(seen.count(f) > 0)
      return;

   seen.insert(f);

   std::map<unsigned, std::set<unsigned> >::const_iterator fp = connections.find(f);
   if(fp == connections.end())
      return;

   std::set<unsigned>::const_iterator dest;
   for(dest = fp->second.begin();
       dest != fp->second.end();
       ++dest)
   {
      std::cout << "  f"    << f
                << "  -> f" << *dest
                << ";"      << std::endl;
      doWriteCallgraph(*dest, seen);
   }
}

void CallgraphVisitor::writeCallgraph()
{
   std::set<unsigned> seen;
   std::set<unsigned>::const_iterator fp;
//   std::map<unsigned, std::set<unsigned> >::const_iterator edge;
//   std::map<unsigned, std::string>::const_iterator name;

   assert(mainDecl != NULL);
   std::cout << "digraph G {" << std::endl;
   doWriteCallgraph(mainDecl->getLocation().getRawEncoding(), seen);

   for(fp = seen.begin();
       fp != seen.end();
       ++fp)
   {
      std::cout << "  f" << *fp
                << "[label=\"" << functionNames[*fp]
                << "\"];" << std::endl;
   }
   std::cout << "}" << std::endl;
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
//   lemon::ListDigraph::Node funcNode = graph.addNode();
//   nodeLabels[funcNode] = funcId;
   return funcId;
} // end of processFunction

/* TODO: Verify that this checks for implicit calls, like
 * object destructors, operators, etc...
 */
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
   if(decl->isMain()) {
      mainDecl = decl;
   }
   return true;
}

bool CallgraphVisitor::VisitCXXConstructExpr(clang::CXXConstructExpr *decl)
{
   clang::CXXConstructorDecl *func = decl->getConstructor();
   if(func) {
      connections[current->getLocation().getRawEncoding()]
                   .insert(func->getLocation().getRawEncoding());
   }
   return true;
}
