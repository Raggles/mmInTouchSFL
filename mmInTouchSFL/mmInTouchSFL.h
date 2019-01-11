// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HCINTOUCHUTILS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HCINTOUCHUTILS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HCINTOUCHUTILS_EXPORTS
#define HCINTOUCHUTILS_API __declspec(dllexport)
#else
#define HCINTOUCHUTILS_API __declspec(dllimport)
#endif

// This class is exported from the HCInTouchUtils.dll
HCINTOUCHUTILS_API int ReadWindowLocation(LPSTR AppDir, LPSTR WindowName, LPSTR XTag, LPSTR YTag);
HCINTOUCHUTILS_API int PasteBuiltInFuncs(LPSTR funcName, LPSTR result);

