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
}
