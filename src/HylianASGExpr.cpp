
#include <iostream>
#include "HylianASG.h"

void HylianASG::HandleCXXOperatorCallExpr(const clang::CXXOperatorCallExpr *expr, std::string name)
{
   std::cout << "- - " << name << " - -" << std::endl;
   clang::CallExpr::const_arg_iterator p;
   int i = 1;
   for(p = expr->arg_begin(); p != expr->arg_end(); ++p, ++i) {
      std::cout << " * * " << i << std::endl;
      HandleExpression(*p);
   }
}

void HylianASG::AddCXXOperatorCallExpr(const clang::CXXOperatorCallExpr *expr, clang::Decl *parent)
{

   switch(expr->getOperator()) {
#undef OVERLOADED_OPERATOR
#undef OVERLOADED_OPERATOR_MULTI

#define OVERLOADED_OPERATOR(Name,Spelling,Token,Unary,Binary,MemberOnly) case clang::OO_ ## Name: { \
   HandleCXXOperatorCallExpr(expr, #Name); \
   break; }
#define OVERLOADED_OPERATOR_MULTI(Name,Spelling,Unary,Binary,MemberOnly) case clang::OO_ ## Name: { \
   std::cout << #Spelling << "\t" << Unary << "\t" << Binary << std::endl; \
   break; }

#include "clang/Basic/OperatorKinds.def"
#undef OVERLOADED_OPERATOR
#undef OVERLOADED_OPERATOR_MULTI

      case clang::OO_None:
      case clang::NUM_OVERLOADED_OPERATORS:
        break;
   }

}

void HylianASG::AddCXXMemberCallExpr(const clang::CXXMemberCallExpr *expr, clang::Decl *parent)
{

}

// void HylianASG::AddCXXNamedCastExpr(const clang::CXXNamedCastExpr *expr, clang::Decl *parent)
// {
// }

// void HylianASG::AddCXXStaticCastExpr(const clang::CXXStaticCastExpr *expr, clang::Decl *parent)
// {
// }

// void HylianASG::AddCXXDynamicCastExpr(const clang::CXXDynamicCastExpr *expr, clang::Decl *parent)
// {
// }

// void HylianASG::AddCXXReinterpretCastExpr(const clang::CXXReinterpretCastExpr *expr, clang::Decl *parent)
// {
// }

// void HylianASG::AddCXXConstCastExpr(const clang::CXXConstCastExpr *expr, clang::Decl *parent)
// {
// }

