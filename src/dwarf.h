#ifndef DWARF_H_
#define DWARF_H_

#ifdef __APPLE__
#define DWARF_OSX
#endif

#ifdef __linux__
#define DWARF_LINUX
#endif

typedef bool BOOL;
typedef float F32;
typedef int I32;
typedef unsigned int U32;
typedef long long I64;
typedef unsigned long long U64;

#endif