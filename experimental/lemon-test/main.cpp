
#include <iostream>
#include <string>
#include <typeinfo>
#include <lemon/list_graph.h>
#include <lemon/lgf_writer.h>
using std::cout;
using std::endl;

int main()
{
  lemon::ListDigraph graph;

  lemon::ListDigraph::Node u = graph.addNode();
  lemon::ListDigraph::Node v = graph.addNode();
  lemon::ListDigraph::Node w = graph.addNode();
  lemon::ListDigraph::Arc  a = graph.addArc(u, v);
  lemon::ListDigraph::Arc  b = graph.addArc(v, w);

  cout << "Hello World! This is LEMON library here." << endl;
  cout << "We have a directed graph with " << countNodes(graph) 
       << " nodes " << "and " << countArcs(graph) << " arc." << endl;

  cout << "Type name: " << typeid(lemon::ListDigraph).name() << endl;
  lemon::DigraphWriter<lemon::ListDigraph> graphWriter(graph);
  lemon::ListDigraph::ArcMap<std::string> arcLabels(graph);
  lemon::ListDigraph::NodeMap<std::string> nodeLabels(graph);
  arcLabels[a] = "arc(u, v)";
  arcLabels[b] = "arc(v, w)";
  nodeLabels[u] = "node(u)";
  nodeLabels[v] = "node(v)";
  nodeLabels[w] = "node(w)";
  graphWriter.arcMap("label",arcLabels);
  graphWriter.nodeMap("label",nodeLabels);
  graphWriter.run();

  return 0;
}
