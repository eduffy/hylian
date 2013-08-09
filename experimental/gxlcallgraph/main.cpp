
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "gxl.h"

std::string getQualifiedName(gxl::Graph const&, gxl::Node *);
std::string resolveFunction(gxl::Graph const&, gxl::Node *);
std::string resolveType(gxl::Graph const&, gxl::Node *);

template<class T, class U>
void concat(T &dest, U const& src)
{
   dest.insert(dest.end(), src.begin(), src.end());
}

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
   if(parent == NULL) {

      /* No parent.  Is it a phantom? */

      parent = graph.findHeadNodeOfType("Member", el);


      return name;
   }

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
        || el->getType() == "Enum"
        || el->getType() == "PhantomTypename"
        || el->getType() == "PhantomTypeReference") {
      gxl::Attribute *a = el->getAttribute("name");
      return (a == NULL) ? el->getId() : a->asString();
   }
   else if(el->getType() == "Class") {
      return getQualifiedName(graph, el);
   }
   else if(el->getType() == "PointerType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      return resolveType(graph, base) + "*";
   }
   else if(el->getType() == "ReferenceType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      return resolveType(graph, base) + "&";
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
      return resolveFunction(graph, el);
   }
   else if(el->getType() == "ArrayType") {
      gxl::Node *base = graph.findTailNodeOfType("BaseType", el);
      gxl::Node *size = graph.findTailNodeOfType("ArraySize", el);
      std::string result = resolveType(graph, base) + "[";
      if(size) {
         assert(size->getType() == "Literal");
         gxl::Attribute *attr = size->getAttribute("value");
         result += attr->asString();
      }
      return result + "]";
   }

   /* fallthrough */
   return el->getId() + "{" + el->getType() + "}";
}

std::string resolveFunction(gxl::Graph const& graph,
                            gxl::Node *f)
{
   bool isFuncPtr;
   std::string result;
   std::string qname;
   std::vector<gxl::Node*> params;
   std::vector<gxl::Node*>::const_iterator p;
   gxl::Node *node;
   gxl::Attribute *attr;
   bool first;

   isFuncPtr = (f->getType() == "FunctionPointer");

   if(isFuncPtr) {
      node = graph.findTailNodeOfType("ReturnType", f);
      if(node)
         result += resolveType(graph, node);
      result += " (*";
      /* Getting the function pointer's name isn't really needed.
         We don't retrieve the names of the other parameters, so
         why bother? */
      node = graph.findHeadNodeOfType("TypeOf", f);
      if(node) {
         attr = node->getAttribute("name");
         if(attr)
            result += attr->asString();
         else
            result += f->getId();
      }
      else
         result += f->getId();
   
      result += ")";
   }
   else {
      result += getQualifiedName(graph, f);
   }
   result += "(";
   params = graph.findTailNodesOfType("ParameterDeclaration", f);
   first = true;
   for(p = params.begin(); p != params.end(); ++p) {
      if(!first) result += ", ";
      node = graph.findTailNodeOfType("TypeOf", *p);
      result += resolveType(graph, node);
      first = false;
   }

   attr = f->getAttribute("variable_parameters");
   if(attr && attr->asBool())
      result += ", ...";

   result += ")";

   attr = f->getAttribute("is_const");
   if(attr && attr->asBool())
      result += " const";
   return result;
}

std::string getCaller(gxl::Graph const& graph,
                      gxl::Node *fc)
{
   /* This function assumes that a FunctionCallExpr won't
    * be the tail of more than one edge until it finds its caller. */
   std::vector<gxl::Node *> h = graph.findHeadNodesOfAnyType(fc);
   while(!h.empty()) {
      assert(h.size() == 1);
      if(h.at(0)->getType() == "Function"
           || h.at(0)->getType() == "Constructor"
           || h.at(0)->getType() == "Destructor"
           /* yes .. caller may be a variable initialization in a namespace */
           || h.at(0)->getType() == "GlobalNamespace"
           || h.at(0)->getType() == "Namespace")
         return h.at(0)->getId();
      h = graph.findHeadNodesOfAnyType(h.at(0));
   }
   assert(false);
   return "";
}

std::string getCallee(gxl::Graph const& graph,
                      gxl::Node *fc)
{
   gxl::Node *f = graph.findTailNodeOfType("FunctionDecl", fc);
   assert(f != NULL);

   while(f->getType() == "MemberAccess") {
      f = graph.findTailNodeOfType("Member", f);
   }
   return f->getId();
}

int main(int argc, char *argv[])
{
   std::string fn(argv[1]);
   gxl::Graph graph;
   std::vector<gxl::Node*> functionNodes;
   std::vector<gxl::Node*> namespaceNodes;
   std::vector<gxl::Node*>::const_iterator fp;
   std::map<std::string, std::string> functions;
   std::vector<gxl::Node*> callExprs;
   std::vector<gxl::Node*>::const_iterator cp;


   graph.parse(fn);
   namespaceNodes = graph.getAllNodesOfType("Namespace");
   functionNodes = graph.getAllNodesOfType("Function");
   concat(functionNodes, graph.getAllNodesOfType("Constructor"));
   concat(functionNodes, graph.getAllNodesOfType("Destructor"));
   concat(functionNodes, graph.getAllNodesOfType("PhantomReference"));
   std::cout << functionNodes.size() << " functions found."
             << std::endl;
   for(fp = functionNodes.begin(); fp != functionNodes.end(); ++fp) {
      std::string name = resolveFunction(graph, *fp);
      functions.insert(make_pair((*fp)->getId(), name));
   }

   functions.insert(make_pair(std::string("global"), std::string("[global]")));
   for(fp = namespaceNodes.begin(); fp != namespaceNodes.end(); ++fp) {
//      std::string name = resolveNamespace(graph, *fp);
//      functions.insert(make_pair((*fp)->getId(), name));
   }

   callExprs = graph.getAllNodesOfType("FunctionCallExpr");
   std::cout << callExprs.size() << " function calls found."
             << std::endl;
   for(cp = callExprs.begin(); cp != callExprs.end(); ++cp) {
      gxl::Node *dv = graph.findHeadNodeOfType("DefaultValue", *cp);
      if(dv != NULL) {
         /* XXX:  Bug in the ASG.  Function calls coming from default
          *   parameter values; ie. f(T x = g()); do not have a FunctionDecl
          *   node attached to the FunctionCallExpr */
         continue;
      }
 //   std::cout << "call expr: " << (*cp)->getId() << std::endl;
      std::string caller = getCaller(graph, *cp);
      std::string callee = getCallee(graph, *cp);   

//      if(functions[caller] == "") {
//        std::cout << "caller = " << caller << std::endl;
//        abort();
//      }
      if(functions[callee] == "") {
        std::cout << "callee = " << callee << std::endl;
        abort();
      }

      std::cout << "`" << functions[caller] << "` -> `" << functions[callee] << "`" << std::endl;
   }

   return EXIT_SUCCESS;
   
}
