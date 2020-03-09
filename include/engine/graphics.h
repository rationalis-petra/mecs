#ifndef GRAPHICS_BACKEND
#define GRAPHICS_BACKEND OPEN_GL
#endif

#if GRAPHICS_BACKEND == OPEN_GL
#include "engine/graphics/opengl.h"
#elif GRAPHICS_BACKEND == VULKAN
#include"engine/graphics/vulkan.h"
#else
#error UNSUPPORTED_GRAPHICS_BACKEND: GRAPHICS_BACKEND
#endif

#include "engine/graphics/window.h"
