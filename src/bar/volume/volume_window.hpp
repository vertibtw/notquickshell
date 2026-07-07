#pragma once
#include <gtkmm.h>
#include <regex>
#include <cmath>
#include <glibmm.h>

class VolumeWindow : public Gtk::Popover {
    private:
    int VOLUME = -1; // last known
    sigc::connection poll_conn;
    Gtk::Scale* s; 

    int get_vol (); 
    bool is_muted();
    void watch_vol();
    bool poll_vol();

    public:
    VolumeWindow();
    ~VolumeWindow() = default;
};
