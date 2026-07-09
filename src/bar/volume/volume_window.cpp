#include "volume_window.hpp"
#include "../wireplumber.hpp"
namespace bar::modules {

VolumeWindow::VolumeWindow() {
    // TODO: don't accentally forget that this is always supposed to be horizontal when u finally get to the part where you make the vertical bar work
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 4);
    vbox->set_margin(4);

    slider = Gtk::make_managed<Gtk::Scale>(Gtk::Adjustment::create(50.0, 0.0, 100.0, 1.0, 10.0, 0.0));
    slider->set_digits(0);
    slider->set_draw_value(false);
    slider->set_size_request(140, -1);

    mute_btn = Gtk::make_managed<Gtk::ToggleButton>("Mute");
    
    vbox->append(*slider);
    vbox->append(*mute_btn);
    set_child(*vbox);

    slider->signal_value_changed().connect([this]() {
        if (!updating) {
            wp::wpctl_set_volume(slider->get_value());
            this->change_button_label(this->mute_btn, slider->get_value());
        }
    });

    mute_btn->signal_toggled().connect([this]() {
        if (!updating) {
            wp::wpctl_set_muted(mute_btn->get_active());
            this->change_button_label(this->mute_btn, slider->get_value());
        }
    });

    signal_show().connect([this]() {
        if (!poll_conn.connected()) {
            poll_conn = Glib::signal_timeout().connect(
                sigc::mem_fun(*this, &VolumeWindow::poll), 500);
        }
        // initial poll
        Glib::signal_idle().connect_once([this]() { poll(); });
    });

    signal_hide().connect([this]() {
        poll_conn.disconnect();
    });

    this->add_css_class("volume_window");
}

bool VolumeWindow::poll() {
    this->updating = true;
    slider->set_value(wp::wpctl_get_volume() * 100.0);
    mute_btn->set_active(wp::wpctl_get_muted());
    updating = false;
    return true;
}

double VolumeWindow::get_volume() const {
    return slider->get_value();
}

bool VolumeWindow::get_muted() const {
    return mute_btn->get_active();
}

void VolumeWindow::change_button_label (Gtk::ToggleButton* btn, double volume) {
    if      (volume <= 0)   btn->set_label("muted"); 
    else if (volume <= 33)  btn->set_label("small sound");
    else if (volume <= 66)  btn->set_label("medium sound");
    else if (volume <= 100) btn->set_label("big sound");
}

}
