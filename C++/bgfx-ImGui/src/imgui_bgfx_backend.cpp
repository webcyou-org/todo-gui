#include "imgui_bgfx_backend.h"

#include <dear-imgui/imgui.h>
#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>
#include <bx/math.h>

// Precompiled shader binary headers from bgfx's imgui examples
#include "imgui/vs_ocornut_imgui.bin.h"
#include "imgui/fs_ocornut_imgui.bin.h"

#include <cstring>

static const bgfx::EmbeddedShader s_shaders[] = {
    BGFX_EMBEDDED_SHADER(vs_ocornut_imgui),
    BGFX_EMBEDDED_SHADER(fs_ocornut_imgui),
    BGFX_EMBEDDED_SHADER_END()
};

namespace {

struct Context {
    bgfx::ViewId        view_id  = 255;
    bgfx::VertexLayout  layout;
    bgfx::ProgramHandle program  = BGFX_INVALID_HANDLE;
    bgfx::UniformHandle s_tex    = BGFX_INVALID_HANDLE;
};

static Context s_ctx;

// Convert ImGui pixel data (RGBA32 or Alpha8) → BGRA8 for bgfx/Metal
static bgfx::TextureHandle create_bgfx_texture(const ImTextureData* tex) {
    const int pixels = tex->Width * tex->Height;
    uint8_t* bgra = new uint8_t[pixels * 4];

    if (tex->Format == ImTextureFormat_RGBA32) {
        for (int i = 0; i < pixels; ++i) {
            bgra[i*4+0] = tex->Pixels[i*4+2]; // B ← R
            bgra[i*4+1] = tex->Pixels[i*4+1]; // G
            bgra[i*4+2] = tex->Pixels[i*4+0]; // R ← B
            bgra[i*4+3] = tex->Pixels[i*4+3]; // A
        }
    } else { // Alpha8 → white BGRA
        for (int i = 0; i < pixels; ++i) {
            bgra[i*4+0] = bgra[i*4+1] = bgra[i*4+2] = 255;
            bgra[i*4+3] = tex->Pixels[i];
        }
    }

    bgfx::TextureHandle handle = bgfx::createTexture2D(
        (uint16_t)tex->Width, (uint16_t)tex->Height, false, 1,
        bgfx::TextureFormat::BGRA8, 0,
        bgfx::copy(bgra, pixels * 4));
    delete[] bgra;
    return handle;
}

// Update a subrect of an existing bgfx texture
static void update_bgfx_texture_rect(bgfx::TextureHandle handle,
                                      const ImTextureData* tex,
                                      const ImTextureRect& rect)
{
    const int rw = rect.w, rh = rect.h;
    uint8_t* bgra = new uint8_t[rw * rh * 4];

    for (int row = 0; row < rh; ++row) {
        const uint8_t* src = tex->Pixels
            + ((rect.y + row) * tex->Width + rect.x) * tex->BytesPerPixel;
        uint8_t* dst = bgra + row * rw * 4;

        if (tex->Format == ImTextureFormat_RGBA32) {
            for (int col = 0; col < rw; ++col) {
                dst[col*4+0] = src[col*4+2];
                dst[col*4+1] = src[col*4+1];
                dst[col*4+2] = src[col*4+0];
                dst[col*4+3] = src[col*4+3];
            }
        } else {
            for (int col = 0; col < rw; ++col) {
                dst[col*4+0] = dst[col*4+1] = dst[col*4+2] = 255;
                dst[col*4+3] = src[col];
            }
        }
    }

    bgfx::updateTexture2D(handle, 0, 0,
        (uint16_t)rect.x, (uint16_t)rect.y,
        (uint16_t)rw, (uint16_t)rh,
        bgfx::copy(bgra, rw * rh * 4),
        (uint16_t)(rw * 4));
    delete[] bgra;
}

// Handle ImTextureData state machine for one texture
static void process_texture(ImTextureData* tex) {
    switch (tex->Status) {
        case ImTextureStatus_WantCreate: {
            bgfx::TextureHandle handle = create_bgfx_texture(tex);
            tex->SetTexID((ImTextureID)handle.idx);
            tex->SetStatus(ImTextureStatus_OK);
            break;
        }
        case ImTextureStatus_WantUpdates: {
            bgfx::TextureHandle handle;
            handle.idx = (uint16_t)(ImU64)tex->TexID;
            for (const ImTextureRect& rect : tex->Updates)
                update_bgfx_texture_rect(handle, tex, rect);
            tex->SetStatus(ImTextureStatus_OK);
            break;
        }
        case ImTextureStatus_WantDestroy: {
            bgfx::TextureHandle handle;
            handle.idx = (uint16_t)(ImU64)tex->TexID;
            bgfx::destroy(handle);
            tex->SetTexID(ImTextureID_Invalid);
            tex->SetStatus(ImTextureStatus_Destroyed);
            break;
        }
        default:
            break;
    }
}

} // namespace

