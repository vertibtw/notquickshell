#pragma once
#include "workspace.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

namespace hyprland {
    class Ipc {
        private:
        std::string his = "";
        std::string runtimedir = "";
        public:
        std::string socket1(std::string);
        [[nodiscard]] std::vector<Workspace> get_initial_workspaces ();
        Ipc ();
        ~Ipc() = default;
    };
}