#pragma once
#include <string>

namespace theme {
    struct theme {
        std::string background_main;
        std::string background_secondary;
        std::string foreground_main;
        std::string foreground_secondary;
        // TODO: better naming 
        std::string red;
        std::string green;
        std::string blue;
        std::string purple;
    };

    const theme catppuccin_mocha {
        .background_main      = "#1e1e2e",
        .background_secondary = "#313244",
        .foreground_main      = "#cdd6f4",
        .foreground_secondary = "#7f849c",
        .red                  = "#f38ba8",
        .green                = "#a6e3a1",
        .blue                 = "#89b4fa",
        .purple               = "#cba6f7",
    };

    const theme catppuccin_macchiato {
        .background_main      = "#1e2030",
        .background_secondary = "#24273a",
        .foreground_main      = "#cad3f5",
        .foreground_secondary = "#8087a2",
        .red                  = "#ed8796",
        .green                = "#a6da95",
        .blue                 = "#8aadf4",
        .purple               = "#c6a0f6",
    };

    const theme catppuccin_frappe {
        .background_main      = "#292c3c",
        .background_secondary = "#303446",
        .foreground_main      = "#c6d0f5",
        .foreground_secondary = "#838ba7",
        .red                  = "#e78284",
        .green                = "#a6d189",
        .blue                 = "#8caaee",
        .purple               = "#ca9ee6",
    };

    const theme catppuccin_latte {
        .background_main      = "#e6e9ef",
        .background_secondary = "#eff1f5",
        .foreground_main      = "#4c4f69",
        .foreground_secondary = "#8c8fa1",
        .red                  = "#d20f39",
        .green                = "#40a02b",
        .blue                 = "#1e66f5",
        .purple               = "#8839ef",
    };
}