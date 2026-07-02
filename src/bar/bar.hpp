#pragma once
#include <gtkmm.h>
#include <gtk4-layer-shell/gtk4-layer-shell.h>
#include <memory>

#include "../ini/ini.hpp"
#include "../ipc/hyprland/ipc.hpp"

namespace widgets {

    class Bar : public Gtk::Window {
        private:
        bool vertical = false;
        bool horizontal = false;
        std::shared_ptr<hyprland::Ipc> ipc;

        public:
        Bar (std::shared_ptr<ini>);
        ~Bar() = default;
    };

}