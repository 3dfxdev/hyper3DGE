/*

    WGL loader generated by glad 0.1.16a0 on Sat Feb 10 06:36:28 2018.

    Language/Generator: C/C++
    Specification: wgl
    APIs: wgl=1.0
    Profile: -
    Extensions:
        WGL_ARB_create_context,
        WGL_ARB_create_context_no_error,
        WGL_ARB_create_context_profile,
        WGL_ARB_create_context_robustness,
        WGL_ARB_extensions_string,
        WGL_ARB_multisample,
        WGL_ARB_pbuffer,
        WGL_ARB_pixel_format,
        WGL_ARB_render_texture,
        WGL_EXT_extensions_string,
        WGL_EXT_swap_control,
        WGL_EXT_swap_control_tear,
        WGL_OML_sync_control
    Loader: True
    Local files: False
    Omit khrplatform: False

    Commandline:
        --api="wgl=1.0" --generator="c" --spec="wgl" --extensions="WGL_ARB_create_context,WGL_ARB_create_context_no_error,WGL_ARB_create_context_profile,WGL_ARB_create_context_robustness,WGL_ARB_extensions_string,WGL_ARB_multisample,WGL_ARB_pbuffer,WGL_ARB_pixel_format,WGL_ARB_render_texture,WGL_EXT_extensions_string,WGL_EXT_swap_control,WGL_EXT_swap_control_tear,WGL_OML_sync_control"
    Online:
        http://glad.dav1d.de/#language=c&specification=wgl&loader=on&api=wgl%3D1.0&extensions=WGL_ARB_create_context&extensions=WGL_ARB_create_context_no_error&extensions=WGL_ARB_create_context_profile&extensions=WGL_ARB_create_context_robustness&extensions=WGL_ARB_extensions_string&extensions=WGL_ARB_multisample&extensions=WGL_ARB_pbuffer&extensions=WGL_ARB_pixel_format&extensions=WGL_ARB_render_texture&extensions=WGL_EXT_extensions_string&extensions=WGL_EXT_swap_control&extensions=WGL_EXT_swap_control_tear&extensions=WGL_OML_sync_control
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad_wgl.h>

static void* get_proc(const char *namez);

#ifdef _WIN32
#include <windows.h>
static HMODULE libGL;

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

static
int open_gl(void) {
    libGL = LoadLibraryW(L"opengl32.dll");
    if(libGL != NULL) {
        gladGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE)GetProcAddress(
                libGL, "wglGetProcAddress");
        return gladGetProcAddressPtr != NULL;
    }

    return 0;
}

static
void close_gl(void) {
    if(libGL != NULL) {
        FreeLibrary(libGL);
        libGL = NULL;
    }
}
#else
#include <dlfcn.h>
static void* libGL;

#ifndef __APPLE__
typedef void* (APIENTRYP PFNGLXGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNGLXGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;
#endif

static
int open_gl(void) {
#ifdef __APPLE__
    static const char *NAMES[] = {
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
    };
#else
    static const char *NAMES[] = {"libGL.so.1", "libGL.so"};
#endif

    unsigned int index = 0;
    for(index = 0; index < (sizeof(NAMES) / sizeof(NAMES[0])); index++) {
        libGL = dlopen(NAMES[index], RTLD_NOW | RTLD_GLOBAL);

        if(libGL != NULL) {
#ifdef __APPLE__
            return 1;
#else
            gladGetProcAddressPtr = (PFNGLXGETPROCADDRESSPROC_PRIVATE)dlsym(libGL,
                "glXGetProcAddressARB");
            return gladGetProcAddressPtr != NULL;
#endif
        }
    }

    return 0;
}

static
void close_gl(void) {
    if(libGL != NULL) {
        dlclose(libGL);
        libGL = NULL;
    }
}
#endif

static
void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;

#ifndef __APPLE__
    if(gladGetProcAddressPtr != NULL) {
        result = gladGetProcAddressPtr(namez);
    }
#endif
    if(result == NULL) {
#ifdef _WIN32
        result = (void*)GetProcAddress(libGL, namez);
#else
        result = dlsym(libGL, namez);
#endif
    }

    return result;
}

int gladLoadWGL(HDC hdc) {
    int status = 0;

    if(open_gl()) {
        status = gladLoadWGLLoader((GLADloadproc)get_proc, hdc);
        close_gl();
    }

    return status;
}

static HDC GLADWGLhdc = (HDC)INVALID_HANDLE_VALUE;

static int get_exts(void) {
    return 1;
}

static void free_exts(void) {
    return;
}

static int has_ext(const char *ext) {
    const char *terminator;
    const char *loc;
    const char *extensions;

    if(wglGetExtensionsStringEXT == NULL && wglGetExtensionsStringARB == NULL)
        return 0;

    if(wglGetExtensionsStringARB == NULL || GLADWGLhdc == INVALID_HANDLE_VALUE)
        extensions = wglGetExtensionsStringEXT();
    else
        extensions = wglGetExtensionsStringARB(GLADWGLhdc);

    if(extensions == NULL || ext == NULL)
        return 0;

    while(1) {
        loc = strstr(extensions, ext);
        if(loc == NULL)
            break;

        terminator = loc + strlen(ext);
        if((loc == extensions || *(loc - 1) == ' ') &&
            (*terminator == ' ' || *terminator == '\0'))
        {
            return 1;
        }
        extensions = terminator;
    }

    return 0;
}
int GLAD_WGL_VERSION_1_0;
int GLAD_WGL_ARB_create_context_no_error;
int GLAD_WGL_ARB_create_context_robustness;
int GLAD_WGL_EXT_swap_control_tear;
int GLAD_WGL_EXT_swap_control;
int GLAD_WGL_ARB_pixel_format;
int GLAD_WGL_OML_sync_control;
int GLAD_WGL_ARB_multisample;
int GLAD_WGL_ARB_pbuffer;
int GLAD_WGL_ARB_create_context_profile;
int GLAD_WGL_ARB_render_texture;
int GLAD_WGL_ARB_extensions_string;
int GLAD_WGL_ARB_create_context;
int GLAD_WGL_EXT_extensions_string;
PFNWGLCREATECONTEXTATTRIBSARBPROC glad_wglCreateContextAttribsARB;
PFNWGLGETEXTENSIONSSTRINGARBPROC glad_wglGetExtensionsStringARB;
PFNWGLCREATEPBUFFERARBPROC glad_wglCreatePbufferARB;
PFNWGLGETPBUFFERDCARBPROC glad_wglGetPbufferDCARB;
PFNWGLRELEASEPBUFFERDCARBPROC glad_wglReleasePbufferDCARB;
PFNWGLDESTROYPBUFFERARBPROC glad_wglDestroyPbufferARB;
PFNWGLQUERYPBUFFERARBPROC glad_wglQueryPbufferARB;
PFNWGLGETPIXELFORMATATTRIBIVARBPROC glad_wglGetPixelFormatAttribivARB;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC glad_wglGetPixelFormatAttribfvARB;
PFNWGLCHOOSEPIXELFORMATARBPROC glad_wglChoosePixelFormatARB;
PFNWGLBINDTEXIMAGEARBPROC glad_wglBindTexImageARB;
PFNWGLRELEASETEXIMAGEARBPROC glad_wglReleaseTexImageARB;
PFNWGLSETPBUFFERATTRIBARBPROC glad_wglSetPbufferAttribARB;
PFNWGLGETEXTENSIONSSTRINGEXTPROC glad_wglGetExtensionsStringEXT;
PFNWGLSWAPINTERVALEXTPROC glad_wglSwapIntervalEXT;
PFNWGLGETSWAPINTERVALEXTPROC glad_wglGetSwapIntervalEXT;
PFNWGLGETSYNCVALUESOMLPROC glad_wglGetSyncValuesOML;
PFNWGLGETMSCRATEOMLPROC glad_wglGetMscRateOML;
PFNWGLSWAPBUFFERSMSCOMLPROC glad_wglSwapBuffersMscOML;
PFNWGLSWAPLAYERBUFFERSMSCOMLPROC glad_wglSwapLayerBuffersMscOML;
PFNWGLWAITFORMSCOMLPROC glad_wglWaitForMscOML;
PFNWGLWAITFORSBCOMLPROC glad_wglWaitForSbcOML;
static void load_WGL_ARB_create_context(GLADloadproc load) {
	if(!GLAD_WGL_ARB_create_context) return;
	glad_wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)load("wglCreateContextAttribsARB");
}
static void load_WGL_ARB_extensions_string(GLADloadproc load) {
	if(!GLAD_WGL_ARB_extensions_string) return;
	glad_wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)load("wglGetExtensionsStringARB");
}
static void load_WGL_ARB_pbuffer(GLADloadproc load) {
	if(!GLAD_WGL_ARB_pbuffer) return;
	glad_wglCreatePbufferARB = (PFNWGLCREATEPBUFFERARBPROC)load("wglCreatePbufferARB");
	glad_wglGetPbufferDCARB = (PFNWGLGETPBUFFERDCARBPROC)load("wglGetPbufferDCARB");
	glad_wglReleasePbufferDCARB = (PFNWGLRELEASEPBUFFERDCARBPROC)load("wglReleasePbufferDCARB");
	glad_wglDestroyPbufferARB = (PFNWGLDESTROYPBUFFERARBPROC)load("wglDestroyPbufferARB");
	glad_wglQueryPbufferARB = (PFNWGLQUERYPBUFFERARBPROC)load("wglQueryPbufferARB");
}
static void load_WGL_ARB_pixel_format(GLADloadproc load) {
	if(!GLAD_WGL_ARB_pixel_format) return;
	glad_wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)load("wglGetPixelFormatAttribivARB");
	glad_wglGetPixelFormatAttribfvARB = (PFNWGLGETPIXELFORMATATTRIBFVARBPROC)load("wglGetPixelFormatAttribfvARB");
	glad_wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)load("wglChoosePixelFormatARB");
}
static void load_WGL_ARB_render_texture(GLADloadproc load) {
	if(!GLAD_WGL_ARB_render_texture) return;
	glad_wglBindTexImageARB = (PFNWGLBINDTEXIMAGEARBPROC)load("wglBindTexImageARB");
	glad_wglReleaseTexImageARB = (PFNWGLRELEASETEXIMAGEARBPROC)load("wglReleaseTexImageARB");
	glad_wglSetPbufferAttribARB = (PFNWGLSETPBUFFERATTRIBARBPROC)load("wglSetPbufferAttribARB");
}
static void load_WGL_EXT_extensions_string(GLADloadproc load) {
	if(!GLAD_WGL_EXT_extensions_string) return;
	glad_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)load("wglGetExtensionsStringEXT");
}
static void load_WGL_EXT_swap_control(GLADloadproc load) {
	if(!GLAD_WGL_EXT_swap_control) return;
	glad_wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)load("wglSwapIntervalEXT");
	glad_wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)load("wglGetSwapIntervalEXT");
}
static void load_WGL_OML_sync_control(GLADloadproc load) {
	if(!GLAD_WGL_OML_sync_control) return;
	glad_wglGetSyncValuesOML = (PFNWGLGETSYNCVALUESOMLPROC)load("wglGetSyncValuesOML");
	glad_wglGetMscRateOML = (PFNWGLGETMSCRATEOMLPROC)load("wglGetMscRateOML");
	glad_wglSwapBuffersMscOML = (PFNWGLSWAPBUFFERSMSCOMLPROC)load("wglSwapBuffersMscOML");
	glad_wglSwapLayerBuffersMscOML = (PFNWGLSWAPLAYERBUFFERSMSCOMLPROC)load("wglSwapLayerBuffersMscOML");
	glad_wglWaitForMscOML = (PFNWGLWAITFORMSCOMLPROC)load("wglWaitForMscOML");
	glad_wglWaitForSbcOML = (PFNWGLWAITFORSBCOMLPROC)load("wglWaitForSbcOML");
}
static int find_extensionsWGL(void) {
	if (!get_exts()) return 0;
	GLAD_WGL_ARB_create_context = has_ext("WGL_ARB_create_context");
	GLAD_WGL_ARB_create_context_no_error = has_ext("WGL_ARB_create_context_no_error");
	GLAD_WGL_ARB_create_context_profile = has_ext("WGL_ARB_create_context_profile");
	GLAD_WGL_ARB_create_context_robustness = has_ext("WGL_ARB_create_context_robustness");
	GLAD_WGL_ARB_extensions_string = has_ext("WGL_ARB_extensions_string");
	GLAD_WGL_ARB_multisample = has_ext("WGL_ARB_multisample");
	GLAD_WGL_ARB_pbuffer = has_ext("WGL_ARB_pbuffer");
	GLAD_WGL_ARB_pixel_format = has_ext("WGL_ARB_pixel_format");
	GLAD_WGL_ARB_render_texture = has_ext("WGL_ARB_render_texture");
	GLAD_WGL_EXT_extensions_string = has_ext("WGL_EXT_extensions_string");
	GLAD_WGL_EXT_swap_control = has_ext("WGL_EXT_swap_control");
	GLAD_WGL_EXT_swap_control_tear = has_ext("WGL_EXT_swap_control_tear");
	GLAD_WGL_OML_sync_control = has_ext("WGL_OML_sync_control");
	free_exts();
	return 1;
}

static void find_coreWGL(HDC hdc) {
	GLADWGLhdc = hdc;
}

int gladLoadWGLLoader(GLADloadproc load, HDC hdc) {
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)load("wglGetExtensionsStringARB");
	wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)load("wglGetExtensionsStringEXT");
	if(wglGetExtensionsStringARB == NULL && wglGetExtensionsStringEXT == NULL) return 0;
	find_coreWGL(hdc);

	if (!find_extensionsWGL()) return 0;
	load_WGL_ARB_create_context(load);
	load_WGL_ARB_extensions_string(load);
	load_WGL_ARB_pbuffer(load);
	load_WGL_ARB_pixel_format(load);
	load_WGL_ARB_render_texture(load);
	load_WGL_EXT_extensions_string(load);
	load_WGL_EXT_swap_control(load);
	load_WGL_OML_sync_control(load);
	return 1;
}

