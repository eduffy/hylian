
#ifndef CALLGRAPH_H
#define CALLGRAPH_H

#include <map>
#include <set>
#include <string>

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <lemon/list_graph.h>
#include <lemon/lgf_writer.h>

class CallgraphVisitor
   : public clang::RecursiveASTVisitor<CallgraphVisitor>
{
public:
   CallgraphVisitor(clang::ASTContext *context);
   virtual ~CallgraphVisitor() { }

   void writeCallgraph();

   bool VisitCallExpr(clang::CallExpr *decl);
   bool VisitFunctionDecl(clang::FunctionDecl *decl);

private:
   clang::FunctionDecl *current;
   std::map<unsigned, std::set<unsigned> > connections;
   std::map<unsigned, std::string> functionNames;

   lemon::ListDigraph graph;
   lemon::ListDigraph::NodeMap<std::string> nodeLabels;
   lemon::DigraphWriter<lemon::ListDigraph> graphWriter;

   std::string getCompleteFunctionId(const clang::Decl *);
   const lemon::ListDigraph& getGraph() const { return graph; }
   const lemon::ListDigraph::NodeMap<std::string>& 
   getNodeLabels() const { return nodeLabels; }
};

#endif  /* CALLGRAPH_H */
