#pragma once
#include <fstream>
#include <gtkmm.h>
#include <iostream>

namespace bar::modules {
class Battery : public Gtk::Box {
    private:
    Gtk::Label *st_icon;
    Gtk::Label *percentage;

    public:
    Battery();
    ~Battery() = default;
};
} // namespace bar::modules
