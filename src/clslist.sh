#!/bin/bash -x

cls=$1
if [[ -z $cls ]]; then
   cls=Decl
fi
INCLDIR=$(llvm-config --includedir)/clang/AST
egrep --no-filename --only-matching 'class [A-Za-z_]*'$cls' ' ${INCLDIR}/*.h | awk '{print $2}' | /bin/grep -v ObjC


# exmaple run:
# ./clslist.sh Stmt | awk '{print "   else if(const clang::"$1" *p = clang::dyn_cast<const clang::"$1">(stmt)) {\n      Add"$1"(p, NULL);\n   }"}'

