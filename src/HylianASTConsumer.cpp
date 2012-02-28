
#include <iostream>
#include "HylianASTConsumer.h"

void HylianASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef declGroup)
{
   for(clang::DeclGroupRef::iterator i = declGroup.begin(); i != declGroup.end(); ++i)
   {
      const clang::Decl *decl = clang::dyn_cast<clang::Decl>(*i);
      switch(decl->getKind()) {
         case clang::Decl::Namespace:
            asg.AddNamespaceDecl(clang::dyn_cast<clang::NamespaceDecl>(decl), NULL);
            break;

         case clang::Decl::Function:
            asg.AddFunctionDecl(clang::dyn_cast<clang::FunctionDecl>(decl), NULL);
            break;

         case clang::Decl::CXXMethod:
            asg.AddCXXMethodDecl(clang::dyn_cast<clang::CXXMethodDecl>(decl), NULL);
            break;

         case clang::Decl::Var:
            asg.AddVarDecl(clang::dyn_cast<clang::VarDecl>(decl), NULL);
            break;


//         case clang::Decl::PrettyStackTrace:
//         case clang::Decl::AnyFunction:
         case clang::Decl::AccessSpec:
         case clang::Decl::CXXRecord:
         case clang::Decl::CXXConstructor:
         case clang::Decl::CXXDestructor:
         case clang::Decl::CXXConversion:
         case clang::Decl::LinkageSpec:
         case clang::Decl::UsingDirective:
         case clang::Decl::NamespaceAlias:
         case clang::Decl::UsingShadow:
         case clang::Decl::Using:
         case clang::Decl::UnresolvedUsingValue:
         case clang::Decl::UnresolvedUsingTypename:
         case clang::Decl::StaticAssert:
         case clang::Decl::Friend:
         case clang::Decl::TranslationUnit:
//         case clang::Decl::Named:
         case clang::Decl::Label:
//         case clang::Decl::Value:
//         case clang::Decl::Declarator:
         case clang::Decl::ImplicitParam:
         case clang::Decl::ParmVar:
         case clang::Decl::Field:
         case clang::Decl::EnumConstant:
         case clang::Decl::IndirectField:
//         case clang::Decl::Type:
//         case clang::Decl::TypedefName:
         case clang::Decl::Typedef:
         case clang::Decl::TypeAlias:
         case clang::Decl::Enum:
         case clang::Decl::Record:
         case clang::Decl::FileScopeAsm:
         case clang::Decl::Block:
//         case clang::Decl::Template:
//         case clang::Decl::RedeclarableTemplate:
         case clang::Decl::FunctionTemplate:
         case clang::Decl::TemplateTypeParm:
         case clang::Decl::ClassTemplate:
         case clang::Decl::FriendTemplate:
         case clang::Decl::TypeAliasTemplate:
         case clang::Decl::TemplateTemplateParm:
         case clang::Decl::ClassTemplateSpecialization:
         case clang::Decl::ClassTemplatePartialSpecialization:
         case clang::Decl::NonTypeTemplateParm:
         case clang::Decl::ClassScopeFunctionSpecialization:

         {
            std::cerr << "Unknown declaration of type `" << decl->getDeclKindName()
                      << "' (" << decl->getKind() << ")." << std::endl;
         }

         // Prevent warnings about missing enums
         case clang::Decl::ObjCMethod:
         //case clang::Decl::ObjCContainer:
         case clang::Decl::ObjCInterface:
         case clang::Decl::ObjCIvar:
         case clang::Decl::ObjCAtDefsField:
         case clang::Decl::ObjCProtocol:
         case clang::Decl::ObjCClass:
         case clang::Decl::ObjCForwardProtocol:
         case clang::Decl::ObjCCategory:
         //case clang::Decl::ObjCImpl:
         case clang::Decl::ObjCCategoryImpl:
         case clang::Decl::ObjCImplementation:
         case clang::Decl::ObjCCompatibleAlias:
         case clang::Decl::ObjCProperty:
         case clang::Decl::ObjCPropertyImpl:
         default:
            break;
      }
   }
}

