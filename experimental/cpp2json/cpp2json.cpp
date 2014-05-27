
#include <string>
#include <cstdio>
#include <iostream>
#include <stdarg.h>

#include "cpp2json.h"

CppToJsonVisitor::CppToJsonVisitor(clang::ASTContext *context)
{
}

std::string CppToJsonVisitor::getQualifiedName(const clang::Decl *decl)
{
   const clang::FunctionDecl *f = clang::dyn_cast<const clang::FunctionDecl>(decl);
   std::string result = f->getQualifiedNameAsString() + "(";
   bool first = true;
   clang::FunctionDecl::param_const_iterator pi;
   for (pi = f->param_begin(); pi != f->param_end(); ++pi)
   {
      if(!first)
         result += ", ";
      result += (*pi)->getType().getAsString();
      first = false;
   }
   if(f->isVariadic())
      result += ", ...";
   result += ")";

   if(clang::CXXMethodDecl::classof(f)) 
   {
      const clang::CXXMethodDecl *method = 
         clang::dyn_cast<const clang::CXXMethodDecl>(f);
      clang::ASTContext &context = method->getParentASTContext();
      if(method->isStatic())
         result = "static " + result;
      if(method->isVolatile())
         result += " volatile";
      if(method->isConst())
         result += " const";
   }

   return result;
}

JsonASTNode *CppToJsonVisitor::StmtToJson(clang::Stmt *stmt)
{
   if(stmt == NULL)
      return NULL;
   TraverseStmt(stmt);
   JsonASTNode *result = buildStack.top();
   buildStack.pop();
   return result;
}

JsonASTObject *CppToJsonVisitor::GenericTraverseDecl(clang::Decl *decl)
{
   JsonASTObject *result = new JsonASTObject;

   result->insert("Kind", std::string(decl->getDeclKindName()) + "Decl");

   if(clang::NamedDecl *p = clang::dyn_cast<clang::NamedDecl>(decl))
      result->insert("name", p->getNameAsString());

   if(clang::TypedefNameDecl *p = clang::dyn_cast<clang::TypedefNameDecl>(decl))
     result->insert("type", p->getTypeSourceInfo()->getType().getAsString());

   if(clang::VarDecl *p = clang::dyn_cast<clang::VarDecl>(decl))
      result->insert("init", StmtToJson(p->getInit()));

   return result;
}

bool CppToJsonVisitor::GenericTraverseStmt(clang::Stmt *stmt, ...)
{
   va_list ap;
   const char *name;
   clang::Stmt::child_iterator cp = stmt->child_begin();
   JsonASTObject *result = new JsonASTObject(stmt);

   va_start(ap, stmt);
   name = va_arg(ap, const char *);
   while(name != NULL) {
      result->insert(name, StmtToJson(*cp));
      name = va_arg(ap, const char *);
      ++cp;
   }
   va_end(ap);
   buildStack.push(result);

   return true;
}

bool CppToJsonVisitor::TraverseTranslationUnitDecl(clang::TranslationUnitDecl *decl)
{
   JsonASTList *decls = new JsonASTList;
   clang::DeclContext::decl_iterator di;
   for(di = decl->decls_begin(); di != decl->decls_end(); ++di) {
      int stackSize = buildStack.size();
      TraverseDecl(*di);
      if(stackSize + 1 != buildStack.size()) {
         /* std::cerr << "Unknown declaration type " << ((clang::Decl*)*di)->getDeclKindName() << "Decl" << std::endl; */
         continue;
      }
      decls->append(buildStack.top());
      buildStack.pop();
   }

   JsonASTObject *result = new JsonASTObject;
   result->insert("Kind",  std::string(((clang::Decl *)decl)->getDeclKindName()) + "Decl");
   result->insert("decls", decls);
   buildStack.push(result);

   return true;
}

bool CppToJsonVisitor::TraverseTypedefDecl(clang::TypedefDecl *decl)
{
   buildStack.push(GenericTraverseDecl(decl));
   return true;
}

bool CppToJsonVisitor::TraverseIntegerLiteral(clang::IntegerLiteral *lit)
{
   JsonASTObject *result = new JsonASTObject(lit);
   result->insert("value", lit->getValue().toString(10, true));
   buildStack.push(result);
   return true;
}

bool CppToJsonVisitor::TraverseDeclStmt(clang::DeclStmt *stmt)
{
   JsonASTList *decls = new JsonASTList;
   clang::DeclStmt::decl_iterator di;
   for(di = stmt->decl_begin(); di != stmt->decl_end(); ++di) {
      JsonASTObject *decl = new JsonASTObject;
      decl->insert("Kind", std::string((*di)->getDeclKindName()) + "Decl");
      if(clang::NamedDecl *p = clang::dyn_cast<clang::NamedDecl>(*di))
         decl->insert("name", p->getNameAsString());
      if(clang::ValueDecl *p = clang::dyn_cast<clang::ValueDecl>(*di))
         decl->insert("type", p->getType().getAsString());
      if(clang::VarDecl *p = clang::dyn_cast<clang::VarDecl>(*di)) {
         decl->insert("init", StmtToJson(p->getInit()));
      }
      decls->append(decl);
   }
   JsonASTObject *result = new JsonASTObject(stmt);
   result->insert("decls", decls);
   buildStack.push(result);
   return true;
}