namespace ImGui_Bgfx {

bool Init(bgfx::ViewId view_id) {
    s_ctx.view_id = view_id;

    // Vertex layout matching ImDrawVert exactly: pos(2f), uv(2f), col(4u8)
    s_ctx.layout.begin()
        .add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
        .end();

    bgfx::RendererType::Enum type = bgfx::getRendererType();
    s_ctx.program = bgfx::createProgram(
        bgfx::createEmbeddedShader(s_shaders, type, "vs_ocornut_imgui"),
        bgfx::createEmbeddedShader(s_shaders, type, "fs_ocornut_imgui"),
        true);

    s_ctx.s_tex = bgfx::createUniform("s_tex", bgfx::UniformType::Sampler);

    // Tell ImGui 1.92+ that this backend handles texture management
    ImGui::GetIO().BackendFlags |= ImGuiBackendFlags_RendererHasTextures;

    return bgfx::isValid(s_ctx.program);
}

void Shutdown() {
    // Destroy all GPU textures still tracked by ImGui
    ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
    for (ImTextureData* tex : pio.Textures) {
        if (tex->TexID != ImTextureID_Invalid) {
            bgfx::TextureHandle handle;
            handle.idx = (uint16_t)(ImU64)tex->TexID;
            bgfx::destroy(handle);
            tex->SetTexID(ImTextureID_Invalid);
            tex->SetStatus(ImTextureStatus_Destroyed);
        }
    }
    bgfx::destroy(s_ctx.program);
    bgfx::destroy(s_ctx.s_tex);
    s_ctx = {};
}

void RenderDrawData(ImDrawData* draw_data) {
    if (!draw_data) return;

    // ── Texture management (ImGui 1.92 new API) ──────────────────────────────
    if (draw_data->Textures) {
        for (ImTextureData* tex : *draw_data->Textures)
            process_texture(tex);
    }

    if (draw_data->CmdListsCount == 0) return;

    // ── View transform (orthographic) ────────────────────────────────────────
    float L = draw_data->DisplayPos.x;
    float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
    float T = draw_data->DisplayPos.y;
    float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
    float ortho[16];
    bx::mtxOrtho(ortho, L, R, B, T, 0.f, 1000.f, 0.f,
                 bgfx::getCaps()->homogeneousDepth);
    bgfx::setViewTransform(s_ctx.view_id, nullptr, ortho);

    const uint64_t state =
        BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A |
        BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA,
                               BGFX_STATE_BLEND_INV_SRC_ALPHA);

    // ── Draw lists ───────────────────────────────────────────────────────────
    for (int n = 0; n < draw_data->CmdListsCount; ++n) {
        const ImDrawList* dl    = draw_data->CmdLists[n];
        const uint32_t    nv    = (uint32_t)dl->VtxBuffer.Size;
        const uint32_t    ni    = (uint32_t)dl->IdxBuffer.Size;
        const bool        idx32 = sizeof(ImDrawIdx) == 4;

        if (bgfx::getAvailTransientVertexBuffer(nv, s_ctx.layout) < nv ||
            bgfx::getAvailTransientIndexBuffer(ni, idx32) < ni)
            continue;

        bgfx::TransientVertexBuffer tvb;
        bgfx::TransientIndexBuffer  tib;
        bgfx::allocTransientVertexBuffer(&tvb, nv, s_ctx.layout);
        bgfx::allocTransientIndexBuffer(&tib, ni, idx32);

        memcpy(tvb.data, dl->VtxBuffer.Data, nv * sizeof(ImDrawVert));
        memcpy(tib.data, dl->IdxBuffer.Data, ni * sizeof(ImDrawIdx));

        uint32_t offset = 0;
        for (const ImDrawCmd& cmd : dl->CmdBuffer) {
            if (cmd.UserCallback) {
                cmd.UserCallback(dl, &cmd);
            } else {
                ImVec2 clip_min = {cmd.ClipRect.x - draw_data->DisplayPos.x,
                                   cmd.ClipRect.y - draw_data->DisplayPos.y};
                ImVec2 clip_max = {cmd.ClipRect.z - draw_data->DisplayPos.x,
                                   cmd.ClipRect.w - draw_data->DisplayPos.y};
                if (clip_max.x <= clip_min.x || clip_max.y <= clip_min.y) {
                    offset += cmd.ElemCount;
                    continue;
                }

                bgfx::setScissor(
                    (uint16_t)clip_min.x, (uint16_t)clip_min.y,
                    (uint16_t)(clip_max.x - clip_min.x),
                    (uint16_t)(clip_max.y - clip_min.y));

                bgfx::TextureHandle tex;
                // ImDrawCmd::GetTexID() resolves ImTextureRef → ImTextureID
                tex.idx = (uint16_t)(ImU64)cmd.GetTexID();
                bgfx::setTexture(0, s_ctx.s_tex, tex);

                bgfx::setState(state);
                bgfx::setVertexBuffer(0, &tvb, 0, nv);
                bgfx::setIndexBuffer(&tib, offset, cmd.ElemCount);
                bgfx::submit(s_ctx.view_id, s_ctx.program);
            }
            offset += cmd.ElemCount;
        }
    }
}

} // namespace ImGui_Bgfx