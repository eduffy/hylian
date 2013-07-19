
#include <cassert>
#include <iostream>
#include <cstring>
#include <string>
#include <expat.h>
#include <zlib.h>
#include "gxl.h"

#define streq(X,Y)  (strcmp((X),(Y))==0)

struct ParserState
{
   gxl::Graph     *activeGraph;
   gxl::Node      *activeNode;
   gxl::Edge      *activeEdge;
   gxl::Attribute *activeAttr;
   std::string     activeString;
};

static void startElement(void *userData,
                         const char *tag,
                         const char **attrs)
{
   ParserState *state = (ParserState *)userData;

   if(streq(tag, "graph")) {
      // TODO get `id` attribute
   }
   else if(streq(tag, "node")) {
      assert(state->activeNode == NULL);
      state->activeNode = new gxl::Node(attrs);
   }
   else if(streq(tag, "edge")) {
      assert(state->activeEdge == NULL);
      state->activeEdge = new gxl::Edge(attrs);
   }
   else if(streq(tag, "attr")) {
      assert(state->activeAttr == NULL);
      state->activeAttr = new gxl::Attribute(attrs);
   }
   else if(streq(tag, "type")) {
      assert(streq(attrs[0], "xlink:href"));
      std::string type(attrs[1] + 8);
      if(state->activeNode)
         state->activeNode->setType(type);
      else if(state->activeEdge)
         state->activeEdge->setType(type);
   }
   else if(streq(tag, "string")
           || streq(tag, "int")
           || streq(tag, "bool")
           || streq(tag, "enum")) {
      assert(state->activeAttr != NULL);
      state->activeString = "";
   }

   else {
      std::cout << "Unhandled tag: `" << tag << "`." << std::endl;
   }
   
}

static void endElement(void *userData,
                         const char *tag)
{
   ParserState *state = (ParserState *)userData;
   if(streq(tag, "node")) {
      state->activeGraph->addNode(state->activeNode);
      state->activeNode = NULL;
   }
   else if(streq(tag, "edge")) {
      state->activeGraph->addEdge(state->activeEdge);
      state->activeEdge = NULL;
   }
   else if(streq(tag, "attr")) {
      if(state->activeNode)
         state->activeNode->addAttribute(state->activeAttr);
      else if(state->activeEdge)
         state->activeEdge->addAttribute(state->activeAttr);
      else
         std::cout << "Dangling attribute: " << *state->activeAttr 
                   << std::endl;
      state->activeAttr = NULL;
   }
   else if(streq(tag, "string")
           || streq(tag, "int")
           || streq(tag, "bool")
           || streq(tag, "enum")) {
      state->activeAttr->setType(tag);
      state->activeAttr->setValue(state->activeString);
   }
}

static void characters(void *userData,
                       const char *data,
                       int length)
{
   ParserState *state = (ParserState *)userData;
   state->activeString += std::string(data, length);
}

void gxl::Graph::addNode(Node *node)
{
   nodes[node->getId()] = node;
}

void gxl::Graph::addEdge(Edge *edge)
{
   edgeHeads.insert(make_pair(edge->getHead(), edge));
   edgeTails.insert(make_pair(edge->getTail(), edge));
}

void gxl::Graph::parse(std::string const& fn)
{
  enum { BUFFSIZE = (1 << 20) };

  gzFile f;
  char buffer[BUFFSIZE];
  size_t bytesread;
  XML_Parser parser;
  ParserState state;

  state.activeGraph   = this;
  state.activeNode    = NULL;
  state.activeEdge    = NULL;
  state.activeAttr    = NULL;
  state.activeString  = "";

  parser = XML_ParserCreate(NULL);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, characters);
  XML_SetUserData(parser, &state);

  f = gzopen(fn.c_str(), "r");
  assert(f != NULL);
  do {
     bytesread = gzread(f, buffer, BUFFSIZE);
     XML_Parse(parser, buffer, bytesread, bytesread < BUFFSIZE);
  } while(bytesread == BUFFSIZE);
}


std::vector<gxl::Node*>
gxl::Graph::getAllNodesOfType(std::string const& type) const
{
   // this will not results in a copy when `return`ed
   std::vector<Node*> result;
   std::map<std::string, Node*>::const_iterator p;

   for(p = nodes.begin(); p != nodes.end(); ++p) {
      if(p->second->getType() == type)
         result.push_back(p->second);
   }
   return result;
}

