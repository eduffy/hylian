
#ifndef GXL_H
#define GXL_H

#include <string>
#include <vector>
#include <map>

namespace gxl {

class Graph;
class Node;
class Edge;
class Attribute;

class Graph
{
public:
   void addNode(Node *);
   void addEdge(Edge *);
   void parse(std::string const& fn);

   std::vector<Node*> getAllNodesOfType(std::string const&) const;
   Node *findHeadNodeOfType(std::string const&, Node*) const;
   Node *findTailNodeOfType(std::string const&, Node*) const;
   std::vector<Node*> findTailNodesOfType(std::string const&, Node*) const;

private:
   std::map<std::string, Node*>       nodes;
   std::multimap<std::string, Edge*>  edgeHeads, edgeTails;
};


class Node
{
public:
   Node(const char **);
   std::string const& getId() const;
   std::string const& getType() const;
   void setType(std::string const&);
   void addAttribute(Attribute *);
   Attribute *getAttribute(std::string const&) const;
private:
   std::string id, type;
   std::vector<Attribute*> attributes;
};

class Edge
{
public:
   Edge(const char **);
   std::string const& getHead() const;
   std::string const& getTail() const;
   std::string const& getType() const;
   void setType(std::string const&);
   void addAttribute(Attribute *);
private:
   std::string from, to;
   std::string type;
   std::vector<Attribute *> attributes;
};

class Attribute
{
public:
   Attribute(const char **);
   void setType(std::string const&);
   void setValue(std::string const&);

   std::string const& getName() const;
   std::string const& asString() const;
   int asInt() const;
   bool asBool() const;

   std::ostream &Print(std::ostream &os) const;

private:
   std::string name;
   std::string type;
   std::string value;
};


} // namespace gxl

inline std::ostream &operator<<(std::ostream &os, gxl::Attribute const& a)
{
   return a.Print(os);
} 

#endif  /* GXL_H */
