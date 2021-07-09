/*

    WGL loader generated by glad 0.1.34 on Fri Jul  9 16:38:40 2021.

    Language/Generator: C/C++
    Specification: wgl
    APIs: wgl=1.0
    Profile: -
    Extensions:
        WGL_ARB_extensions_string,
        WGL_EXT_extensions_string,
        WGL_NV_DX_interop
    Loader: True
    Local files: False
    Omit khrplatform: False
    Reproducible: False

    Commandline:
        --api="wgl=1.0" --generator="c" --spec="wgl" --extensions="WGL_ARB_extensions_string,WGL_EXT_extensions_string,WGL_NV_DX_interop"
    Online:
        https://glad.dav1d.de/#language=c&specification=wgl&loader=on&api=wgl%3D1.0&extensions=WGL_ARB_extensions_string&extensions=WGL_EXT_extensions_string&extensions=WGL_NV_DX_interop
*/


#ifndef WINAPI
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef NOMINMAX
#define NOMINMAX 1
#endif
#include <windows.h>
#endif

#include "glad.h"

#ifndef __glad_wglext_h_

#ifdef __wglext_h_
#error WGL header already included, remove this include, glad already provides it
#endif

#define __glad_wglext_h_
#define __wglext_h_

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (* GLADloadproc)(const char *name);

#ifndef GLAPI
# if defined(GLAD_GLAPI_EXPORT)
#  if defined(_WIN32) || defined(__CYGWIN__)
#   if defined(GLAD_GLAPI_EXPORT_BUILD)
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllexport)) extern
#    else
#     define GLAPI __declspec(dllexport) extern
#    endif
#   else
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllimport)) extern
#    else
#     define GLAPI __declspec(dllimport) extern
#    endif
#   endif
#  elif defined(__GNUC__) && defined(GLAD_GLAPI_EXPORT_BUILD)
#   define GLAPI __attribute__ ((visibility ("default"))) extern
#  else
#   define GLAPI extern
#  endif
# else
#  define GLAPI extern
# endif
#endif

GLAPI int gladLoadWGL(HDC hdc);
GLAPI void gladUnloadWGL(void);

GLAPI int gladLoadWGLLoader(GLADloadproc, HDC hdc);

struct _GPU_DEVICE {
    DWORD  cb;
    CHAR   DeviceName[32];
    CHAR   DeviceString[128];
    DWORD  Flags;
    RECT   rcVirtualScreen;
};
DECLARE_HANDLE(HPBUFFERARB);
DECLARE_HANDLE(HPBUFFEREXT);
DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
DECLARE_HANDLE(HPVIDEODEV);
DECLARE_HANDLE(HPGPUNV);
DECLARE_HANDLE(HGPUNV);
DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
typedef struct _GPU_DEVICE GPU_DEVICE;
typedef struct _GPU_DEVICE *PGPU_DEVICE;
#define WGL_ACCESS_READ_ONLY_NV 0x00000000
#define WGL_ACCESS_READ_WRITE_NV 0x00000001
#define WGL_ACCESS_WRITE_DISCARD_NV 0x00000002
#ifndef WGL_ARB_extensions_string
#define WGL_ARB_extensions_string 1
GLAPI int GLAD_WGL_ARB_extensions_string;
typedef const char * (APIENTRYP PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
GLAPI PFNWGLGETEXTENSIONSSTRINGARBPROC glad_wglGetExtensionsStringARB;
#define wglGetExtensionsStringARB glad_wglGetExtensionsStringARB
#endif
#ifndef WGL_EXT_extensions_string
#define WGL_EXT_extensions_string 1
GLAPI int GLAD_WGL_EXT_extensions_string;
typedef const char * (APIENTRYP PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
GLAPI PFNWGLGETEXTENSIONSSTRINGEXTPROC glad_wglGetExtensionsStringEXT;
#define wglGetExtensionsStringEXT glad_wglGetExtensionsStringEXT
#endif
#ifndef WGL_NV_DX_interop
#define WGL_NV_DX_interop 1
GLAPI int GLAD_WGL_NV_DX_interop;
typedef BOOL (APIENTRYP PFNWGLDXSETRESOURCESHAREHANDLENVPROC)(void *dxObject, HANDLE shareHandle);
GLAPI PFNWGLDXSETRESOURCESHAREHANDLENVPROC glad_wglDXSetResourceShareHandleNV;
#define wglDXSetResourceShareHandleNV glad_wglDXSetResourceShareHandleNV
typedef HANDLE (APIENTRYP PFNWGLDXOPENDEVICENVPROC)(void *dxDevice);
GLAPI PFNWGLDXOPENDEVICENVPROC glad_wglDXOpenDeviceNV;
#define wglDXOpenDeviceNV glad_wglDXOpenDeviceNV
typedef BOOL (APIENTRYP PFNWGLDXCLOSEDEVICENVPROC)(HANDLE hDevice);
GLAPI PFNWGLDXCLOSEDEVICENVPROC glad_wglDXCloseDeviceNV;
#define wglDXCloseDeviceNV glad_wglDXCloseDeviceNV
typedef HANDLE (APIENTRYP PFNWGLDXREGISTEROBJECTNVPROC)(HANDLE hDevice, void *dxObject, GLuint name, GLenum type, GLenum access);
GLAPI PFNWGLDXREGISTEROBJECTNVPROC glad_wglDXRegisterObjectNV;
#define wglDXRegisterObjectNV glad_wglDXRegisterObjectNV
typedef BOOL (APIENTRYP PFNWGLDXUNREGISTEROBJECTNVPROC)(HANDLE hDevice, HANDLE hObject);
GLAPI PFNWGLDXUNREGISTEROBJECTNVPROC glad_wglDXUnregisterObjectNV;
#define wglDXUnregisterObjectNV glad_wglDXUnregisterObjectNV
typedef BOOL (APIENTRYP PFNWGLDXOBJECTACCESSNVPROC)(HANDLE hObject, GLenum access);
GLAPI PFNWGLDXOBJECTACCESSNVPROC glad_wglDXObjectAccessNV;
#define wglDXObjectAccessNV glad_wglDXObjectAccessNV
typedef BOOL (APIENTRYP PFNWGLDXLOCKOBJECTSNVPROC)(HANDLE hDevice, GLint count, HANDLE *hObjects);
GLAPI PFNWGLDXLOCKOBJECTSNVPROC glad_wglDXLockObjectsNV;
#define wglDXLockObjectsNV glad_wglDXLockObjectsNV
typedef BOOL (APIENTRYP PFNWGLDXUNLOCKOBJECTSNVPROC)(HANDLE hDevice, GLint count, HANDLE *hObjects);
GLAPI PFNWGLDXUNLOCKOBJECTSNVPROC glad_wglDXUnlockObjectsNV;
#define wglDXUnlockObjectsNV glad_wglDXUnlockObjectsNV
#endif

#ifdef __cplusplus
}
#endif

#endif
