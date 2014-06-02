
#include <fstream>
#include <iostream>
#include <llvm/Config/config.h>
#include <clang/Basic/Version.h>
#include <clang/Basic/SourceManager.h>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticBuffer.h>
#include <llvm/Support/CommandLine.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include "cpp2json.h"

struct CppToJsonConsumer
   : public clang::ASTConsumer
{
   CppToJsonConsumer(clang::CompilerInstance &ci)
      : clang::ASTConsumer()
      , visitor(new CppToJsonVisitor(&ci.getASTContext()))
   { }

   virtual ~CppToJsonConsumer()
   {
      delete visitor;
   }

   virtual void HandleTranslationUnit(clang::ASTContext &context);
   CppToJsonVisitor *getVisitor() { return visitor; }
   void setAction(struct CppToJsonAction *a) { action = a; }

   CppToJsonVisitor *visitor;
   struct CppToJsonAction *action;
};

struct CppToJsonAction
   : public clang::ASTFrontendAction
{
   CppToJsonAction()
      : clang::ASTFrontendAction()
      , consumer(NULL)
   { }

   virtual ~CppToJsonAction()
   {
      // segfaults if you delete this
      // delete consumer;
   }

   virtual clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &ci,
                                                 llvm::StringRef filename)
   {
      sourceManager = &ci.getSourceManager();
      sourceManager->Retain();
      consumer = new CppToJsonConsumer(ci);
      consumer->setAction(this);
      return consumer;
   }
   CppToJsonConsumer *getConsumer() { return consumer; }
   void setAST(JsonASTNode *a) { AST = a; }
   JsonASTNode *getAST() { return AST; }
   clang::SourceManager &getSourceManager() { return *sourceManager; }

   CppToJsonConsumer *consumer;
   clang::SourceManager *sourceManager;
   JsonASTNode *AST;
};

class CppToJsonFrontendActionFactory
   : public clang::tooling::FrontendActionFactory
{
public:
   clang::FrontendAction *create() { return (action = new CppToJsonAction); }
   CppToJsonAction *getAction() { return action; }
private:
   CppToJsonAction *action;
};

void CppToJsonConsumer::HandleTranslationUnit(clang::ASTContext &context)
{
   visitor->TraverseDecl(context.getTranslationUnitDecl());
   action->setAST(visitor->getAST());
}

using clang::tooling::newFrontendActionFactory;
using clang::tooling::CommonOptionsParser;
using clang::tooling::ClangTool;
namespace cl = llvm::cl;

cl::opt<std::string> OutputFilename("o", cl::desc("Specify output filename"), cl::value_desc("filename"));

int main(int argc, const char *argv[])
{
   const char *addl[] = { "--"
                        /* FIXME:  There's got to be a better way to get system
                         *         header files than this. */
                        , "-I"LLVM_PREFIX"/lib/clang/"CLANG_VERSION_STRING"/include"
                        , "-Wall", "-x", "c++"
                        };
   llvm::SmallVector<const char *, 16> args(argv, argv + argc);
   args.append(addl, addl + sizeof(addl) / sizeof(const char *));
   int nargs = args.size();
   CommonOptionsParser opts(nargs, args.data());
   ClangTool tool(opts.getCompilations(),
                  opts.getSourcePathList());

   clang::TextDiagnosticBuffer diag;
   CppToJsonFrontendActionFactory factory;
   tool.setDiagnosticConsumer(&diag);
   int rescode = tool.run(&factory);

   JsonASTObject result;
   JsonASTList   warnings, errors;
   clang::TextDiagnosticBuffer::const_iterator di;
   clang::SourceManager &SM = factory.getAction()->getSourceManager();

   for(di = diag.warn_begin(); di != diag.warn_end(); ++di) {
      JsonASTObject *w = new JsonASTObject;
      clang::PresumedLoc pl = SM.getPresumedLoc(di->first);

      w->insert("message", di->second);
      w->insert("line",    pl.getLine());
      w->insert("column",  pl.getColumn());
      warnings.append(w);
   }
   for(di = diag.err_begin(); di != diag.err_end(); ++di) {
      JsonASTObject *e = new JsonASTObject;
      clang::PresumedLoc pl = SM.getPresumedLoc(di->first);

      e->insert("message", di->second);
      e->insert("line",    pl.getLine());
      e->insert("column",  pl.getColumn());
      errors.append(e);
   }

   result.insert("AST",      factory.getAction()->getAST());
   result.insert("Warnings", &warnings);
   result.insert("Errors",   &errors);

   if(OutputFilename == "" || OutputFilename == "-") {
      result.Print(std::cout);
   }
   else {
      std::ofstream output(OutputFilename.c_str());
      result.Print(output);
      output.close();
   }

   return 0;
}

