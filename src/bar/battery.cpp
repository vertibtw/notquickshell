#include "battery.hpp"

namespace bar::modules {
    Battery::Battery () {
        this->add_css_class("battery");
        this->label = Gtk::make_managed<Gtk::Label>();
        this->append(*this->label);

        Gio::init();
        this->proxy = Gio::DBus::Proxy::create_for_bus_sync(
            Gio::DBus::BusType::SYSTEM,
            "org.freedesktop.UPower",
            "/org/freedesktop/UPower/devices/battery_BAT0",
            "org.freedesktop.UPower.Device");

        this->proxy->signal_properties_changed().connect(
            [this](const std::map<Glib::ustring, Glib::VariantBase>&, const std::vector<Glib::ustring>&) {
                this->refresh();
            });

        this->refresh();
    }

    void Battery::refresh () {
        Glib::VariantBase pct, state;
        this->proxy->get_cached_property(pct, "Percentage");
        this->proxy->get_cached_property(state, "State");

        if (!pct.gobj()) return;

        int percent = (int)Glib::VariantBase::cast_dynamic<Glib::Variant<double>>(pct).get();
        bool charging = state.gobj() ? Glib::VariantBase::cast_dynamic<Glib::Variant<guint32>>(state).get() == 1 : false;

        std::string text = std::to_string(percent) + "%";
        if (charging) text += " [\uf431]";

        this->label->set_text(text);
    }
}
