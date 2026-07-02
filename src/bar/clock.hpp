#pragma  once
#include <gtkmm.h>
#include <glibmm.h>
#include <sstream>
#include <ctime>
#include <format>

namespace bar {
    namespace modules {
        class Clock : public Gtk::Box {
            private:
            Gtk::Label* l = Gtk::make_managed<Gtk::Label>();
            bool update();
            public:
            Clock();
            ~Clock() = default;
        };
    }
}