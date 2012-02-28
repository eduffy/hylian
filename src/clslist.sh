#!/bin/bash -x

cls=$1
if [[ -z $cls ]]; then
   cls=Decl
fi
INCLDIR=$(llvm-config --includedir)/clang/AST
egrep --no-filename --only-matching 'class [A-Za-z_]*'$cls' ' ${INCLDIR}/*.h | awk '{print $2}' #| /bin/grep -v ObjC
