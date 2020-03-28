#ifdef MMUTILS_EXPORTS
#define MMUTILS_API __declspec(dllexport)
#else
#define MMUTILS_API __declspec(dllimport)
#endif

// This class is exported from the mmInTouchSFL.dll
MMUTILS_API int ReadWindowLocation(LPSTR AppDir, LPSTR WindowName, LPSTR XTag, LPSTR YTag);
MMUTILS_API int PasteBuiltInFuncs(LPSTR funcName, LPSTR result);

