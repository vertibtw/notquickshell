#pragma once
#include <gtkmm.h>
#include "volume_window.hpp"

class VolumeButton : public Gtk::MenuButton {
    public:
    std::string label = "";
    VolumeButton (VolumeWindow*);
    ~VolumeButton() = default;
};
