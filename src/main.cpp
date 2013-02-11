
#include <unistd.h>
#include <iostream>
#include <llvm/Config/config.h>
#include <llvm/Support/CrashRecoveryContext.h>
#include <llvm/Support/Path.h>
#include <clang/Basic/Version.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Parse/ParseAST.h>
#include "HylianASTConsumer.h"

std::string sharepath;

void getSharePath(const char *argv0)
{
   char exepath[PATH_MAX];
   realpath(argv0, exepath);

   llvm::sys::Path path(exepath);
   llvm::sys::Path sp(llvm::sys::path::parent_path(
      llvm::sys::path::parent_path(exepath)));
   sp.appendComponent("share");
   sp.appendComponent("hylian");
   sharepath = sp.str();
}

std::string replaceExtension(std::string const& fn)
{
   std::string result(fn);

   if(result.find_last_of("/") != std::string::npos) {
      result.erase(0, 1 + result.find_last_of("/"));
   }
   if(result.substr(result.find_last_of(".")) == ".cpp") {
      result.erase(result.find_last_of("."));
   }
   result.append(".db");
   return result;
}

int main(int argc, char *argv[])
{
   llvm::cl::SetVersionPrinter(NULL);
   getSharePath(argv[0]);

   // Using LLVM's command parser throws a lot of backend/architecture options that
   // we won't use.  But that'll help maintain command-line compatability, so we
   // can be a drop-in replacement for g++ and clang++.
   llvm::cl::opt<std::string>  outputFilename("o", llvm::cl::desc("Output filename"), llvm::cl::value_desc(".db file"));
   llvm::cl::opt<bool>         compileOnly("c", llvm::cl::desc("Compile only"), llvm::cl::value_desc(""));
   llvm::cl::list<std::string> inputFilenames(llvm::cl::Positional, llvm::cl::desc("<C++ files>"));
   llvm::cl::ParseCommandLineOptions(argc, argv, "hylian-c++");
   
   if(outputFilename == "") {
      if(inputFilenames.size() == 1) {
         outputFilename = replaceExtension(inputFilenames[0]);
      }
      else {
         outputFilename = "a.db";
      }
   }

   if(access(outputFilename.c_str(), F_OK) == 0) {
      unlink(outputFilename.c_str());
   }
   HylianASTConsumer *hylian = new HylianASTConsumer(outputFilename);

   llvm::DisablePrettyStackTrace = false;
   llvm::CrashRecoveryContext::Enable();

   const char *args[] = {
      inputFilenames[0].c_str(),
//      "-fspell-checking",
   }, **argsEnd = &args[sizeof(args) / sizeof(void *)];

   clang::CompilerInstance compiler;
   clang::DiagnosticOptions *diagOpts = new clang::DiagnosticOptions();
   clang::TextDiagnosticPrinter *DiagClient =
      new clang::TextDiagnosticPrinter(llvm::errs(), diagOpts);
   llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> DiagID(new clang::DiagnosticIDs());
   clang::DiagnosticsEngine Diags(DiagID, diagOpts);


   compiler.createDiagnostics(argsEnd - args, args);
   clang::CompilerInvocation::CreateFromArgs(compiler.getInvocation(), args, argsEnd, Diags);
   compiler.setTarget(clang::TargetInfo::CreateTargetInfo(Diags, compiler.getTargetOpts()));

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
   compiler.setASTConsumer(hylian);
   compiler.createSema(clang::TU_Complete, NULL);

   compiler.InitializeSourceManager(inputFilenames[0]);
   ParseAST(pp, &compiler.getASTConsumer(), compiler.getASTContext());
   
   return EXIT_SUCCESS;
}
