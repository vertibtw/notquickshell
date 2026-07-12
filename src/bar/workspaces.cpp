#include "workspaces.hpp"

void bar::modules::Workspaces::change_active_ws(int ws_id) {
    for (auto workspace : this->workspaces) {
        if (workspace->id == ws_id) {
            workspace->active = true;
            workspace->add_css_class("active");
        } else {
            workspace->active = false;
            workspace->remove_css_class("active");
        }
    }
}

void bar::modules::Workspaces::destroy_ws(int ws_id) {
    for (auto workspace : this->workspaces) {
        if (workspace->id == ws_id) {
            workspace->exists = false;
            workspace->add_css_class("empty");
            workspace->remove_css_class("active");
            workspace->remove_css_class("occupied");
        }
    }
}

void bar::modules::Workspaces::create_ws(int ws_id) {
    for (auto workspace : this->workspaces) {
        if (workspace->id == ws_id) {
            workspace->exists = true;
            workspace->add_css_class("occupied");
        }
    }
}

bar::modules::Workspaces::Workspaces(std::shared_ptr<hyprland::Ipc> Ipc)
    : ipc(Ipc) {
    this->workspaces = this->ipc->get_initial_workspaces();
    this->set_orientation(Gtk::Orientation::HORIZONTAL);
    this->set_spacing(6);
    this->set_valign(Gtk::Align::CENTER); // this fixes sizing issues (will be set_halign for a vertical bar)

    for (const auto &workspace : this->workspaces) {
        // auto l = Gtk::make_managed<Gtk::Label>(std::to_string(workspace->id));
        // workspace->append(*l);
        this->append(*workspace);
    }
}
