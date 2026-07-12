#pragma once
#include <gtkmm.h>

namespace bar::modules {
class VolumeButton : public Gtk::MenuButton {
    public:
    Gtk::Label *label = Gtk::make_managed<Gtk::Label>();
    VolumeButton(Gtk::Popover *);
    void update_label(double volume, bool muted);
    ~VolumeButton() = default;

    private:
    sigc::connection poll_conn;
    bool poll();
};
} // namespace bar::modules
