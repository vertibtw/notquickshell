#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <gtkmm.h>

#include "ini/ini.hpp"
#include "bar/bar.hpp"

int main (int argc, char** argv) {
    std::stringstream ss;
    std::ifstream f ("example.ini");
    if (!f.is_open()) {
        std::cout << "ERROR: couldn't open config file\n";
        return EXIT_FAILURE;
    }
    ss << f.rdbuf();

    std::string content = ss.str();
    std::shared_ptr<ini> conf = std::make_shared<ini>(ini::parse(content));

    auto app = Gtk::Application::create("v.shell.app");

    auto bar = Gtk::make_managed<widgets::Bar>(conf);

    app->signal_activate().connect([&]() -> void {
        bar->present();
    });
    
    app->signal_startup().connect([&]() -> void {
        app->add_window(*bar);
    });

    return app->run(argc, argv);
}
