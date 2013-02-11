
#ifndef HYLIAN_ASG_H
#define HYLIAN_ASG_H

#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/GlobalDecl.h>
#include <sqlite3.h>

class HylianASG
{
public:
   HylianASG(std::string const& fn);
   ~HylianASG();

   void ExecSQL(std::string &sql);
   void CheckSQLResult(int result);

   void HandleDeclaration(const clang::Decl *decl);
   void HandleStatement(const clang::Stmt *stmt);
   void HandleExpression(const clang::Expr *expr);
   void LookupValueDecl(const clang::ValueDecl *decl);


   // Declarations
   void AddPrettyStackTraceDecl(const clang::PrettyStackTraceDecl *decl, clang::Decl *parent);
   void AddAnyFunctionDecl(const clang::AnyFunctionDecl *decl, clang::Decl *parent);
   void AddAccessSpecDecl(const clang::AccessSpecDecl *decl, clang::Decl *parent);
   void AddCXXRecordDecl(const clang::CXXRecordDecl *decl, clang::Decl *parent);
   void AddCXXMethodDecl(const clang::CXXMethodDecl *decl, clang::Decl *parent);
   void AddCXXConstructorDecl(const clang::CXXConstructorDecl *decl, clang::Decl *parent);
   void AddCXXDestructorDecl(const clang::CXXDestructorDecl *decl, clang::Decl *parent);
   void AddCXXConversionDecl(const clang::CXXConversionDecl *decl, clang::Decl *parent);
   void AddLinkageSpecDecl(const clang::LinkageSpecDecl *decl, clang::Decl *parent);
   void AddUsingDirectiveDecl(const clang::UsingDirectiveDecl *decl, clang::Decl *parent);
   void AddNamespaceAliasDecl(const clang::NamespaceAliasDecl *decl, clang::Decl *parent);
   void AddUsingShadowDecl(const clang::UsingShadowDecl *decl, clang::Decl *parent);
   void AddUsingDecl(const clang::UsingDecl *decl, clang::Decl *parent);
   void AddUnresolvedUsingValueDecl(const clang::UnresolvedUsingValueDecl *decl, clang::Decl *parent);
   void AddUnresolvedUsingTypenameDecl(const clang::UnresolvedUsingTypenameDecl *decl, clang::Decl *parent);
   void AddStaticAssertDecl(const clang::StaticAssertDecl *decl, clang::Decl *parent);
   void AddFriendDecl(const clang::FriendDecl *decl, clang::Decl *parent);
   void AddTranslationUnitDecl(const clang::TranslationUnitDecl *decl, clang::Decl *parent);
   void AddNamedDecl(const clang::NamedDecl *decl, clang::Decl *parent);
   void AddLabelDecl(const clang::LabelDecl *decl, clang::Decl *parent);
   void AddNamespaceDecl(const clang::NamespaceDecl *decl, clang::Decl *parent);
   void AddValueDecl(const clang::ValueDecl *decl, clang::Decl *parent);
   void AddDeclaratorDecl(const clang::DeclaratorDecl *decl, clang::Decl *parent);
   void AddVarDecl(const clang::VarDecl *decl, clang::Decl *parent);
   void AddImplicitParamDecl(const clang::ImplicitParamDecl *decl, clang::Decl *parent);
   void AddParmVarDecl(const clang::ParmVarDecl *decl, clang::Decl *parent);
   void AddFunctionDecl(const clang::FunctionDecl *decl, clang::Decl *parent);
   void AddFieldDecl(const clang::FieldDecl *decl, clang::Decl *parent);
   void AddEnumConstantDecl(const clang::EnumConstantDecl *decl, clang::Decl *parent);
   void AddIndirectFieldDecl(const clang::IndirectFieldDecl *decl, clang::Decl *parent);
   void AddTypeDecl(const clang::TypeDecl *decl, clang::Decl *parent);
   void AddTypedefNameDecl(const clang::TypedefNameDecl *decl, clang::Decl *parent);
   void AddTypedefDecl(const clang::TypedefDecl *decl, clang::Decl *parent);
   void AddTypeAliasDecl(const clang::TypeAliasDecl *decl, clang::Decl *parent);
   void AddEnumDecl(const clang::EnumDecl *decl, clang::Decl *parent);
   void AddRecordDecl(const clang::RecordDecl *decl, clang::Decl *parent);
   void AddFileScopeAsmDecl(const clang::FileScopeAsmDecl *decl, clang::Decl *parent);
   void AddBlockDecl(const clang::BlockDecl *decl, clang::Decl *parent);
   void AddTemplateDecl(const clang::TemplateDecl *decl, clang::Decl *parent);
   void AddRedeclarableTemplateDecl(const clang::RedeclarableTemplateDecl *decl, clang::Decl *parent);
   void AddFunctionTemplateDecl(const clang::FunctionTemplateDecl *decl, clang::Decl *parent);
   void AddTemplateTypeParmDecl(const clang::TemplateTypeParmDecl *decl, clang::Decl *parent);
   void AddClassTemplateDecl(const clang::ClassTemplateDecl *decl, clang::Decl *parent);
   void AddFriendTemplateDecl(const clang::FriendTemplateDecl *decl, clang::Decl *parent);
   void AddTypeAliasTemplateDecl(const clang::TypeAliasTemplateDecl *decl, clang::Decl *parent);
   void AddClassScopeFunctionSpecializationDecl(const clang::ClassScopeFunctionSpecializationDecl *decl, clang::Decl *parent);
   void AddGlobalDecl(const clang::GlobalDecl *decl, clang::Decl *parent);

