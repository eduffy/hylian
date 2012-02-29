
#include <llvm/Config/config.h>
#include <llvm/Support/CrashRecoveryContext.h>
#include <clang/Basic/Version.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Parse/ParseAST.h>
#include "HylianASTConsumer.h"

int main(int argc, char *argv[])
{
   llvm::cl::SetVersionPrinter(NULL);

   // Using LLVM's command parser throws a lot of backend/architecture options that
   // we won't use.  But that'll help maintain command-line compatability, so we
   // can be a drop-in replacement for g++ and clang++.
   llvm::cl::list<std::string> inputFilenames(llvm::cl::Positional, llvm::cl::desc("<C++ files>"));
   llvm::cl::ParseCommandLineOptions(argc, argv, "hylian-c++");
   
   llvm::DisablePrettyStackTrace = false;
   llvm::CrashRecoveryContext::Enable();

   const char *args[] = {
      inputFilenames[0].c_str(),
//      "-fspell-checking",
   }, **argsEnd = &args[sizeof(args) / sizeof(void *)];

   clang::CompilerInstance compiler;

   compiler.createDiagnostics(argc, argv);
   clang::CompilerInvocation::CreateFromArgs(compiler.getInvocation(), args, argsEnd, compiler.getDiagnostics());
   compiler.setTarget(clang::TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), compiler.getTargetOpts()));

   compiler.createFileManager();
   compiler.createSourceManager(compiler.getFileManager());

   // Set up header file search path.
   // 1. Standard C header files
   compiler.getHeaderSearchOpts().AddPath("/usr/include",
      clang::frontend::CXXSystem, false, false, false);
   compiler.getHeaderSearchOpts().AddPath("/usr/include/bits",
      clang::frontend::CXXSystem, false, false, false);
   // 2. clang's internal header files
   compiler.getHeaderSearchOpts().AddPath(LLVM_LIBDIR"/clang/"CLANG_VERSION_STRING"/include",
      clang::frontend::CXXSystem, false, false, false);
   // 3. GCC C++ header files
   compiler.getHeaderSearchOpts().AddPath("/usr/include/c++/"GCC_VERSION,
      clang::frontend::CXXSystem, false, false, false);
   compiler.getHeaderSearchOpts().AddPath("/usr/include/c++/"GCC_VERSION"/tr1",
      clang::frontend::CXXSystem, false, false, false);
   compiler.getHeaderSearchOpts().AddPath("/usr/include/c++/"GCC_VERSION"/parallel",
      clang::frontend::CXXSystem, false, false, false);
   compiler.getHeaderSearchOpts().AddPath("/usr/include/c++/"GCC_VERSION"/"GCC_MACHINE,
      clang::frontend::CXXSystem, false, false, false);

   compiler.createPreprocessor();
   clang::Preprocessor &pp = compiler.getPreprocessor();
   pp.getBuiltinInfo().InitializeBuiltins(pp.getIdentifierTable(), pp.getLangOptions());

   compiler.createASTContext();
   compiler.setASTConsumer(new HylianASTConsumer());
   compiler.createSema(clang::TU_Complete, NULL);

   compiler.InitializeSourceManager(inputFilenames[0]);
   ParseAST(pp, &compiler.getASTConsumer(), compiler.getASTContext());
   
   return EXIT_SUCCESS;
}
