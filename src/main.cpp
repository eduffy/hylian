
#include <iostream>
#include <llvm/Config/config.h>
#include <llvm/Support/CrashRecoveryContext.h>
#include <clang/Basic/Version.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTUnit.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Index/Program.h>
#include <clang/Index/Indexer.h>
/*
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
*/
#include <clang/Parse/ParseAST.h>
#include "HylianASTConsumer.h"

#if 0
class HylianConsumer : public clang::ASTConsumer
{
public:
   virtual void HandleTopLevelDecl(clang::DeclGroupRef declGroup)
   {
      for(clang::DeclGroupRef::iterator i = declGroup.begin(); i != declGroup.end(); ++i) {
         const clang::Decl *decl = clang::dyn_cast<clang::Decl>(*i);
         switch(decl->getKind()) {
           case clang::Decl::AccessSpec: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Block: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::ClassScopeFunctionSpecialization: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::FileScopeAsm: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Friend: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::FriendTemplate: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::LinkageSpec: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Label: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Namespace:
              HandleNamespaceDecl(clang::dyn_cast<clang::NamespaceDecl>(*i));
              break;
           case clang::Decl::NamespaceAlias: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::ClassTemplate: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::FunctionTemplate: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::TypeAliasTemplate: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::TemplateTemplateParm: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Enum: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Record: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::CXXRecord: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::ClassTemplateSpecialization: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::ClassTemplatePartialSpecialization: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::TemplateTypeParm: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::TypeAlias: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Typedef: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::UnresolvedUsingTypename: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Using: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::UsingDirective: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::UsingShadow: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Field: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Function:
              HandleFunctionDecl(clang::dyn_cast<clang::FunctionDecl>(*i));
              break;
           case clang::Decl::CXXMethod:
              HandleCXXMethodDecl(clang::dyn_cast<clang::CXXMethodDecl>(*i));
              break;
           case clang::Decl::CXXConstructor: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::CXXConversion: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::CXXDestructor: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::NonTypeTemplateParm: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::Var: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::ImplicitParam: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::ParmVar: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::EnumConstant: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::IndirectField: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::UnresolvedUsingValue: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::StaticAssert: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }
           case clang::Decl::TranslationUnit: {
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
              break;
           }

           // Put Objective-C declarations in here to avoid warnings
           case clang::Decl::ObjCCompatibleAlias:
           case clang::Decl::ObjCCategory:
           case clang::Decl::ObjCCategoryImpl:
           case clang::Decl::ObjCImplementation:
           case clang::Decl::ObjCInterface:
           case clang::Decl::ObjCProtocol:
           case clang::Decl::ObjCMethod:
           case clang::Decl::ObjCProperty:
           case clang::Decl::ObjCAtDefsField:
           case clang::Decl::ObjCIvar:
           case clang::Decl::ObjCClass:
           case clang::Decl::ObjCForwardProtocol:
           case clang::Decl::ObjCPropertyImpl:
           default: {
              if(const clang::NamedDecl *ND = clang::dyn_cast<clang::NamedDecl>(*i)) {
                 std::cout << "top-level-decl: \"" << ND->getQualifiedNameAsString() << "\"" << std::endl;
              }
              std::cout << "Unknown declaration of type `" << decl->getDeclKindName() << "' (" << decl->getKind() << ")." << std::endl;
           }
         }
      }
   }
private:
   void HandleNamespaceDecl(clang::NamespaceDecl *ns)
   {
      std::cout << "Namespace `" << ns->getQualifiedNameAsString() << "'" << std::endl;
      for(clang::DeclContext::decl_iterator p = ns->decls_begin(); p != ns->decls_end(); ++p) {
         std::cout << "\t" << (*p)->getDeclKindName() << "\t";
         if(clang::NamedDecl *nd = clang::dyn_cast<clang::NamedDecl>(*p)) {
            std::cout << nd->getQualifiedNameAsString();
            if(clang::VarDecl *v = clang::dyn_cast<clang::VarDecl>(*p)) {
               std::cout << "\t" << v->getType().getAsString();
            }
         }
         std::cout << std::endl;
      }
   }

   void HandleFunctionDecl(clang::FunctionDecl *f)
   {
      std::cout << "Function `" << f->getQualifiedNameAsString() << "':" << std::endl;
      std::cout << "\tResult type:     " << f->getResultType().getAsString() << std::endl;
      std::cout << "\tNum. parameters: " << f->getNumParams() << std::endl;
      for(clang::FunctionDecl::param_const_iterator p = f->param_begin(); p != f->param_end(); ++p) {
         std::cout << "\t\t" << (*p)->getQualifiedNameAsString() << " :: " << (*p)->getOriginalType().getAsString() << std::endl;
      }
      if(f->hasBody()) {
         clang::Stmt *statement = f->getBody();
         for(clang::Stmt::const_child_iterator s = statement->child_begin(); s != statement->child_end(); ++s) {
            std::cout << "\t" << (*s)->getStmtClassName() << std::endl;
         }
      }
   }

   void HandleCXXMethodDecl(clang::CXXMethodDecl *f)
   {
      std::cout << "C++ Method `" << f->getQualifiedNameAsString() << "':" << std::endl;
      std::cout << "\tResult type:     " << f->getResultType().getAsString() << std::endl;
      std::cout << "\tNum. parameters: " << f->getNumParams() << std::endl;
      for(clang::FunctionDecl::param_const_iterator p = f->param_begin(); p != f->param_end(); ++p) {
         std::cout << "\t\t" << (*p)->getQualifiedNameAsString() << " :: " << (*p)->getOriginalType().getAsString() << std::endl;
      }
   }
};
#endif


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
//   clang::HeaderSearch headerSearch(compiler.getFileManager());


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
