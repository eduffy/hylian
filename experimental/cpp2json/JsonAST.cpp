
#include "JsonAST.h"

std::ostream &JsonASTString::Print(std::ostream &os) const
{
   return os << "\"" << value << "\"";
}

void JsonASTList::append(JsonASTNode *value)
{
   values.push_back(value);
}

std::ostream &JsonASTList::Print(std::ostream &os) const
{
   os << "[";
   for(std::list<JsonASTNode *>::const_iterator p = values.begin();
                                                p != values.end();
                                                ++p)
   {
      if(p != values.begin()) os << ",";
      (*p)->Print(os);
   }
   return os << "]";
}

JsonASTObject::JsonASTObject(clang::Stmt *obj)
{
   if(obj != NULL) {
      insert("Kind", obj->getStmtClassName());
   }
}

void JsonASTObject::insert(std::string const& key, JsonASTNode *value)
{
   values.insert(std::make_pair(key, value));
}

void JsonASTObject::insert(std::string const& key, std::string const& value)
{
   insert(key, new JsonASTString(value));
}

void JsonASTObject::insert(const char *key, JsonASTNode *value)
{
   insert(std::string(key), value);
}

std::ostream &JsonASTObject::Print(std::ostream &os) const
{
   os << "{";
   for(std::map<std::string, JsonASTNode *>::const_iterator p = values.begin();
                                                            p != values.end();
                                                            ++p)
   {
      if(p != values.begin()) os << ",";
      os << "\"" << p->first << "\":";
      if(p->second)
         p->second->Print(os);
      else
         os << "null";
   }
   return os << "}";
}

