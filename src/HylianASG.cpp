
#include <iostream>
#include "HylianASG.h"

HylianASG::HylianASG()
{
   int result = sqlite3_open("temp.db", &db);
   assert(result == SQLITE_OK);
}

HylianASG::~HylianASG()
{

}


void HylianASG::HandleStatement(const clang::Stmt *stmt)
{
   if(const clang::CXXCatchStmt *p = clang::dyn_cast<clang::CXXCatchStmt>(stmt)) {
   }

   else if(const clang::CXXTryStmt *p = clang::dyn_cast<clang::CXXTryStmt>(stmt)) {
   }

   else if(const clang::CXXForRangeStmt *p = clang::dyn_cast<clang::CXXForRangeStmt>(stmt)) {
   }

   else if(const clang::DeclStmt *p = clang::dyn_cast<clang::DeclStmt>(stmt)) {
   }

   else if(const clang::NullStmt *p = clang::dyn_cast<clang::NullStmt>(stmt)) {
   }

   else if(const clang::CompoundStmt *p = clang::dyn_cast<clang::CompoundStmt>(stmt)) {
   }

   else if(const clang::CaseStmt *p = clang::dyn_cast<clang::CaseStmt>(stmt)) {
   }

   else if(const clang::DefaultStmt *p = clang::dyn_cast<clang::DefaultStmt>(stmt)) {
   }

   else if(const clang::LabelStmt *p = clang::dyn_cast<clang::LabelStmt>(stmt)) {
   }

   else if(const clang::IfStmt *p = clang::dyn_cast<clang::IfStmt>(stmt)) {
   }

   else if(const clang::SwitchStmt *p = clang::dyn_cast<clang::SwitchStmt>(stmt)) {
   }

   else if(const clang::WhileStmt *p = clang::dyn_cast<clang::WhileStmt>(stmt)) {
   }

   else if(const clang::DoStmt *p = clang::dyn_cast<clang::DoStmt>(stmt)) {
   }

   else if(const clang::ForStmt *p = clang::dyn_cast<clang::ForStmt>(stmt)) {
   }

   else if(const clang::GotoStmt *p = clang::dyn_cast<clang::GotoStmt>(stmt)) {
   }

   else if(const clang::IndirectGotoStmt *p = clang::dyn_cast<clang::IndirectGotoStmt>(stmt)) {
   }

   else if(const clang::ContinueStmt *p = clang::dyn_cast<clang::ContinueStmt>(stmt)) {
   }

   else if(const clang::BreakStmt *p = clang::dyn_cast<clang::BreakStmt>(stmt)) {
   }

   else if(const clang::ReturnStmt *p = clang::dyn_cast<const clang::ReturnStmt>(stmt)) {
      std::cout << "new Return Statement" << std::endl;
      HandleExpression(p->getRetValue());
   }
   else {
      std::cout << "\t\tUnknown statement " << stmt->getStmtClassName() << std::endl;
   }
}

