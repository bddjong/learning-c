#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "shader.h"

typedef struct {
    float position[3];
    float color[4];
} vertex_t;

static const vertex_t vertices[] = {
    { { 0.0f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} }, // Top vertex - Red
    { {-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} }, // Bottom left - Green
    { { 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} }  // Bottom right - Blue
};

static sg_pipeline pipeline;
static sg_bindings bindings;

static void init_cb(void) {
    sg_setup(&(sg_desc){
        .environment = sglue_environment()
    });

    bindings.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
        .data = SG_RANGE(vertices),
        .label = "triangle_vertices"
    });

    sg_shader shd = sg_make_shader(triangle_shader_desc(sg_query_backend()));

    pipeline = sg_make_pipeline(&(sg_pipeline_desc){
        .shader = shd,
        .layout = {
            .attrs = {
                [ATTR_triangle_position].format = SG_VERTEXFORMAT_FLOAT3,
                [ATTR_triangle_color0].format = SG_VERTEXFORMAT_FLOAT4,
            }
        }
    });
}

static void frame_cb(void) {
    sg_pass_action pass = {
        .colors[0] = {
            .load_action = SG_LOADACTION_CLEAR,
            .clear_value = { 0.0f, 0.0f, 0.0f, 1.0f }
        }
    };
    sg_begin_pass(&(sg_pass){
        .action    = pass,
        .swapchain = sglue_swapchain()
    });
    sg_apply_pipeline(pipeline);
    sg_apply_bindings(&bindings);
    sg_draw(0, 3, 1);
    sg_end_pass();
    sg_commit();
}

static void cleanup_cb(void) {
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb        = init_cb,
        .frame_cb       = frame_cb,
        .cleanup_cb     = cleanup_cb,
        .width          = 800,
        .height         = 600,
        .window_title   = "Sokol Metal Window",
        .icon.sokol_default = true,
        .high_dpi       = true,
    };
}
