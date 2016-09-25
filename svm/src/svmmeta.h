#ifndef SVMMETA_H
#define SVMMETA_H

// VM Version
#define _SVM_VERSION_ "v0.1"

// Compiler type and version used to compile MVM
#ifdef __clang__
#define _SVM_COMPILER_ "Clang/LLVM"
#define _SVM_COMPILER_VERSION_ __clang_version__
#else
#define _SVM_COMPILER_ "g++"
#define _SVM_COMPILER_VERSION_ __VERSION__
#endif

// Arch of MVM
#ifdef __amd64__
#define _SVM_ARCH_ "x64"
#else
#define _SVM_ARCH_ "x86"
#endif


#endif // VMINFO_H
