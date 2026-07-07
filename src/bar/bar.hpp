#pragma once
#include <glibmm/main.h>
#include <gtk/gtk.h>
#include <gtkmm.h>
#include <gtk4-layer-shell/gtk4-layer-shell.h>
#include <gtkmm/box.h>
#include <gtkmm/centerbox.h>
#include <gtkmm/object.h>
#include <memory>
#include <string>

#include "../ini/ini.hpp"
#include "../ipc/hyprland/ipc.hpp"
#include "../theme/theme.hpp"
#include "../util/is_int.hpp"
#include "clock.hpp"
#include "workspaces.hpp"
#include "volume/volume_button.hpp"
#include "volume/volume_window.hpp"

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
