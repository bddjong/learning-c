#import <Cocoa/Cocoa.h>
#import "sokol_app.h"
#import "sokol_gfx.h"
#import "sokol_glue.h"

static void init_cb(void) {
    sg_setup(&(sg_desc){
        .environment = sglue_environment()
    });
}

static void frame_cb(void) {
    sg_pass_action pass = {
        .colors[0] = {
            .load_action = SG_LOADACTION_CLEAR,
            .clear_value = { 1.0f, 0.0f, 0.0f, 1.0f }
        }
    };
    sg_begin_pass(&(sg_pass){
        .action    = pass,
        .swapchain = sglue_swapchain()
    });
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
