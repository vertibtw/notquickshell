#include "ipc.hpp"
#include "../../util/extern/json.hpp"
#include <sys/socket.h>
#include <vector>

namespace hyprland {
    Ipc::Ipc () {
        this->his        = std::getenv("HYPRLAND_INSTANCE_SIGNATURE");
        this->runtimedir = std::getenv("XDG_RUNTIME_DIR");
    }

    std::string Ipc::socket1 (std::string cmd) {
        std::string socket_path = this->runtimedir + "/hypr/" + this->his + "/.socket.sock";

        int s = socket(AF_UNIX, SOCK_STREAM, 0);
        if (s < 0) {
            std::cerr << "ERROR: couldn't connect to hyprland's ipc.\n";
            std::exit(1);
        }
        
        struct sockaddr_un addr;
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, socket_path.c_str());
        
        if (connect(s, (sockaddr*)&addr, sizeof(addr)) < 0) {
            std::cerr << "ERROR: couldn't connect to hyprland's ipc.\n";
            std::exit(2);
        }
        
        send(s, cmd.c_str(), cmd.size(), 0);

        char buffer [4096]; // probably doesn't have to be larger idk
        ssize_t received;
        std::string response; 

        while ((received = recv(s, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[received] = '\0';
            response.append(buffer, received); 
            std::cout << buffer << "\n";
        }
        if (received < 0) {
            std::cerr << "ERROR: recv failed: " << strerror(errno) << "\n";
        }
        close(s);
        return response;
    }

    std::vector<Workspace> Ipc::get_initial_workspaces () {
        std::string raw_ws = socket1("j/workspaces");
        std::string raw_active_ws = socket1("j/activeworkspace");

        nlohmann::json j_ws   = nlohmann::json::parse(raw_ws);
        nlohmann::json j_a_ws = nlohmann::json::parse(raw_active_ws);

        int active_ws_id = -1;
        if (j_a_ws.contains("id")) {
            active_ws_id = j_a_ws["id"].get<int>();
        }

        // TODO: check if the output is good
        for (const auto& obj : j_ws) {
            Workspace w;
            if (obj.contains("id")) {
                w.id = obj["id"].get<int>();
                std::cout << "workspace: " << w.id << "\n";
            } else {
                std::cerr << "workspace doesn't have an id for some reason\n";
                w.id = -67;
            }

            if (w.id == active_ws_id) {
                w.active = true;
                std::cout << w.id << " is currently active!!\n";
            }
        }

        return {};
    }
}