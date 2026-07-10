#pragma once
#include <gtkmm.h>
#include <giomm.h>

namespace bar::modules {
    class Battery : public Gtk::Box {
        private:
        Glib::RefPtr<Gio::DBus::Proxy> proxy;
        Gtk::Label* label;

        void refresh();
        public:
        Battery();
        ~Battery() override = default;
    };
}