   // Statements
   void AddCXXCatchStmt(const clang::CXXCatchStmt *stmt, clang::Decl *parent);
   void AddCXXTryStmt(const clang::CXXTryStmt *stmt, clang::Decl *parent);
   void AddCXXForRangeStmt(const clang::CXXForRangeStmt *stmt, clang::Decl *parent);
   void AddDeclStmt(const clang::DeclStmt *stmt, clang::Decl *parent);
   void AddNullStmt(const clang::NullStmt *stmt, clang::Decl *parent);
   void AddCompoundStmt(const clang::CompoundStmt *stmt, clang::Decl *parent);
   void AddCaseStmt(const clang::CaseStmt *stmt, clang::Decl *parent);
   void AddDefaultStmt(const clang::DefaultStmt *stmt, clang::Decl *parent);
   void AddLabelStmt(const clang::LabelStmt *stmt, clang::Decl *parent);
   void AddIfStmt(const clang::IfStmt *stmt, clang::Decl *parent);
   void AddSwitchStmt(const clang::SwitchStmt *stmt, clang::Decl *parent);
   void AddWhileStmt(const clang::WhileStmt *stmt, clang::Decl *parent);
   void AddDoStmt(const clang::DoStmt *stmt, clang::Decl *parent);
   void AddForStmt(const clang::ForStmt *stmt, clang::Decl *parent);
   void AddGotoStmt(const clang::GotoStmt *stmt, clang::Decl *parent);
   void AddIndirectGotoStmt(const clang::IndirectGotoStmt *stmt, clang::Decl *parent);
   void AddContinueStmt(const clang::ContinueStmt *stmt, clang::Decl *parent);
   void AddBreakStmt(const clang::BreakStmt *stmt, clang::Decl *parent);
   void AddReturnStmt(const clang::ReturnStmt *stmt, clang::Decl *parent);
   void AddAsmStmt(const clang::AsmStmt *stmt, clang::Decl *parent);
   void AddSEHExceptStmt(const clang::SEHExceptStmt *stmt, clang::Decl *parent);
   void AddSEHFinallyStmt(const clang::SEHFinallyStmt *stmt, clang::Decl *parent);
   void AddSEHTryStmt(const clang::SEHTryStmt *stmt, clang::Decl *parent);

