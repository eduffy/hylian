
#ifndef HYLIAN_CONSUMER_H
#define HYLIAN_CONSUMER_H

#include <clang/AST/Decl.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/GlobalDecl.h>
#include <clang/AST/ASTConsumer.h>
#include <lemon/list_graph.h>
#include <lemon/lgf_writer.h>

class HylianASTConsumer : public clang::ASTConsumer
{
public:
   HylianASTConsumer() : 
     graph(), 
     nodeLabels(graph),
     graphWriter(graph)
   {}
   virtual void HandleTopLevelDecl(clang::DeclGroupRef declGroup);
   void writeCallgraph();

private:
   lemon::ListDigraph graph;
   lemon::ListDigraph::NodeMap<std::string> nodeLabels;
   lemon::DigraphWriter<lemon::ListDigraph> graphWriter;

   void HandleNamespaceDecl(const clang::NamespaceDecl *);
   void HandleFunctionDecl(const clang::FunctionDecl *);
   void HandleCXXMethodDecl(const clang::CXXMethodDecl *);
   void processFunction(const clang::Decl *);
   const lemon::ListDigraph& getGraph() const { return graph; }
   const lemon::ListDigraph::NodeMap<std::string>& 
     getNodeLabels() const { return nodeLabels; }
};

#endif  /* HYLIAN_CONSUMER_H */
