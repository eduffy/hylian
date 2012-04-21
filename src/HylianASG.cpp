
#include <iostream>
#include <string>
#include "HylianASG.h"

static const char *SQLITE_ERRORS_READABLE[] = {
   "Successful result",
/* beginning-of-error-codes */
   "SQL error or missing database",
   "Internal logic error in SQLite",
   "Access permission denied",
   "Callback routine requested an abort",
   "The database file is locked",
   "A table in the database is locked",
   "A malloc() failed",
   "Attempt to write a readonly database",
   "Operation terminated by sqlite3_interrupt()",
   "Some kind of disk I/O error occurred",
   "The database disk image is malformed",
   "Unknown opcode in sqlite3_file_control()",
   "Insertion failed because database is full",
   "Unable to open the database file",
   "Database lock protocol error",
   "Database is empty",
   "The database schema changed",
   "String or BLOB exceeds size limit",
   "Abort due to constraint violation",
   "Data type mismatch",
   "Library used incorrectly",
   "Uses OS features not supported on host",
   "Authorization denied",
   "Auxiliary database format error",
   "2nd parameter to sqlite3_bind out of range",
   "File opened that is not a database file",
   /* 100 */ "sqlite3_step() has another row ready",
   /* 101 */ "sqlite3_step() has finished executing"
};


HylianASG::HylianASG(std::string const& fn)
{
   int result;
   sqlite3_stmt *stmt;
   const char *tail;

   result = sqlite3_open(fn.c_str(), &db);
   assert(result == SQLITE_OK);

   std::string comm = "CREATE TABLE StringLiteral(ID INTEGER PRIMARY KEY, Value TEXT)";
   result = sqlite3_prepare_v2(db, comm.c_str(), comm.size(), &stmt, &tail);
   assert(result == SQLITE_OK);
   result = sqlite3_step(stmt);
   assert(result == SQLITE_OK);
}

HylianASG::~HylianASG()
{

}

void HylianASG::ExecSQL(std::string &sql)
{
   int result;
   sqlite3_stmt *stmt;
   const char *tail;

   result = sqlite3_prepare_v2(db, sql.c_str(), sql.size(), &stmt, &tail);
   if(result != SQLITE_OK) {
      std::cerr << SQLITE_ERRORS_READABLE[result] << std::endl;
      abort();
   }
   result = sqlite3_step(stmt);
   if(result != SQLITE_OK) {
      std::cerr << SQLITE_ERRORS_READABLE[result] << std::endl;
      abort();
   }
}

void HylianASG::CheckSQLResult(int result)
{
   if(result != SQLITE_OK) {
      std::cerr << SQLITE_ERRORS_READABLE[result] << std::endl;
      abort();
   }
}

