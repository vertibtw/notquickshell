#pragma once
#include <gtkmm.h>

namespace hyprland {
    struct Workspace : public Gtk::Box {
        int id = -1;
        bool active = false;
        bool exists = false; 
        bool irregular = false;
    };
}