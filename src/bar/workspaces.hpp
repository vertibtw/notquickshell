#pragma once

#include "../ipc/hyprland/ipc.hpp"
#include "workspace.hpp"
#include <gtkmm/box.h>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/object.h>
#include <memory>
#include <string>
#include <vector>

namespace bar {
namespace modules {
class Workspaces : public Gtk::Box {
    private:
    std::vector<hyprland::Workspace *> workspaces;
    std::shared_ptr<hyprland::Ipc> ipc;

    public:
    void change_active_ws(int);
    void destroy_ws(int);
    void create_ws(int);

    Workspaces(std::shared_ptr<hyprland::Ipc>);
    ~Workspaces() = default;
};
} // namespace modules
} // namespace bar