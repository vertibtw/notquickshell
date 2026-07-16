#pragma once

#include <string_view>
namespace themes::catppuccin {
inline constexpr std::string_view latte =
    R"CSS(:root {
        --background_main: #e6e9ef;
        --background_secondary: #eff1f5;
        --background_light: ;
        --foreground_main: #4c4f69;
        --foreground_secondary: #8c8fa1;
        --red: #d20f39;
        --orange: #fe640b;
        --green: #40a02b;
        --blue: #1e66f5;
        --purple: #8839ef;
    }
)CSS";
} // namespace themes::catppuccin
