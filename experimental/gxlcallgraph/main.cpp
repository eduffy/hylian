
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "gxl.h"

std::string getQualifiedName(gxl::Graph const& graph,
                             gxl::Node *el)
{
   if(el->getId() == "global")
      return "";

   std::string name = el->getId();
   gxl::Attribute *attr = el->getAttribute("name");
   if(attr)
      name = attr->asString();

   gxl::Node *parent = graph.findHeadNodeOfType("Contains", el);
   assert(parent != NULL);
   std::string pname = getQualifiedName(graph, parent);

   if(pname == "")
      return name;
   return pname + "::" + name;
}

std::string resolveType(gxl::Graph const& graph,
                        gxl::Node *el)

{

   if(el->getType() == "BuiltinType"
        || el->getType() == "Enum") {
      gxl::Attribute *a = el->getAttribute("name");
      return a->asString();
   }
   else if(el->getType() == "Class") {
      return getQualifiedName(graph, el);
   }
   else if(el->getType() == "PointerType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      return resolveType(graph, base) + " *";
   }
   else if(el->getType() == "ReferenceType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      return resolveType(graph, base) + " &";
   }
   else if(el->getType() == "ConstType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      return "const " + resolveType(graph, base);
   }
   else if(el->getType() == "VolatileType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      return "volatile " + resolveType(graph, base);
   }
   else if(el->getType() == "FunctionPointer") {
      return "(*)()";  /* FIXME */
   }
   else if(el->getType() == "ArrayType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      /* FIXME */
      return resolveType(graph, base) + "[]";
   }

   std::cout << "type[" << el->getType() << "]" << std::endl;
   /* fallthrough */
   return el->getId();
}

std::string resolveFunction(gxl::Graph const& graph,
                            gxl::Node *f)
{
   std::string result;
   std::string qname;
   std::vector<gxl::Node*> params;
   std::vector<gxl::Node*>::const_iterator p;
   gxl::Node *ptype;
   gxl::Attribute *attr;
   bool first;

   result = getQualifiedName(graph, f);
   result += "(";
   params = graph.findTailNodesOfType("ParameterDeclaration", f);
   first = true;
   for(p = params.begin(); p != params.end(); ++p) {
      if(!first) result += ", ";
      ptype = graph.findTailNodeOfType("TypeOf", *p);
      result += resolveType(graph, ptype);
      first = false;
   }

   result += ")";

   attr = f->getAttribute("is_const");
   if(attr->asBool())
      result += " const";
//   result = qname + "(" + "" + ")";
   return result;
}


int main(int argc, char *argv[])
{
   std::string fn(argv[1]);
   gxl::Graph graph;
   std::vector<gxl::Node*> functions;
   std::vector<gxl::Node*>::const_iterator fp;


   graph.parse(fn);
   functions = graph.getAllNodesOfType("Function");
   std::cout << functions.size() << " functions found."
             << std::endl;
   for(fp = functions.begin(); fp != functions.end(); ++fp) {
      std::string name = resolveFunction(graph, *fp);
      std::cout << name << std::endl;

     // break;
   }
   


   return EXIT_SUCCESS;
   
}
