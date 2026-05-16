// Provide STB implementations that bgfx's imconfig.h strips from Dear ImGui.
// Must NOT include imgui.h — imconfig.h would re-disable the implementations.
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb/stb_rect_pack.h>

#define STBTT_malloc(x, u)  malloc(x)
#define STBTT_free(x, u)    free(x)
#define STBTT_assert(x)     ((void)(x))
#define STBTT_fmod(x, y)    fmod((x), (y))
#define STBTT_sqrt(x)       sqrt(x)
#define STBTT_pow(x, y)     pow((x), (y))
#define STBTT_fabs(x)       fabs(x)
#define STBTT_ifloor(x)     ((int)floor(x))
#define STBTT_iceil(x)      ((int)ceil(x))
#define STBTT_strlen(x)     strlen(x)
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>