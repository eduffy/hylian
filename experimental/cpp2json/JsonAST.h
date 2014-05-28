
#ifndef JSON_AST_H
#define JSON_AST_H

#include <map>
#include <list>
#include <string>
#include <iostream>

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>


class JsonASTNode
{
public:
   JsonASTNode() { }
   virtual ~JsonASTNode() { }
   virtual std::ostream &Print(std::ostream &) const = 0;
};

class JsonASTString
   : public JsonASTNode
{
public:
   JsonASTString(std::string const& v) : value(v) { }
   std::ostream &Print(std::ostream &os) const;
private:
   std::string value;
};

class JsonASTInt
   : public JsonASTNode
{
public:
   JsonASTInt(int v) : value(v) { }
   std::ostream &Print(std::ostream &os) const;
private:
   int value;
};

class JsonASTList
   : public JsonASTNode
{
public:
   void append(JsonASTNode *value);
   void append(std::string const& value);
   std::ostream &Print(std::ostream &os) const;
private:
   std::list<JsonASTNode *> values;
};

class JsonASTObject
   : public JsonASTNode
{
public:
   JsonASTObject(clang::Stmt *obj = NULL);
   void insert(std::string const& key, JsonASTNode *value);
   void insert(std::string const& key, std::string const& value);
   void insert(std::string const& key, int value);
   void insert(const char *key, JsonASTNode *value);
   std::ostream &Print(std::ostream &os) const;
private:
   std::map<std::string, JsonASTNode *> values;
};

#endif  /* JSON_AST_H */
