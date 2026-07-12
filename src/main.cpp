#include <cstdlib>
#include <fstream>
#include <gtkmm.h>
#include <iostream>
#include <memory>
#include <sstream>

#include "bar/bar.hpp"
#include "ini/ini.hpp"
#include "theme/theme.hpp"

int main(int argc, char **argv) {
    std::stringstream ss;

    std::string home_dir = std::getenv("HOME");

    if (home_dir.empty()) {
        std::cerr << "ERROR: $HOME environment variable not set.\n";
        std::exit(1);
    }

    std::string config_path;

    config_path = home_dir + "/.shell.ini"; // I don't wanna do configs in .config

    std::ifstream f(config_path);

    if (!f.is_open()) {
        std::cout << "ERROR: couldn't open config file '" << config_path << "'\n";
        return EXIT_FAILURE;
    }
    ss << f.rdbuf();

    std::string content = ss.str();
    std::shared_ptr<ini> conf = std::make_shared<ini>(ini::parse(content));

    auto css = Gtk::CssProvider::create();

    // TODO: get rid of this stupid fucking inline css
    std::string css_str =
        "* {"
        "font-family: 'Scientifica';"
        "font-size: 15px;"
        "font-weight: bold;"
        "}"
        ".bar {"
        "  background: var(--background_main);"
        "  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.4);"
        "}"
        ".left-box {"
        "  margin-left: 10px;"
        "}"
        ".right-box {"
        "  margin-right: 10px;"
        "}"
        ".workspace {"
        "  min-width: 20px;"
        "  min-height: 4px;"
        //    "  border-radius: 2px;"
        "  background: var(--background_light); margin: 0 2px;"
        "  transition: background 200ms ease, min-width 200ms ease, min-height 200ms ease;"
        "}"
        ".workspace.occupied { background: var(--foreground_secondary); }"
        ".workspace.active {"
        "  min-width: 28px;"
        "  min-height: 6px;"
        //    "  border-radius: 3px;"
        "  background: var(--purple);"
        "}"
        ".clock {"
        "  color: var(--foreground_main);"
        "}"
        ".volume_button button {"
        "  background: none;"
        "  box-shadow: none;"
        "  border: none;"
        "}"
        ".volume_window contents {"
        "  border-radius: 0;"
        "  background: var(--background_main);"
        "  min-width: 200px;"
        "}"
        ".volume_window arrow {"
        "  background: var(--background_main);"
        "  min-width: 12px;"
        "  min-height: 6px;"
        "}"
        ".volume_window scale trough {"
        "  border: none;"
        "  background: var(--foreground_secondary);"
        "  min-height: 6px;"
        "  border-radius: 0;"
        "}"
        ".volume_window scale highlight {"
        "  background: var(--blue);"
        "}"
        ".volume_window scale slider {"
        "  background: var(--foreground_main);"
        "  border-radius: 0;"
        "  border: none;"
        "}"
        ".volume_button label {"
        "  color: var(--foreground_main);"
        "}"
        ".volume_button arrow {" // idk it would not disable itself despite the set_always_show_arrow(false), gtk ig
        "  min-width: 0;"
        "  min-height: 0;"
        "  opacity: 0;"
        "}"
        ".window_title label {"
        "  color: var(--foreground_main);"
        "}"
        ".battery label {"
        "  color: var(--foreground_main);"
        "}"
        ".battery .low {"
        "  color: var(--orange);"
        "}"
        ".battery .full {"
        "  color: var(--foreground_main);"
        "}"
        ".battery .discharging {"
        "  color: var(--foreground_main);"
        "}"
        ".battery .not_charging {"
        "  color: var(--foreground_main);"
        "}"
        ".battery .charging {"
        "  color: var(--green);"
        "}"
        ".battery .unknown {"
        "  color: var(--purple);"
        "}";

    if (conf->contains("", "theme")) {
        if ((*conf)[""]["theme"] == "catppuccin mocha")
            css_str.insert(0, theme::catppuccin_mocha);
        else if ((*conf)[""]["theme"] == "catppuccin frappe")
            css_str.insert(0, theme::catppuccin_frappe);
        else if ((*conf)[""]["theme"] == "catppuccin latte")
            css_str.insert(0, theme::catppuccin_latte);
        else if ((*conf)[""]["theme"] == "catppuccin macchiato")
            css_str.insert(0, theme::catppuccin_macchiato);
        else {
            std::cerr << "ERROR: invalid theme name: '" << (*conf)[""]["theme"] << "'; using catppuccin mocha.\n";
            css_str.insert(0, theme::catppuccin_macchiato);
        }
    } else {
        std::cerr << "WARN: no theme provided, using catppuccin mocha.\n";
        css_str.insert(0, theme::catppuccin_macchiato);
    }

    auto app = Gtk::Application::create("v.shell.app");

    auto bar = Gtk::make_managed<widgets::Bar>(conf);

    app->signal_startup().connect([&]() -> void {
        css->load_from_data(css_str);
        Gtk::StyleContext::add_provider_for_display(Gdk::Display::get_default(), css,
                                                    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        app->add_window(*bar);
        app->signal_activate().connect([&]() -> void { bar->present(); });
    });

    return app->run(argc, argv);
}
