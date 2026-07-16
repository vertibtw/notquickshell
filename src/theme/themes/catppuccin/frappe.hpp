#pragma once

#include <string_view>
namespace themes::catppuccin {
inline constexpr std::string_view frappe =
    R"CSS(:root {
        --background_main: #292c3c;
        --background_secondary: #303446;
        --background_light: ;
        --foreground_main: #c6d0f5;
        --foreground_secondary: #838ba7;
        --red: #e78284;
        --orange: #ef9f76;
        --green: #a6d189;
        --blue: #8caaee;
        --purple: #ca9ee6;
    })CSS";
} // namespace themes::catppuccin
