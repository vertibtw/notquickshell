#pragma once
#include <iostream>
#include <fstream>
#include <gtkmm.h>

namespace bar::modules {
    class Battery : public Gtk::Box {
        private:
        Gtk::Label* st_icon;
        Gtk::Label* percentage;
        public:
        Battery();
        ~Battery() = default;
    };
}