gxl::Node *gxl::Graph::findHeadNodeOfType(std::string const& type, Node* tail) const
{
   std::pair<std::multimap<std::string, Edge*>::const_iterator,
             std::multimap<std::string, Edge*>::const_iterator> range;
   std::multimap<std::string, Edge*>::const_iterator p;
   range = edgeTails.equal_range(tail->getId());
   for(p = range.first; p != range.second; ++p) {
      if(p->second->getType() == type)
         return nodes.at(p->second->getHead());
   }
   
   return NULL;
}

gxl::Node *gxl::Graph::findTailNodeOfType(std::string const& type, Node* head) const
{
   std::pair<std::multimap<std::string, Edge*>::const_iterator,
             std::multimap<std::string, Edge*>::const_iterator> range;
   std::multimap<std::string, Edge*>::const_iterator p;
   range = edgeHeads.equal_range(head->getId());
   for(p = range.first; p != range.second; ++p) {
      if(p->second->getType() == type)
         return nodes.at(p->second->getTail());
   }
   
   return NULL;
}

std::vector<gxl::Node*>
gxl::Graph::findTailNodesOfType(std::string const& type, Node *head) const
{
   std::vector<gxl::Node*> result;
   std::pair<std::multimap<std::string, Edge*>::const_iterator,
             std::multimap<std::string, Edge*>::const_iterator> range;
   std::multimap<std::string, Edge*>::const_iterator p;
   range = edgeHeads.equal_range(head->getId());
   for(p = range.first; p != range.second; ++p) {
      if(p->second->getType() == type)
         result.push_back(nodes.at(p->second->getTail()));
   }
   
   return result;
}

gxl::Node::Node(const char **attrs)
{
   for(int i = 0; attrs[i] != NULL; i += 2)
   {
      if(streq(attrs[i], "id"))
         id = attrs[i+1];
   }
}

std::string const& gxl::Node::getId() const
{
   return id;
}

void gxl::Node::setType(std::string const& _type)
{
   type = _type;
} 

std::string const& gxl::Node::getType() const
{
   return type;
} 

void gxl::Node::addAttribute(Attribute *a)
{
   attributes.push_back(a);
}

gxl::Attribute *gxl::Node::getAttribute(std::string const& name) const
{
   std::vector<Attribute*>::const_iterator p;
   for(p = attributes.begin(); p != attributes.end(); ++p)
      if((*p)->getName() == name)
         return *p;
   return NULL;
}

gxl::Edge::Edge(const char **attrs)
{
   for(int i = 0; attrs[i] != NULL; i += 2)
   {
      if(streq(attrs[i], "from"))
         from = attrs[i+1];
      else if(streq(attrs[i], "to"))
         to = attrs[i+1];
   }
}

std::string const& gxl::Edge::getHead() const
{
   return from;
}

std::string const& gxl::Edge::getTail() const
{
   return to;
}

std::string const& gxl::Edge::getType() const
{
   return type;
} 

void gxl::Edge::setType(std::string const& _type)
{
   type = _type;
} 

void gxl::Edge::addAttribute(Attribute *a)
{
   attributes.push_back(a);
}

gxl::Attribute::Attribute(const char **attrs)
{
   for(int i = 0; attrs[i] != NULL; i += 2)
   {
      if(streq(attrs[i], "name"))
         name = attrs[i+1];
   }
}

void gxl::Attribute::setType(std::string const& type_)
{
   type = type_;
}

void gxl::Attribute::setValue(std::string const& value_)
{
   value = value_;
}

std::string const& gxl::Attribute::getName() const
{
   return name;
}

std::string const& gxl::Attribute::asString() const
{
   assert(type == "string" || type == "enum");
   return value;
}

int gxl::Attribute::asInt() const
{
   assert(type == "enum");
   return atoi(value.c_str());
}

bool gxl::Attribute::asBool() const
{
   assert(type == "bool");
   return value == "true";
}

std::ostream &gxl::Attribute::Print(std::ostream &os) const
{
   return os << "[" << name << ":" << type << "] = " << value;
}

