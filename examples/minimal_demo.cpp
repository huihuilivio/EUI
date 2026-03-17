#ifndef EUI_ENABLE_GLFW_OPENGL_BACKEND
#define EUI_ENABLE_GLFW_OPENGL_BACKEND 1
#endif
#include "EUI.h"

#include <algorithm>
#include <string>

struct MinimalState {
    bool dark_mode{false};
    int clicks{0};
    float progress{0.0f};
    std::string name{"EUI"};
};

int main() {
    MinimalState state{};
    eui::demo::AppOptions options{};
    options.title = "EUI Minimal Demo";
    options.width = 560;
    options.height = 360;
    options.vsync = true;
    options.continuous_render = false;
    options.max_fps = 120.0;

    return eui::demo::run(
        [&](eui::demo::FrameContext frame) {
            auto& ui = frame.ui;
            const float scale = std::max(1.0f, frame.dpi_scale);
            const auto dp = [scale](float value) { return value * scale; };

            ui.set_theme_mode(state.dark_mode ? eui::ThemeMode::Dark : eui::ThemeMode::Light);
            ui.set_primary_color(eui::rgba(0.30f, 0.74f, 0.77f, 1.0f));
            ui.set_corner_radius(12.0f * scale);

            const float margin = dp(16.0f);
            const float panel_w =
                std::max(dp(260.0f), static_cast<float>(frame.framebuffer_w) - margin * 2.0f);
            ui.begin_panel("", margin, dp(16.0f), panel_w, 0.0f, -1.0f);

            ui.begin_card("MINIMAL");
            ui.label("A compact interactive demo.", dp(12.0f), true);
            ui.input_text("Name", state.name, dp(34.0f));

            ui.begin_row(3, dp(8.0f));
            if (ui.button(state.dark_mode ? "Light" : "Dark", eui::ButtonStyle::Secondary, dp(34.0f))) {
                state.dark_mode = !state.dark_mode;
            }
            if (ui.button("Click +1", eui::ButtonStyle::Primary, dp(34.0f))) {
                state.clicks += 1;
                state.progress = std::min(1.0f, static_cast<float>(state.clicks) / 10.0f);
            }
            ui.input_readonly("Clicks", std::to_string(state.clicks), dp(34.0f), true, 1.0f, false);
            ui.end_row();

            ui.progress("Progress", state.progress, dp(24.0f));
            ui.end_card();

            ui.end_panel();
        },
        options);
}

#if defined(_WIN32)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main();
}
#endif
