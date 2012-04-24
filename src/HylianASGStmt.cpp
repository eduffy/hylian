
#include <iostream>
#include "HylianASG.h"

void HylianASG::AddCXXCatchStmt(const clang::CXXCatchStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddCXXTryStmt(const clang::CXXTryStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddCXXForRangeStmt(const clang::CXXForRangeStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddDeclStmt(const clang::DeclStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddNullStmt(const clang::NullStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddCompoundStmt(const clang::CompoundStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddCaseStmt(const clang::CaseStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddDefaultStmt(const clang::DefaultStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddLabelStmt(const clang::LabelStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddIfStmt(const clang::IfStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddSwitchStmt(const clang::SwitchStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddWhileStmt(const clang::WhileStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddDoStmt(const clang::DoStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddForStmt(const clang::ForStmt *stmt, clang::Decl *parent)
{
   HandleStatement(stmt->getInit());
   HandleExpression(stmt->getCond());
   HandleExpression(stmt->getInc());
   HandleStatement(stmt->getBody());
}

void HylianASG::AddGotoStmt(const clang::GotoStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddIndirectGotoStmt(const clang::IndirectGotoStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddContinueStmt(const clang::ContinueStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddBreakStmt(const clang::BreakStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddReturnStmt(const clang::ReturnStmt *stmt, clang::Decl *parent)
{
   std::cout << "new Return Statement" << std::endl;
   HandleExpression(stmt->getRetValue());
}

void HylianASG::AddAsmStmt(const clang::AsmStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddSEHExceptStmt(const clang::SEHExceptStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddSEHFinallyStmt(const clang::SEHFinallyStmt *stmt, clang::Decl *parent)
{
}

void HylianASG::AddSEHTryStmt(const clang::SEHTryStmt *stmt, clang::Decl *parent)
{
}