   // Expressions
   void HandleCXXOperatorCallExpr(const clang::CXXOperatorCallExpr *expr, std::string name);
   void AddCXXOperatorCallExpr(const clang::CXXOperatorCallExpr *expr, clang::Decl *parent);
   void AddCXXMemberCallExpr(const clang::CXXMemberCallExpr *expr, clang::Decl *parent);
   void AddCXXNamedCastExpr(const clang::CXXNamedCastExpr *expr, clang::Decl *parent);
   void AddCXXStaticCastExpr(const clang::CXXStaticCastExpr *expr, clang::Decl *parent);
   void AddCXXDynamicCastExpr(const clang::CXXDynamicCastExpr *expr, clang::Decl *parent);
   void AddCXXReinterpretCastExpr(const clang::CXXReinterpretCastExpr *expr, clang::Decl *parent);
   void AddCXXConstCastExpr(const clang::CXXConstCastExpr *expr, clang::Decl *parent);
   void AddCXXBoolLiteralExpr(const clang::CXXBoolLiteralExpr *expr, clang::Decl *parent);
   void AddCXXNullPtrLiteralExpr(const clang::CXXNullPtrLiteralExpr *expr, clang::Decl *parent);
   void AddCXXTypeidExpr(const clang::CXXTypeidExpr *expr, clang::Decl *parent);
   void AddCXXUuidofExpr(const clang::CXXUuidofExpr *expr, clang::Decl *parent);
   void AddCXXThisExpr(const clang::CXXThisExpr *expr, clang::Decl *parent);
   void AddCXXThrowExpr(const clang::CXXThrowExpr *expr, clang::Decl *parent);
   void AddCXXDefaultArgExpr(const clang::CXXDefaultArgExpr *expr, clang::Decl *parent);
   void AddCXXBindTemporaryExpr(const clang::CXXBindTemporaryExpr *expr, clang::Decl *parent);
   void AddCXXConstructExpr(const clang::CXXConstructExpr *expr, clang::Decl *parent);
   void AddCXXFunctionalCastExpr(const clang::CXXFunctionalCastExpr *expr, clang::Decl *parent);
   void AddCXXTemporaryObjectExpr(const clang::CXXTemporaryObjectExpr *expr, clang::Decl *parent);
   void AddCXXScalarValueInitExpr(const clang::CXXScalarValueInitExpr *expr, clang::Decl *parent);
   void AddCXXNewExpr(const clang::CXXNewExpr *expr, clang::Decl *parent);
   void AddCXXDeleteExpr(const clang::CXXDeleteExpr *expr, clang::Decl *parent);
   void AddCXXPseudoDestructorExpr(const clang::CXXPseudoDestructorExpr *expr, clang::Decl *parent);
   void AddUnaryTypeTraitExpr(const clang::UnaryTypeTraitExpr *expr, clang::Decl *parent);
   void AddBinaryTypeTraitExpr(const clang::BinaryTypeTraitExpr *expr, clang::Decl *parent);
   void AddArrayTypeTraitExpr(const clang::ArrayTypeTraitExpr *expr, clang::Decl *parent);
   void AddExpressionTraitExpr(const clang::ExpressionTraitExpr *expr, clang::Decl *parent);
   void AddOverloadExpr(const clang::OverloadExpr *expr, clang::Decl *parent);
   void AddUnresolvedLookupExpr(const clang::UnresolvedLookupExpr *expr, clang::Decl *parent);
   void AddDependentScopeDeclRefExpr(const clang::DependentScopeDeclRefExpr *expr, clang::Decl *parent);
   void AddCXXUnresolvedConstructExpr(const clang::CXXUnresolvedConstructExpr *expr, clang::Decl *parent);
   void AddCXXDependentScopeMemberExpr(const clang::CXXDependentScopeMemberExpr *expr, clang::Decl *parent);
   void AddUnresolvedMemberExpr(const clang::UnresolvedMemberExpr *expr, clang::Decl *parent);
   void AddCXXNoexceptExpr(const clang::CXXNoexceptExpr *expr, clang::Decl *parent);
   void AddPackExpansionExpr(const clang::PackExpansionExpr *expr, clang::Decl *parent);
   void AddSizeOfPackExpr(const clang::SizeOfPackExpr *expr, clang::Decl *parent);
   void AddSubstNonTypeTemplateParmExpr(const clang::SubstNonTypeTemplateParmExpr *expr, clang::Decl *parent);
   void AddSubstNonTypeTemplateParmPackExpr(const clang::SubstNonTypeTemplateParmPackExpr *expr, clang::Decl *parent);
   void AddMaterializeTemporaryExpr(const clang::MaterializeTemporaryExpr *expr, clang::Decl *parent);
   void AddOpaqueValueExpr(const clang::OpaqueValueExpr *expr, clang::Decl *parent);
   void AddDeclRefExpr(const clang::DeclRefExpr *expr, clang::Decl *parent);
   void AddPredefinedExpr(const clang::PredefinedExpr *expr, clang::Decl *parent);
   void AddParenExpr(const clang::ParenExpr *expr, clang::Decl *parent);
   void AddOffsetOfExpr(const clang::OffsetOfExpr *expr, clang::Decl *parent);
   void AddUnaryExprOrTypeTraitExpr(const clang::UnaryExprOrTypeTraitExpr *expr, clang::Decl *parent);
   void AddArraySubscriptExpr(const clang::ArraySubscriptExpr *expr, clang::Decl *parent);
   void AddCallExpr(const clang::CallExpr *expr, clang::Decl *parent);
   void AddMemberExpr(const clang::MemberExpr *expr, clang::Decl *parent);
   void AddCompoundLiteralExpr(const clang::CompoundLiteralExpr *expr, clang::Decl *parent);
   void AddCastExpr(const clang::CastExpr *expr, clang::Decl *parent);
   void AddImplicitCastExpr(const clang::ImplicitCastExpr *expr, clang::Decl *parent);
   void AddExplicitCastExpr(const clang::ExplicitCastExpr *expr, clang::Decl *parent);
   void AddCStyleCastExpr(const clang::CStyleCastExpr *expr, clang::Decl *parent);
   void AddAddrLabelExpr(const clang::AddrLabelExpr *expr, clang::Decl *parent);
   void AddStmtExpr(const clang::StmtExpr *expr, clang::Decl *parent);
   void AddShuffleVectorExpr(const clang::ShuffleVectorExpr *expr, clang::Decl *parent);
   void AddChooseExpr(const clang::ChooseExpr *expr, clang::Decl *parent);
   void AddGNUNullExpr(const clang::GNUNullExpr *expr, clang::Decl *parent);
   void AddVAArgExpr(const clang::VAArgExpr *expr, clang::Decl *parent);
   void AddInitListExpr(const clang::InitListExpr *expr, clang::Decl *parent);
   void AddDesignatedInitExpr(const clang::DesignatedInitExpr *expr, clang::Decl *parent);
   void AddImplicitValueInitExpr(const clang::ImplicitValueInitExpr *expr, clang::Decl *parent);
   void AddParenListExpr(const clang::ParenListExpr *expr, clang::Decl *parent);
   void AddGenericSelectionExpr(const clang::GenericSelectionExpr *expr, clang::Decl *parent);
   void AddExtVectorElementExpr(const clang::ExtVectorElementExpr *expr, clang::Decl *parent);
   void AddBlockExpr(const clang::BlockExpr *expr, clang::Decl *parent);
   void AddAsTypeExpr(const clang::AsTypeExpr *expr, clang::Decl *parent);
   void AddAtomicExpr(const clang::AtomicExpr *expr, clang::Decl *parent);
   void AddStringLiteral(const clang::StringLiteral *expr, clang::Decl *parent);
   void AddIntegerLiteral(const clang::IntegerLiteral *expr, clang::Decl *parent);
   void AddUnaryOperator(const clang::UnaryOperator *expr, clang::Decl *parent);
   void AddBinaryOperator(const clang::BinaryOperator *expr, clang::Decl *parent);
   void AddCompoundAssignOperator(const clang::CompoundAssignOperator *expr, clang::Decl *parent);

private:
   sqlite3 *db;

};

#endif /* HYLIAN_ASG_H */