void HylianASG::AddCXXBoolLiteralExpr(const clang::CXXBoolLiteralExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXNullPtrLiteralExpr(const clang::CXXNullPtrLiteralExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXTypeidExpr(const clang::CXXTypeidExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXUuidofExpr(const clang::CXXUuidofExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXThisExpr(const clang::CXXThisExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXThrowExpr(const clang::CXXThrowExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXDefaultArgExpr(const clang::CXXDefaultArgExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXBindTemporaryExpr(const clang::CXXBindTemporaryExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXConstructExpr(const clang::CXXConstructExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXFunctionalCastExpr(const clang::CXXFunctionalCastExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXTemporaryObjectExpr(const clang::CXXTemporaryObjectExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXScalarValueInitExpr(const clang::CXXScalarValueInitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXNewExpr(const clang::CXXNewExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXDeleteExpr(const clang::CXXDeleteExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXPseudoDestructorExpr(const clang::CXXPseudoDestructorExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddUnaryTypeTraitExpr(const clang::UnaryTypeTraitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddBinaryTypeTraitExpr(const clang::BinaryTypeTraitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddArrayTypeTraitExpr(const clang::ArrayTypeTraitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddExpressionTraitExpr(const clang::ExpressionTraitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddOverloadExpr(const clang::OverloadExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddUnresolvedLookupExpr(const clang::UnresolvedLookupExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddDependentScopeDeclRefExpr(const clang::DependentScopeDeclRefExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXUnresolvedConstructExpr(const clang::CXXUnresolvedConstructExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXDependentScopeMemberExpr(const clang::CXXDependentScopeMemberExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddUnresolvedMemberExpr(const clang::UnresolvedMemberExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCXXNoexceptExpr(const clang::CXXNoexceptExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddPackExpansionExpr(const clang::PackExpansionExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddSizeOfPackExpr(const clang::SizeOfPackExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddSubstNonTypeTemplateParmExpr(const clang::SubstNonTypeTemplateParmExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddSubstNonTypeTemplateParmPackExpr(const clang::SubstNonTypeTemplateParmPackExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddMaterializeTemporaryExpr(const clang::MaterializeTemporaryExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddOpaqueValueExpr(const clang::OpaqueValueExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddDeclRefExpr(const clang::DeclRefExpr *expr, clang::Decl *parent)
{
   LookupValueDecl(expr->getDecl());
}

void HylianASG::AddPredefinedExpr(const clang::PredefinedExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddParenExpr(const clang::ParenExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddOffsetOfExpr(const clang::OffsetOfExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddUnaryExprOrTypeTraitExpr(const clang::UnaryExprOrTypeTraitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddArraySubscriptExpr(const clang::ArraySubscriptExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCallExpr(const clang::CallExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddMemberExpr(const clang::MemberExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCompoundLiteralExpr(const clang::CompoundLiteralExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddCastExpr(const clang::CastExpr *expr, clang::Decl *parent)
{
   std::cout << "any cast:";
   HandleExpression(expr->getSubExpr());
}

// void HylianASG::AddImplicitCastExpr(const clang::ImplicitCastExpr *expr, clang::Decl *parent)
// {
// }

// void HylianASG::AddExplicitCastExpr(const clang::ExplicitCastExpr *expr, clang::Decl *parent)
// {
// }

// void HylianASG::AddCStyleCastExpr(const clang::CStyleCastExpr *expr, clang::Decl *parent)
// {
// }

void HylianASG::AddAddrLabelExpr(const clang::AddrLabelExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddStmtExpr(const clang::StmtExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddShuffleVectorExpr(const clang::ShuffleVectorExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddChooseExpr(const clang::ChooseExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddGNUNullExpr(const clang::GNUNullExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddVAArgExpr(const clang::VAArgExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddInitListExpr(const clang::InitListExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddDesignatedInitExpr(const clang::DesignatedInitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddImplicitValueInitExpr(const clang::ImplicitValueInitExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddParenListExpr(const clang::ParenListExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddGenericSelectionExpr(const clang::GenericSelectionExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddExtVectorElementExpr(const clang::ExtVectorElementExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddBlockExpr(const clang::BlockExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddBlockDeclRefExpr(const clang::BlockDeclRefExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddAsTypeExpr(const clang::AsTypeExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddAtomicExpr(const clang::AtomicExpr *expr, clang::Decl *parent)
{
}

void HylianASG::AddStringLiteral(const clang::StringLiteral *expr, clang::Decl *parent)
{
   int           result;
   sqlite3_stmt *stmt;
   const char   *tail;
   std::string   sql = "SELECT ID FROM StringLiteral WHERE Value=\"" + expr->getString().str() + "\"";
   int           index = -1;

   result = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &stmt, &tail);
   CheckSQLResult(result);
   result = sqlite3_step(stmt);
   if(result == SQLITE_DONE) {
      /* No result.  Add it to the database */
      sql = "INSERT INTO StringLiteral (Value) VALUES (\"" + expr->getString().str() + "\")";
      result = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &stmt, &tail);
      CheckSQLResult(result);
      result = sqlite3_step(stmt);
      index = sqlite3_last_insert_rowid(db);
   }
   else if(result == SQLITE_ROW) {
      index = sqlite3_column_int(stmt, 0);
   }
   else {
      CheckSQLResult(result);
   }
   std::cout << "INDEX: " << index;
}
