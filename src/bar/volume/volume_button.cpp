#include "volume_button.hpp"

namespace bar::modules {
    VolumeButton::VolumeButton (Gtk::Popover* popover) {
        this->set_popover(*popover);
        this->set_child(*this->label);
        this->set_has_frame(false);
        this->set_always_show_arrow(false);
        this->add_css_class("volume_button");
        this->label->set_text("volume");
    }

    void VolumeButton::update_label(double volume, bool muted) {
        if (muted)          this->label->set_text("󰖁");
        else if (volume <= 0)   this->label->set_text("󰝟");
        else if (volume <= 33)  this->label->set_text("󰕿");
        else if (volume <= 66)  this->label->set_text("󰖀");
        else if (volume <= 100) this->label->set_text("󰕾");
    }
}
