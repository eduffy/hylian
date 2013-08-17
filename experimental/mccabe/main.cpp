
#include <llvm/Config/config.h>
#include <clang/Basic/Version.h>

#include <llvm/Support/CommandLine.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include "mccabe.h"

struct McCabeAction
   : public clang::ASTFrontendAction
   , public clang::ASTConsumer
{
   McCabeAction()
      : clang::ASTFrontendAction()
      , clang::ASTConsumer()
      , visitor(NULL)
   { }

   virtual ~McCabeAction()
   {
      delete visitor;
   }

   virtual clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &ci,
                                                 llvm::StringRef filename)
   {
      visitor = new McCabeVisitor(&ci.getASTContext());
      return this;
   }

   virtual void HandleTranslationUnit(clang::ASTContext &context)
   {
      visitor->TraverseDecl(context.getTranslationUnitDecl());
   }

   McCabeVisitor *visitor;
};

using clang::tooling::newFrontendActionFactory;
using clang::tooling::CommonOptionsParser;
using clang::tooling::ClangTool;

int main(int argc, const char *argv[])
{
   const char *addl[] = { "--"
                        /* FIXME:  There's got to be a better way to get system
                         *         header files than this. */
                        , "-I"LLVM_LIBDIR"/clang/"CLANG_VERSION_STRING"/include"
                        , };
   llvm::SmallVector<const char *, 16> args(argv, argv + argc);
   args.append(addl, addl + sizeof(addl) / sizeof(const char *));
   int nargs = args.size();
   CommonOptionsParser opts(nargs, args.data());
   ClangTool tool(opts.GetCompilations(),
                  opts.GetSourcePathList());
   return tool.run(newFrontendActionFactory<McCabeAction>());
}

