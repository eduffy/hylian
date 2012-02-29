
#include <iostream>
#include <map>
#include <clang-c/Index.h>

CXChildVisitResult dumpast(CXCursor cursor, CXCursor parent, CXClientData data)
{
   std::map<unsigned, unsigned> *indent = static_cast<std::map<unsigned, unsigned> *>(data);
   std::string spelling(clang_getCString(clang_getCursorSpelling(cursor)));
   unsigned hash = clang_hashCursor(cursor);
   if(!clang_equalCursors(parent, clang_getNullCursor())) {
      (*indent)[hash] = (*indent)[clang_hashCursor(parent)] + 1;
   }
   std::cout << (*indent)[hash] << ". ";
   for(unsigned i =0; i < (*indent)[hash]; i++) {
      std::cout << " ";
   }
   switch(cursor.kind)
   {
      case CXCursor_Namespace: {
         std::cout << "namespace [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_ClassDecl: 
      case CXCursor_StructDecl: {
         std::cout << "class [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_ClassTemplate: {
         std::cout << "class template [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_UnionDecl: {
         std::cout << "union [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_FieldDecl: {
         std::cout << "field [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_FunctionDecl: {
         std::cout << "func [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_CXXMethod: {
         std::cout << "method [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_CallExpr: {
         std::cout << "call [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_VarDecl: {
         std::cout << "variable [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_ParmDecl: {
         std::cout << "parameter [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_TypeRef: {
         std::cout << "type reference [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_TemplateRef: {
         std::cout << "template reference [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_UnexposedExpr: {
         std::cout << "unex expr [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_DeclRefExpr: {
         std::cout << "decl ref expr [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_MemberRefExpr: {
         std::cout << "member ref expr [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_BlockExpr: {
         std::cout << "block expr [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_Constructor: {
         std::cout << "contrutor [" << spelling << "]" << std::endl;
         break;
      }
      case CXCursor_MemberRef: {
         std::cout << "member ref [" << spelling << "]" << std::endl;
         break;
      }
      default:
         std::cout << "{" << cursor.kind << "}  [" << spelling << "]" << std::endl;
//         std::cout << "kind = " << cursor.kind << std::endl;
   }
   return CXChildVisit_Recurse;
}

int main(int argc, char *argv[])
{

   std::string inputFilename = argv[1];

   std::cout << "Backend: " << clang_getCString(clang_getClangVersion()) << std::endl;
   std::cout << "parsing " << inputFilename << std::endl;
   CXIndex index = clang_createIndex(1, 1);
   CXTranslationUnit tu = clang_parseTranslationUnit(index,
	inputFilename.c_str(), NULL, 0, NULL, 0, 0);

   std::map<unsigned, unsigned> indent;
   CXCursor c = clang_getTranslationUnitCursor(tu);
   indent[clang_hashCursor(c)] = 0;
   clang_visitChildren(c, dumpast, &indent);


   return 0;
}