void HylianASG::HandleStatement(const clang::Stmt *stmt)
{
   if(const clang::CXXCatchStmt *p = clang::dyn_cast<const clang::CXXCatchStmt>(stmt)) {
      AddCXXCatchStmt(p, NULL);
   }
   else if(const clang::CXXTryStmt *p = clang::dyn_cast<const clang::CXXTryStmt>(stmt)) {
      AddCXXTryStmt(p, NULL);
   }
   else if(const clang::CXXForRangeStmt *p = clang::dyn_cast<const clang::CXXForRangeStmt>(stmt)) {
      AddCXXForRangeStmt(p, NULL);
   }
   else if(const clang::DeclStmt *p = clang::dyn_cast<const clang::DeclStmt>(stmt)) {
      AddDeclStmt(p, NULL);
   }
   else if(const clang::NullStmt *p = clang::dyn_cast<const clang::NullStmt>(stmt)) {
      AddNullStmt(p, NULL);
   }
   else if(const clang::CompoundStmt *p = clang::dyn_cast<const clang::CompoundStmt>(stmt)) {
      AddCompoundStmt(p, NULL);
   }
   else if(const clang::CaseStmt *p = clang::dyn_cast<const clang::CaseStmt>(stmt)) {
      AddCaseStmt(p, NULL);
   }
   else if(const clang::DefaultStmt *p = clang::dyn_cast<const clang::DefaultStmt>(stmt)) {
      AddDefaultStmt(p, NULL);
   }
   else if(const clang::LabelStmt *p = clang::dyn_cast<const clang::LabelStmt>(stmt)) {
      AddLabelStmt(p, NULL);
   }
   else if(const clang::IfStmt *p = clang::dyn_cast<const clang::IfStmt>(stmt)) {
      AddIfStmt(p, NULL);
   }
   else if(const clang::SwitchStmt *p = clang::dyn_cast<const clang::SwitchStmt>(stmt)) {
      AddSwitchStmt(p, NULL);
   }
   else if(const clang::WhileStmt *p = clang::dyn_cast<const clang::WhileStmt>(stmt)) {
      AddWhileStmt(p, NULL);
   }
   else if(const clang::DoStmt *p = clang::dyn_cast<const clang::DoStmt>(stmt)) {
      AddDoStmt(p, NULL);
   }
   else if(const clang::ForStmt *p = clang::dyn_cast<const clang::ForStmt>(stmt)) {
      AddForStmt(p, NULL);
   }
   else if(const clang::GotoStmt *p = clang::dyn_cast<const clang::GotoStmt>(stmt)) {
      AddGotoStmt(p, NULL);
   }
   else if(const clang::IndirectGotoStmt *p = clang::dyn_cast<const clang::IndirectGotoStmt>(stmt)) {
      AddIndirectGotoStmt(p, NULL);
   }
   else if(const clang::ContinueStmt *p = clang::dyn_cast<const clang::ContinueStmt>(stmt)) {
      AddContinueStmt(p, NULL);
   }
   else if(const clang::BreakStmt *p = clang::dyn_cast<const clang::BreakStmt>(stmt)) {
      AddBreakStmt(p, NULL);
   }
   else if(const clang::ReturnStmt *p = clang::dyn_cast<const clang::ReturnStmt>(stmt)) {
      AddReturnStmt(p, NULL);
   }
   else if(const clang::AsmStmt *p = clang::dyn_cast<const clang::AsmStmt>(stmt)) {
      AddAsmStmt(p, NULL);
   }
   else if(const clang::SEHExceptStmt *p = clang::dyn_cast<const clang::SEHExceptStmt>(stmt)) {
      AddSEHExceptStmt(p, NULL);
   }
   else if(const clang::SEHFinallyStmt *p = clang::dyn_cast<const clang::SEHFinallyStmt>(stmt)) {
      AddSEHFinallyStmt(p, NULL);
   }
   else if(const clang::SEHTryStmt *p = clang::dyn_cast<const clang::SEHTryStmt>(stmt)) {
      AddSEHTryStmt(p, NULL);
   }
   else if(clang::Expr::classof(stmt)) {
      HandleExpression(clang::dyn_cast<const clang::Expr>(stmt));
   }
   else {
      std::cout << " * * * Unknown statement * * * " << stmt->getStmtClassName() << std::endl;
   }
}

