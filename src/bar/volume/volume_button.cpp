#include "volume_button.hpp"
#include "../wireplumber.hpp"

namespace bar::modules {
VolumeButton::VolumeButton(Gtk::Popover *popover) {
    this->set_popover(*popover);
    this->set_child(*this->label);
    this->set_has_frame(false);
    this->set_always_show_arrow(false);
    this->add_css_class("volume_button");

    poll();
    poll_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &VolumeButton::poll), 500);
}

void VolumeButton::update_label(double volume, bool muted) {
    if (muted)
        this->label->set_text("󰖁");
    else if (volume <= 0)
        this->label->set_text("󰝟");
    else if (volume <= 33)
        this->label->set_text("󰕿");
    else if (volume <= 66)
        this->label->set_text("󰖀");
    else if (volume <= 100)
        this->label->set_text("󰕾");
}

bool VolumeButton::poll() {
    update_label(wp::wpctl_get_volume() * 100.0, wp::wpctl_get_muted());
    return true;
}
} // namespace bar::modules
