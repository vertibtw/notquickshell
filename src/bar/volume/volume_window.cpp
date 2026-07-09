#include "volume_window.hpp"
#include "volume_button.hpp"
#include "../wireplumber.hpp"
namespace bar::modules {

VolumeWindow::VolumeWindow() {
    // TODO: don't accentally forget that this is always supposed to be horizontal when u finally get to the part where you make the vertical bar work
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 4);
    vbox->set_margin(4);

    this->slider = Gtk::make_managed<Gtk::Scale>(Gtk::Adjustment::create(50.0, 0.0, 100.0, 1.0, 10.0, 0.0));
    this->slider->set_digits(0);
    this->slider->set_draw_value(false);
    this->slider->set_size_request(140, -1);

    this->mute_btn = Gtk::make_managed<Gtk::ToggleButton>("Mute");
    
    vbox->append(*this->slider);
    vbox->append(*this->mute_btn);
    set_child(*vbox);

    slider->signal_value_changed().connect([this]() {
        if (!this->updating) {
            wp::wpctl_set_volume(this->slider->get_value());
            this->change_volume_button_label(this->slider->get_value());
        }
    });

    mute_btn->signal_toggled().connect([this]() {
        if (!updating) {
            wp::wpctl_set_muted(mute_btn->get_active());
            this->change_volume_button_label(this->slider->get_value());
        }
    });

    // doesn't update the volume when the popup is closed, updating the icon in the bar live is still TODO
    signal_show().connect([this]() {
        if (!this->poll_conn.connected()) {
            this->poll_conn = Glib::signal_timeout().connect(
                sigc::mem_fun(*this, &VolumeWindow::poll), 200); // probably fine to do every 200ms
        }

        // initial poll
        Glib::signal_idle().connect_once([this]() { 
            this->change_volume_button_label(wp::wpctl_get_volume());
            this->poll(); 
        });
    });

    signal_hide().connect([this]() {
        poll_conn.disconnect();
    });

    this->add_css_class("volume_window");
}

bool VolumeWindow::poll() {
    this->updating = true;
    double vol = wp::wpctl_get_volume() * 100.0;
    this->slider->set_value(vol);
    this->change_volume_button_label(vol);
    this->mute_btn->set_active(wp::wpctl_get_muted());
    this->updating = false;
    return true;
}

double VolumeWindow::get_volume() const {
    return this->slider->get_value();
}

bool VolumeWindow::get_muted() const {
    return this->mute_btn->get_active();
}

void VolumeWindow::change_volume_button_label (double volume) {
    if (this->get_muted())  this->mute_btn->set_label("󰖁");
    else if (volume <= 0)   this->mute_btn->set_label("󰝟"); 
    else if (volume <= 33)  this->mute_btn->set_label("󰕿");
    else if (volume <= 66)  this->mute_btn->set_label("󰖀");
    else if (volume <= 100) this->mute_btn->set_label("󰕾");

    if (this->volume_button)
        this->volume_button->update_label(volume, this->get_muted());
}

}
