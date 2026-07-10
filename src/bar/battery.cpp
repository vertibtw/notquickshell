#include "battery.hpp"

namespace bar{
    namespace modules {
        Battery::Battery () {
            this->add_css_class("battery");
            this->st_icon    = Gtk::make_managed<Gtk::Label>();
            this->percentage = Gtk::make_managed<Gtk::Label>();

            this->append(*this->st_icon);
            this->append(*this->percentage);
            
            auto refresh = [this] () -> bool {
                int capacity = -1;

                std::ifstream fc ("/sys/class/power_supply/BAT0/capacity");
                std::ifstream fs ("/sys/class/power_supply/BAT0/status");
                if (!(fc >> capacity)) return false;
                this->percentage->set_text(std::to_string(capacity) + "%");

                
                std::string buffer = "";
                if (!std::getline(fs, buffer)) return false;
                if      (buffer == "Full")         this->st_icon->set_text("[f]");
                else if (buffer == "Discharging")  this->st_icon->set_text("[d]");
                else if (buffer == "Not charging") this->st_icon->set_text("[n]");
                else if (buffer == "Charging")     this->st_icon->set_text("[c]");
                else this->st_icon->set_text("[u]");

                return true;
            };

            Glib::signal_timeout().connect([=] () -> bool {
                return refresh();
            }, 200);
        }
}
}