void HylianASG::HandleExpression(const clang::Expr *expr)
{
   std::cout << "entering expression " << expr->getStmtClassName() << std::endl;

   if(const clang::CXXOperatorCallExpr *p = clang::dyn_cast<const clang::CXXOperatorCallExpr>(expr)) {
   }

   else if(const clang::CXXMemberCallExpr *p = clang::dyn_cast<const clang::CXXMemberCallExpr>(expr)) {
   }

   else if(const clang::CUDAKernelCallExpr *p = clang::dyn_cast<const clang::CUDAKernelCallExpr>(expr)) {
   }

   else if(const clang::CXXNamedCastExpr *p = clang::dyn_cast<const clang::CXXNamedCastExpr>(expr)) {
   }

   else if(const clang::CXXStaticCastExpr *p = clang::dyn_cast<const clang::CXXStaticCastExpr>(expr)) {
   }

   else if(const clang::CXXDynamicCastExpr *p = clang::dyn_cast<const clang::CXXDynamicCastExpr>(expr)) {
   }

   else if(const clang::CXXReinterpretCastExpr *p = clang::dyn_cast<const clang::CXXReinterpretCastExpr>(expr)) {
   }

   else if(const clang::CXXConstCastExpr *p = clang::dyn_cast<const clang::CXXConstCastExpr>(expr)) {
   }

   else if(const clang::CXXBoolLiteralExpr *p = clang::dyn_cast<const clang::CXXBoolLiteralExpr>(expr)) {
   }

   else if(const clang::CXXNullPtrLiteralExpr *p = clang::dyn_cast<const clang::CXXNullPtrLiteralExpr>(expr)) {
   }

   else if(const clang::CXXTypeidExpr *p = clang::dyn_cast<const clang::CXXTypeidExpr>(expr)) {
   }

   else if(const clang::CXXUuidofExpr *p = clang::dyn_cast<const clang::CXXUuidofExpr>(expr)) {
   }

   else if(const clang::CXXThisExpr *p = clang::dyn_cast<const clang::CXXThisExpr>(expr)) {
   }

   else if(const clang::CXXThrowExpr *p = clang::dyn_cast<const clang::CXXThrowExpr>(expr)) {
   }

   else if(const clang::CXXDefaultArgExpr *p = clang::dyn_cast<const clang::CXXDefaultArgExpr>(expr)) {
   }

   else if(const clang::CXXBindTemporaryExpr *p = clang::dyn_cast<const clang::CXXBindTemporaryExpr>(expr)) {
   }

   else if(const clang::CXXConstructExpr *p = clang::dyn_cast<const clang::CXXConstructExpr>(expr)) {
   }

   else if(const clang::CXXFunctionalCastExpr *p = clang::dyn_cast<const clang::CXXFunctionalCastExpr>(expr)) {
   }

   else if(const clang::CXXTemporaryObjectExpr *p = clang::dyn_cast<const clang::CXXTemporaryObjectExpr>(expr)) {
   }

   else if(const clang::CXXScalarValueInitExpr *p = clang::dyn_cast<const clang::CXXScalarValueInitExpr>(expr)) {
   }

   else if(const clang::CXXNewExpr *p = clang::dyn_cast<const clang::CXXNewExpr>(expr)) {
   }

   else if(const clang::CXXDeleteExpr *p = clang::dyn_cast<const clang::CXXDeleteExpr>(expr)) {
   }

   else if(const clang::CXXPseudoDestructorExpr *p = clang::dyn_cast<const clang::CXXPseudoDestructorExpr>(expr)) {
   }

   else if(const clang::UnaryTypeTraitExpr *p = clang::dyn_cast<const clang::UnaryTypeTraitExpr>(expr)) {
   }

   else if(const clang::BinaryTypeTraitExpr *p = clang::dyn_cast<const clang::BinaryTypeTraitExpr>(expr)) {
   }

   else if(const clang::ArrayTypeTraitExpr *p = clang::dyn_cast<const clang::ArrayTypeTraitExpr>(expr)) {
   }

   else if(const clang::ExpressionTraitExpr *p = clang::dyn_cast<const clang::ExpressionTraitExpr>(expr)) {
   }

   else if(const clang::OverloadExpr *p = clang::dyn_cast<const clang::OverloadExpr>(expr)) {
   }

   else if(const clang::UnresolvedLookupExpr *p = clang::dyn_cast<const clang::UnresolvedLookupExpr>(expr)) {
   }

   else if(const clang::DependentScopeDeclRefExpr *p = clang::dyn_cast<const clang::DependentScopeDeclRefExpr>(expr)) {
   }

   else if(const clang::CXXUnresolvedConstructExpr *p = clang::dyn_cast<const clang::CXXUnresolvedConstructExpr>(expr)) {
   }

   else if(const clang::CXXDependentScopeMemberExpr *p = clang::dyn_cast<const clang::CXXDependentScopeMemberExpr>(expr)) {
   }

   else if(const clang::UnresolvedMemberExpr *p = clang::dyn_cast<const clang::UnresolvedMemberExpr>(expr)) {
   }

   else if(const clang::CXXNoexceptExpr *p = clang::dyn_cast<const clang::CXXNoexceptExpr>(expr)) {
   }

   else if(const clang::PackExpansionExpr *p = clang::dyn_cast<const clang::PackExpansionExpr>(expr)) {
   }

   else if(const clang::SizeOfPackExpr *p = clang::dyn_cast<const clang::SizeOfPackExpr>(expr)) {
   }

   else if(const clang::SubstNonTypeTemplateParmExpr *p = clang::dyn_cast<const clang::SubstNonTypeTemplateParmExpr>(expr)) {
   }

   else if(const clang::SubstNonTypeTemplateParmPackExpr *p = clang::dyn_cast<const clang::SubstNonTypeTemplateParmPackExpr>(expr)) {
   }

   else if(const clang::MaterializeTemporaryExpr *p = clang::dyn_cast<const clang::MaterializeTemporaryExpr>(expr)) {
   }

   else if(const clang::OpaqueValueExpr *p = clang::dyn_cast<const clang::OpaqueValueExpr>(expr)) {
   }

   else if(const clang::DeclRefExpr *p = clang::dyn_cast<const clang::DeclRefExpr>(expr)) {
   }

   else if(const clang::PredefinedExpr *p = clang::dyn_cast<const clang::PredefinedExpr>(expr)) {
   }

   else if(const clang::ParenExpr *p = clang::dyn_cast<const clang::ParenExpr>(expr)) {
   }

   else if(const clang::OffsetOfExpr *p = clang::dyn_cast<const clang::OffsetOfExpr>(expr)) {
   }

   else if(const clang::UnaryExprOrTypeTraitExpr *p = clang::dyn_cast<const clang::UnaryExprOrTypeTraitExpr>(expr)) {
   }

   else if(const clang::ArraySubscriptExpr *p = clang::dyn_cast<const clang::ArraySubscriptExpr>(expr)) {
   }

   else if(const clang::CallExpr *p = clang::dyn_cast<const clang::CallExpr>(expr)) {
   }

   else if(const clang::MemberExpr *p = clang::dyn_cast<const clang::MemberExpr>(expr)) {
   }

   else if(const clang::CompoundLiteralExpr *p = clang::dyn_cast<const clang::CompoundLiteralExpr>(expr)) {
   }

   else if(const clang::CastExpr *p = clang::dyn_cast<const clang::CastExpr>(expr)) {
   }

   else if(const clang::ImplicitCastExpr *p = clang::dyn_cast<const clang::ImplicitCastExpr>(expr)) {
   }

   else if(const clang::ExplicitCastExpr *p = clang::dyn_cast<const clang::ExplicitCastExpr>(expr)) {
   }

   else if(const clang::CStyleCastExpr *p = clang::dyn_cast<const clang::CStyleCastExpr>(expr)) {
   }

   else if(const clang::AddrLabelExpr *p = clang::dyn_cast<const clang::AddrLabelExpr>(expr)) {
   }

   else if(const clang::StmtExpr *p = clang::dyn_cast<const clang::StmtExpr>(expr)) {
   }

   else if(const clang::ShuffleVectorExpr *p = clang::dyn_cast<const clang::ShuffleVectorExpr>(expr)) {
   }

   else if(const clang::ChooseExpr *p = clang::dyn_cast<const clang::ChooseExpr>(expr)) {
   }

   else if(const clang::GNUNullExpr *p = clang::dyn_cast<const clang::GNUNullExpr>(expr)) {
   }

   else if(const clang::VAArgExpr *p = clang::dyn_cast<const clang::VAArgExpr>(expr)) {
   }

   else if(const clang::InitListExpr *p = clang::dyn_cast<const clang::InitListExpr>(expr)) {
   }

   else if(const clang::DesignatedInitExpr *p = clang::dyn_cast<const clang::DesignatedInitExpr>(expr)) {
   }

   else if(const clang::ImplicitValueInitExpr *p = clang::dyn_cast<const clang::ImplicitValueInitExpr>(expr)) {
   }

   else if(const clang::ParenListExpr *p = clang::dyn_cast<const clang::ParenListExpr>(expr)) {
   }

   else if(const clang::GenericSelectionExpr *p = clang::dyn_cast<const clang::GenericSelectionExpr>(expr)) {
   }

   else if(const clang::ExtVectorElementExpr *p = clang::dyn_cast<const clang::ExtVectorElementExpr>(expr)) {
   }

   else if(const clang::BlockExpr *p = clang::dyn_cast<const clang::BlockExpr>(expr)) {
   }

   else if(const clang::BlockDeclRefExpr *p = clang::dyn_cast<const clang::BlockDeclRefExpr>(expr)) {
   }

   else if(const clang::AsTypeExpr *p = clang::dyn_cast<const clang::AsTypeExpr>(expr)) {
   }

   else if(const clang::AtomicExpr *p = clang::dyn_cast<const clang::AtomicExpr>(expr)) {
   }

   else if(const clang::ExprWithCleanups *p = clang::dyn_cast<const clang::ExprWithCleanups>(expr)) {
   }

   else if(const clang::IntegerLiteral *p = clang::dyn_cast<const clang::IntegerLiteral>(expr)) {
      std::cout << "int_lit{" << p->getValue().toString(10,false) << "}" << std::endl;
   }

   else if(const clang::CharacterLiteral *p = clang::dyn_cast<const clang::CharacterLiteral>(expr)) {
   }

   else if(const clang::FloatingLiteral *p = clang::dyn_cast<const clang::FloatingLiteral>(expr)) {
   }

   else if(const clang::ImaginaryLiteral *p = clang::dyn_cast<const clang::ImaginaryLiteral>(expr)) {
   }

   else if(const clang::StringLiteral *p = clang::dyn_cast<const clang::StringLiteral>(expr)) {
   }

   else if(const clang::UnaryOperator *p = clang::dyn_cast<const clang::UnaryOperator>(expr)) {
   }

   else if(const clang::BinaryOperator *p = clang::dyn_cast<const clang::BinaryOperator>(expr)) {
   }

   else if(const clang::AbstractConditionalOperator *p = clang::dyn_cast<const clang::AbstractConditionalOperator>(expr)) {
   }

   else if(const clang::ObjCStringLiteral *p = clang::dyn_cast<const clang::ObjCStringLiteral>(expr)) {
   }

}
