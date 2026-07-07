#include "volume_button.hpp"

VolumeButton::VolumeButton (VolumeWindow* popover) {
    this->set_popover(*popover);
    this->set_label(this->label);
    this->set_has_frame(false);
    this->set_always_show_arrow(false);


    this->add_css_class("volume_button");
}
