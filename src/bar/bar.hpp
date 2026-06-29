#pragma once
#include <gtkmm.h>
#include <gtk4-layer-shell/gtk4-layer-shell.h>
#include <memory>

#include "../ini/ini.hpp"

namespace widgets {

    class Bar : public Gtk::Window {
        public:
        Bar (std::shared_ptr<ini>);
        ~Bar() = default;
    };

}