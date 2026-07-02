#pragma once

#include <gtkmm/box.h>
#include <memory>
#include <vector>
#include "workspace.hpp"

namespace hyprland { class Ipc; } // compiler complained about circular inclusion fuck c++

namespace bar {
    namespace modules {
        class Workspaces : public Gtk::Box {
            private:
            std::vector<hyprland::Workspace*> workspaces;
            std::shared_ptr<hyprland::Ipc> ipc;
            public:
            
            void change_active_ws (int);
            void destroy_ws (int); 
            void create_ws (int);

            Workspaces (std::shared_ptr<hyprland::Ipc>);
            ~Workspaces () = default;
        };
    }
}