void HylianASG::HandleExpression(const clang::Expr *expr)
{
   std::cout << "entering expression " << expr->getStmtClassName() << std::endl;

   if(const clang::CXXOperatorCallExpr *p = clang::dyn_cast<const clang::CXXOperatorCallExpr>(expr)) {
      AddCXXOperatorCallExpr(p, NULL);
   }
   else if(const clang::CXXMemberCallExpr *p = clang::dyn_cast<const clang::CXXMemberCallExpr>(expr)) {
      AddCXXMemberCallExpr(p, NULL);
   }
//   else if(const clang::CXXNamedCastExpr *p = clang::dyn_cast<const clang::CXXNamedCastExpr>(expr)) {
//      AddCXXNamedCastExpr(p, NULL);
//   }
//   else if(const clang::CXXStaticCastExpr *p = clang::dyn_cast<const clang::CXXStaticCastExpr>(expr)) {
//      AddCXXStaticCastExpr(p, NULL);
//   }
//   else if(const clang::CXXDynamicCastExpr *p = clang::dyn_cast<const clang::CXXDynamicCastExpr>(expr)) {
//      AddCXXDynamicCastExpr(p, NULL);
//   }
//   else if(const clang::CXXReinterpretCastExpr *p = clang::dyn_cast<const clang::CXXReinterpretCastExpr>(expr)) {
//      AddCXXReinterpretCastExpr(p, NULL);
//   }
//   else if(const clang::CXXConstCastExpr *p = clang::dyn_cast<const clang::CXXConstCastExpr>(expr)) {
//      AddCXXConstCastExpr(p, NULL);
//   }
   else if(const clang::CXXBoolLiteralExpr *p = clang::dyn_cast<const clang::CXXBoolLiteralExpr>(expr)) {
      AddCXXBoolLiteralExpr(p, NULL);
   }
   else if(const clang::CXXNullPtrLiteralExpr *p = clang::dyn_cast<const clang::CXXNullPtrLiteralExpr>(expr)) {
      AddCXXNullPtrLiteralExpr(p, NULL);
   }
   else if(const clang::CXXTypeidExpr *p = clang::dyn_cast<const clang::CXXTypeidExpr>(expr)) {
      AddCXXTypeidExpr(p, NULL);
   }
   else if(const clang::CXXUuidofExpr *p = clang::dyn_cast<const clang::CXXUuidofExpr>(expr)) {
      AddCXXUuidofExpr(p, NULL);
   }
   else if(const clang::CXXThisExpr *p = clang::dyn_cast<const clang::CXXThisExpr>(expr)) {
      AddCXXThisExpr(p, NULL);
   }
   else if(const clang::CXXThrowExpr *p = clang::dyn_cast<const clang::CXXThrowExpr>(expr)) {
      AddCXXThrowExpr(p, NULL);
   }
   else if(const clang::CXXDefaultArgExpr *p = clang::dyn_cast<const clang::CXXDefaultArgExpr>(expr)) {
      AddCXXDefaultArgExpr(p, NULL);
   }
   else if(const clang::CXXBindTemporaryExpr *p = clang::dyn_cast<const clang::CXXBindTemporaryExpr>(expr)) {
      AddCXXBindTemporaryExpr(p, NULL);
   }
   else if(const clang::CXXConstructExpr *p = clang::dyn_cast<const clang::CXXConstructExpr>(expr)) {
      AddCXXConstructExpr(p, NULL);
   }
   else if(const clang::CXXFunctionalCastExpr *p = clang::dyn_cast<const clang::CXXFunctionalCastExpr>(expr)) {
      AddCXXFunctionalCastExpr(p, NULL);
   }
   else if(const clang::CXXTemporaryObjectExpr *p = clang::dyn_cast<const clang::CXXTemporaryObjectExpr>(expr)) {
      AddCXXTemporaryObjectExpr(p, NULL);
   }
   else if(const clang::CXXScalarValueInitExpr *p = clang::dyn_cast<const clang::CXXScalarValueInitExpr>(expr)) {
      AddCXXScalarValueInitExpr(p, NULL);
   }
   else if(const clang::CXXNewExpr *p = clang::dyn_cast<const clang::CXXNewExpr>(expr)) {
      AddCXXNewExpr(p, NULL);
   }
   else if(const clang::CXXDeleteExpr *p = clang::dyn_cast<const clang::CXXDeleteExpr>(expr)) {
      AddCXXDeleteExpr(p, NULL);
   }
   else if(const clang::CXXPseudoDestructorExpr *p = clang::dyn_cast<const clang::CXXPseudoDestructorExpr>(expr)) {
      AddCXXPseudoDestructorExpr(p, NULL);
   }
   else if(const clang::UnaryTypeTraitExpr *p = clang::dyn_cast<const clang::UnaryTypeTraitExpr>(expr)) {
      AddUnaryTypeTraitExpr(p, NULL);
   }
   else if(const clang::BinaryTypeTraitExpr *p = clang::dyn_cast<const clang::BinaryTypeTraitExpr>(expr)) {
      AddBinaryTypeTraitExpr(p, NULL);
   }
   else if(const clang::ArrayTypeTraitExpr *p = clang::dyn_cast<const clang::ArrayTypeTraitExpr>(expr)) {
      AddArrayTypeTraitExpr(p, NULL);
   }
   else if(const clang::ExpressionTraitExpr *p = clang::dyn_cast<const clang::ExpressionTraitExpr>(expr)) {
      AddExpressionTraitExpr(p, NULL);
   }
   else if(const clang::OverloadExpr *p = clang::dyn_cast<const clang::OverloadExpr>(expr)) {
      AddOverloadExpr(p, NULL);
   }
   else if(const clang::UnresolvedLookupExpr *p = clang::dyn_cast<const clang::UnresolvedLookupExpr>(expr)) {
      AddUnresolvedLookupExpr(p, NULL);
   }
   else if(const clang::DependentScopeDeclRefExpr *p = clang::dyn_cast<const clang::DependentScopeDeclRefExpr>(expr)) {
      AddDependentScopeDeclRefExpr(p, NULL);
   }
   else if(const clang::CXXUnresolvedConstructExpr *p = clang::dyn_cast<const clang::CXXUnresolvedConstructExpr>(expr)) {
      AddCXXUnresolvedConstructExpr(p, NULL);
   }
   else if(const clang::CXXDependentScopeMemberExpr *p = clang::dyn_cast<const clang::CXXDependentScopeMemberExpr>(expr)) {
      AddCXXDependentScopeMemberExpr(p, NULL);
   }
   else if(const clang::UnresolvedMemberExpr *p = clang::dyn_cast<const clang::UnresolvedMemberExpr>(expr)) {
      AddUnresolvedMemberExpr(p, NULL);
   }
   else if(const clang::CXXNoexceptExpr *p = clang::dyn_cast<const clang::CXXNoexceptExpr>(expr)) {
      AddCXXNoexceptExpr(p, NULL);
   }
   else if(const clang::PackExpansionExpr *p = clang::dyn_cast<const clang::PackExpansionExpr>(expr)) {
      AddPackExpansionExpr(p, NULL);
   }
   else if(const clang::SizeOfPackExpr *p = clang::dyn_cast<const clang::SizeOfPackExpr>(expr)) {
      AddSizeOfPackExpr(p, NULL);
   }
   else if(const clang::SubstNonTypeTemplateParmExpr *p = clang::dyn_cast<const clang::SubstNonTypeTemplateParmExpr>(expr)) {
      AddSubstNonTypeTemplateParmExpr(p, NULL);
   }
   else if(const clang::SubstNonTypeTemplateParmPackExpr *p = clang::dyn_cast<const clang::SubstNonTypeTemplateParmPackExpr>(expr)) {
      AddSubstNonTypeTemplateParmPackExpr(p, NULL);
   }
   else if(const clang::MaterializeTemporaryExpr *p = clang::dyn_cast<const clang::MaterializeTemporaryExpr>(expr)) {
      AddMaterializeTemporaryExpr(p, NULL);
   }
   else if(const clang::OpaqueValueExpr *p = clang::dyn_cast<const clang::OpaqueValueExpr>(expr)) {
      AddOpaqueValueExpr(p, NULL);
   }
   else if(const clang::DeclRefExpr *p = clang::dyn_cast<const clang::DeclRefExpr>(expr)) {
      AddDeclRefExpr(p, NULL);
   }
   else if(const clang::PredefinedExpr *p = clang::dyn_cast<const clang::PredefinedExpr>(expr)) {
      AddPredefinedExpr(p, NULL);
   }
   else if(const clang::ParenExpr *p = clang::dyn_cast<const clang::ParenExpr>(expr)) {
      AddParenExpr(p, NULL);
   }
   else if(const clang::OffsetOfExpr *p = clang::dyn_cast<const clang::OffsetOfExpr>(expr)) {
      AddOffsetOfExpr(p, NULL);
   }
   else if(const clang::UnaryExprOrTypeTraitExpr *p = clang::dyn_cast<const clang::UnaryExprOrTypeTraitExpr>(expr)) {
      AddUnaryExprOrTypeTraitExpr(p, NULL);
   }
   else if(const clang::ArraySubscriptExpr *p = clang::dyn_cast<const clang::ArraySubscriptExpr>(expr)) {
      AddArraySubscriptExpr(p, NULL);
   }
   else if(const clang::CallExpr *p = clang::dyn_cast<const clang::CallExpr>(expr)) {
      AddCallExpr(p, NULL);
   }
   else if(const clang::MemberExpr *p = clang::dyn_cast<const clang::MemberExpr>(expr)) {
      AddMemberExpr(p, NULL);
   }
   else if(const clang::CompoundLiteralExpr *p = clang::dyn_cast<const clang::CompoundLiteralExpr>(expr)) {
      AddCompoundLiteralExpr(p, NULL);
   }
   else if(const clang::CastExpr *p = clang::dyn_cast<const clang::CastExpr>(expr)) {
      AddCastExpr(p, NULL);
   }
//   else if(const clang::ImplicitCastExpr *p = clang::dyn_cast<const clang::ImplicitCastExpr>(expr)) {
//      AddImplicitCastExpr(p, NULL);
//   }
//   else if(const clang::ExplicitCastExpr *p = clang::dyn_cast<const clang::ExplicitCastExpr>(expr)) {
//      AddExplicitCastExpr(p, NULL);
//   }
//   else if(const clang::CStyleCastExpr *p = clang::dyn_cast<const clang::CStyleCastExpr>(expr)) {
//      AddCStyleCastExpr(p, NULL);
//   }
   else if(const clang::AddrLabelExpr *p = clang::dyn_cast<const clang::AddrLabelExpr>(expr)) {
      AddAddrLabelExpr(p, NULL);
   }
   else if(const clang::StmtExpr *p = clang::dyn_cast<const clang::StmtExpr>(expr)) {
      AddStmtExpr(p, NULL);
   }
   else if(const clang::ShuffleVectorExpr *p = clang::dyn_cast<const clang::ShuffleVectorExpr>(expr)) {
      AddShuffleVectorExpr(p, NULL);
   }
   else if(const clang::ChooseExpr *p = clang::dyn_cast<const clang::ChooseExpr>(expr)) {
      AddChooseExpr(p, NULL);
   }
   else if(const clang::GNUNullExpr *p = clang::dyn_cast<const clang::GNUNullExpr>(expr)) {
      AddGNUNullExpr(p, NULL);
   }
   else if(const clang::VAArgExpr *p = clang::dyn_cast<const clang::VAArgExpr>(expr)) {
      AddVAArgExpr(p, NULL);
   }
   else if(const clang::InitListExpr *p = clang::dyn_cast<const clang::InitListExpr>(expr)) {
      AddInitListExpr(p, NULL);
   }
   else if(const clang::DesignatedInitExpr *p = clang::dyn_cast<const clang::DesignatedInitExpr>(expr)) {
      AddDesignatedInitExpr(p, NULL);
   }
   else if(const clang::ImplicitValueInitExpr *p = clang::dyn_cast<const clang::ImplicitValueInitExpr>(expr)) {
      AddImplicitValueInitExpr(p, NULL);
   }
   else if(const clang::ParenListExpr *p = clang::dyn_cast<const clang::ParenListExpr>(expr)) {
      AddParenListExpr(p, NULL);
   }
   else if(const clang::GenericSelectionExpr *p = clang::dyn_cast<const clang::GenericSelectionExpr>(expr)) {
      AddGenericSelectionExpr(p, NULL);
   }
   else if(const clang::ExtVectorElementExpr *p = clang::dyn_cast<const clang::ExtVectorElementExpr>(expr)) {
      AddExtVectorElementExpr(p, NULL);
   }
   else if(const clang::BlockExpr *p = clang::dyn_cast<const clang::BlockExpr>(expr)) {
      AddBlockExpr(p, NULL);
   }
   else if(const clang::BlockDeclRefExpr *p = clang::dyn_cast<const clang::BlockDeclRefExpr>(expr)) {
      AddBlockDeclRefExpr(p, NULL);
   }
   else if(const clang::AsTypeExpr *p = clang::dyn_cast<const clang::AsTypeExpr>(expr)) {
      AddAsTypeExpr(p, NULL);
   }
   else if(const clang::AtomicExpr *p = clang::dyn_cast<const clang::AtomicExpr>(expr)) {
      AddAtomicExpr(p, NULL);
   }
   else if(const clang::StringLiteral *p = clang::dyn_cast<const clang::StringLiteral>(expr)) {
      AddStringLiteral(p, NULL);
   }
}

void HylianASG::LookupValueDecl(const clang::ValueDecl *decl)
{
   std::cout << " + + " << decl->getQualifiedNameAsString() << std::endl;
}
