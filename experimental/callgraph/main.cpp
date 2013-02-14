
#include <llvm/Config/config.h>
#include <clang/Basic/Version.h>

#include <llvm/Support/CommandLine.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include "callgraph.h"


using clang::ASTFrontendAction;
using clang::ASTConsumer;
using clang::CompilerInstance;

class CallgraphAction 
   : public ASTFrontendAction
{
public:
   virtual ASTConsumer *CreateASTConsumer(CompilerInstance &CI,
                                          llvm::StringRef InFile)
   {
      return new HylianASTConsumer;
   }
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
   CommonOptionsParser opts(nargs, (args.data()));
   ClangTool tool(opts.GetCompilations(),
                  opts.GetSourcePathList());
   return tool.run(newFrontendActionFactory<CallgraphAction>());
}

