#pragma once
// #include "../../bar/bar.hpp"
#include "../../bar/workspace.hpp"
#include "../../util/extern/json.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <gtkmm/object.h>
#include <iostream>
#include <memory>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <thread>
#include <unistd.h>
#include <vector>

namespace hyprland {
    class Ipc {
        private:
        std::string his = "";
        std::string runtimedir = "";
        // std::shared_ptr<widgets::Bar> bar;

        public:
        std::function<void(std::string, std::string)> on_event; // my greatest idea yet I feel so c++

        [[nodiscard]] std::string                     socket1(std::string);
        void                                          socket2 ();
        // TODO: move this out of here
        [[nodiscard]] std::vector<hyprland::Workspace*> get_initial_workspaces ();

        Ipc ();
        ~Ipc() = default;
    };
}