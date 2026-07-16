#pragma once

#include <string_view>
namespace themes::catppuccin {
inline constexpr std::string_view macchiato =
    R"CSS(:root {
    --background_main: #1e2030;
    --background_secondary: #24273a;
    --background_light: ;
    --foreground_main: #cad3f5;
    --foreground_secondary: #8087a2;
    --red: #ed8796;
    --orange: #f5a97f;
    --green: #a6da95;
    --blue: #8aadf4;
    --purple: #c6a0f6;
    })CSS";
} // namespace themes::catppuccin
