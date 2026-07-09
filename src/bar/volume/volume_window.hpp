#pragma once

#include <gtkmm.h>
#include <memory>

namespace bar::modules {

class VolumeWindow : public Gtk::Popover {
public:
    VolumeWindow();
    double get_volume() const;
    bool get_muted() const;

private:
    Gtk::Scale *slider = nullptr;
    Gtk::ToggleButton *mute_btn = nullptr;
    sigc::connection poll_conn;
    bool updating = false;

    bool poll();
    void change_button_label (Gtk::ToggleButton*, double volume);
};

}