bool CppToJsonVisitor::TraverseNullStmt(clang::NullStmt *stmt)
{
   return GenericTraverseStmt(stmt, NULL);
}

bool CppToJsonVisitor::TraverseIfStmt(clang::IfStmt *stmt)
{
   return GenericTraverseStmt(stmt, "var", "condition", "then", "else", NULL);
}

bool CppToJsonVisitor::TraverseForStmt(clang::ForStmt *stmt)
{
   return GenericTraverseStmt(stmt, "init", "condvar", "cond", "inc", "body", NULL);
}

bool CppToJsonVisitor::TraverseSwitchStmt(clang::SwitchStmt *stmt)
{
   return GenericTraverseStmt(stmt, "var", "cond", "body", NULL);
}

bool CppToJsonVisitor::TraverseCaseStmt(clang::CaseStmt *stmt)
{
   return GenericTraverseStmt(stmt, "lhs", "rhs", "subStmt", NULL);
}

bool CppToJsonVisitor::TraverseWhileStmt(clang::WhileStmt *stmt)
{
   return GenericTraverseStmt(stmt, "var", "cond", "body", NULL);
}

bool CppToJsonVisitor::TraverseDoStmt(clang::DoStmt *stmt)
{
   return GenericTraverseStmt(stmt, "body", "cond", NULL);
}

bool CppToJsonVisitor::TraverseReturnStmt(clang::ReturnStmt *stmt)
{
   return GenericTraverseStmt(stmt, "retValue", NULL);
}

bool CppToJsonVisitor::TraverseCompoundStmt(clang::CompoundStmt *stmt)
{
   JsonASTObject *result = new JsonASTObject(stmt);
   JsonASTList   *body   = new JsonASTList();
   clang::CompoundStmt::body_iterator i;
   for(i = stmt->body_begin(); i != stmt->body_end(); i++) {
      body->append(StmtToJson(*i));
   }
   result->insert("body", body);
   buildStack.push(result);
   return true;
}

bool CppToJsonVisitor::TraverseDeclRefExpr(clang::DeclRefExpr *expr)
{
   JsonASTObject *result = new JsonASTObject(expr);
   result->insert("name", expr->getFoundDecl()->getNameAsString());
   buildStack.push(result);
   return true;
}

bool CppToJsonVisitor::TraverseFunctionDecl(clang::FunctionDecl *decl)
{
   JsonASTObject *result = new JsonASTObject;
   JsonASTList   *params = new JsonASTList;

   clang::FunctionDecl::param_const_iterator p;
   for(p = decl->param_begin(); p != decl->param_end(); p++) {
      JsonASTObject *obj = new JsonASTObject;
      obj->insert("name", (*p)->getQualifiedNameAsString());
      obj->insert("type", (*p)->getType().getAsString());
      params->append(obj);
   }

   result->insert("Kind",       "FunctionDecl");
   result->insert("returnType", decl->getResultType().getAsString());
   result->insert("name",       decl->getNameInfo().getName().getAsString());
   result->insert("body",       StmtToJson(decl->getBody()));
   result->insert("params",     params);
   buildStack.push(result);
 
   return true;
}

bool CppToJsonVisitor::GenericTraverseUnaryOperator(clang::UnaryOperator *expr)
{
   JsonASTObject *result = new JsonASTObject(expr);
   result->insert("op", clang::UnaryOperator::getOpcodeStr(expr->getOpcode()).str());
   result->insert("subExpr", StmtToJson(expr->getSubExpr()));
   buildStack.push(result);
   return true;
}

#define OPERATOR(NAME) \
  bool CppToJsonVisitor::TraverseUnary##NAME(clang::UnaryOperator *expr) \
  { return GenericTraverseUnaryOperator(expr); }
UNARYOP_LIST()
#undef OPERATOR

bool CppToJsonVisitor::GenericTraverseBinaryOperator(clang::BinaryOperator *expr)
{
   JsonASTObject *result = new JsonASTObject(expr);
   result->insert("op",  clang::BinaryOperator::getOpcodeStr(expr->getOpcode()).str());
   result->insert("lhs", StmtToJson(expr->getLHS()));
   result->insert("rhs", StmtToJson(expr->getRHS()));
   buildStack.push(result);
   return true;
}

#define OPERATOR(NAME) \
  bool CppToJsonVisitor::TraverseBin##NAME(clang::BinaryOperator *expr) \
  { return GenericTraverseBinaryOperator(expr); }
BINOP_LIST()
#undef OPERATOR

#define OPERATOR(NAME) \
  bool CppToJsonVisitor::TraverseBin##NAME##Assign(clang::CompoundAssignOperator *expr) \
  { return GenericTraverseBinaryOperator(expr); }
CAO_LIST()
#undef OPERATOR

