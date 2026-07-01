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
        void dispatch (std::string, std::string);
        std::string socket1(std::string);
        void socket2 ();
        [[nodiscard]] std::vector<Workspace> get_initial_workspaces ();
        Ipc ();
        ~Ipc() = default;
    };
}