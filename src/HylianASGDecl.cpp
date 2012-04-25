
#include <iostream>
#include "HylianASG.h"

void HylianASG::AddPrettyStackTraceDecl(const clang::PrettyStackTraceDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddAnyFunctionDecl(const clang::AnyFunctionDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddAccessSpecDecl(const clang::AccessSpecDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddCXXRecordDecl(const clang::CXXRecordDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddCXXMethodDecl(const clang::CXXMethodDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddCXXConstructorDecl(const clang::CXXConstructorDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddCXXDestructorDecl(const clang::CXXDestructorDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddCXXConversionDecl(const clang::CXXConversionDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddLinkageSpecDecl(const clang::LinkageSpecDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddUsingDirectiveDecl(const clang::UsingDirectiveDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddNamespaceAliasDecl(const clang::NamespaceAliasDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddUsingShadowDecl(const clang::UsingShadowDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddUsingDecl(const clang::UsingDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddUnresolvedUsingValueDecl(const clang::UnresolvedUsingValueDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddUnresolvedUsingTypenameDecl(const clang::UnresolvedUsingTypenameDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddStaticAssertDecl(const clang::StaticAssertDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddFriendDecl(const clang::FriendDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTranslationUnitDecl(const clang::TranslationUnitDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddNamedDecl(const clang::NamedDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddLabelDecl(const clang::LabelDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddNamespaceDecl(const clang::NamespaceDecl *decl, clang::Decl *parent)
{
   std::cout << "Namespace `" << decl->getQualifiedNameAsString() << "'" << std::endl;
   for(clang::DeclContext::decl_iterator p = decl->decls_begin(); p != decl->decls_end(); ++p) {
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

void HylianASG::AddValueDecl(const clang::ValueDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddDeclaratorDecl(const clang::DeclaratorDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddVarDecl(const clang::VarDecl *decl, clang::Decl *parent)
{
std::cout << "VARIABLE decl" << std::endl;
   HandleExpression(decl->getInit());
}

void HylianASG::AddImplicitParamDecl(const clang::ImplicitParamDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddParmVarDecl(const clang::ParmVarDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddFunctionDecl(const clang::FunctionDecl *decl, clang::Decl *parent)
{
      std::cout << "Function `" << decl->getQualifiedNameAsString() << "':" << std::endl;
      std::cout << "\tResult type:     " << decl->getResultType().getAsString() << std::endl;
      std::cout << "\tNum. parameters: " << decl->getNumParams() << std::endl;
      for(clang::FunctionDecl::param_const_iterator p = decl->param_begin(); p != decl->param_end(); ++p) {
         std::cout << "\t\t" << (*p)->getQualifiedNameAsString() << " :: " << (*p)->getOriginalType().getAsString() << std::endl;
      }
      if(decl->hasBody()) {
         clang::Stmt *statement = decl->getBody();
         int i = 1;
         for(clang::Stmt::const_child_iterator s = statement->child_begin();
             s != statement->child_end();
             ++s, ++i)
         {
            HandleStatement(*s);
            std::cout << "\t" << i << ".| " << (*s)->getStmtClassName() << std::endl;
         }
      }
}

void HylianASG::AddFieldDecl(const clang::FieldDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddEnumConstantDecl(const clang::EnumConstantDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddIndirectFieldDecl(const clang::IndirectFieldDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTypeDecl(const clang::TypeDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTypedefNameDecl(const clang::TypedefNameDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTypedefDecl(const clang::TypedefDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTypeAliasDecl(const clang::TypeAliasDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddEnumDecl(const clang::EnumDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddRecordDecl(const clang::RecordDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddFileScopeAsmDecl(const clang::FileScopeAsmDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddBlockDecl(const clang::BlockDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTemplateDecl(const clang::TemplateDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddRedeclarableTemplateDecl(const clang::RedeclarableTemplateDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddFunctionTemplateDecl(const clang::FunctionTemplateDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTemplateTypeParmDecl(const clang::TemplateTypeParmDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddClassTemplateDecl(const clang::ClassTemplateDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddFriendTemplateDecl(const clang::FriendTemplateDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddTypeAliasTemplateDecl(const clang::TypeAliasTemplateDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddClassScopeFunctionSpecializationDecl(const clang::ClassScopeFunctionSpecializationDecl *decl, clang::Decl *parent)
{
}

void HylianASG::AddGlobalDecl(const clang::GlobalDecl *decl, clang::Decl *parent)
{
}

