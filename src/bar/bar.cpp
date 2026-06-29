#include "bar.hpp"
#include "../util/is_int.hpp"
#include "../ipc/hyprland/ipc.hpp"
#include <gtk/gtk.h>
#include <gtk4-layer-shell.h>
#include <string>

namespace widgets {
    Bar::Bar (std::shared_ptr<ini> conf) {
        if (!(*conf).contains("bar")) {
            std::cerr << "ERROR: config does not contain a bar section, bar cannot be created.\n";
            return;
        }
        this->set_title("v.shell.bar");
        this->set_default_size(200, 200);
        gtk_layer_init_for_window(this->gobj());

        bool vertical, horizontal = false;

        /*
        **********************************
        *          POSITION              *
        ********************************** 
        */

        // TODO: find a cleaner way to do this maybe
        if (!(*conf).contains("bar", "position")) {
            std::cerr << "WARN: no bar position or an invalid one provided, using default (top)\n";
            goto top; // uh yes
        } else if ((*conf)["bar"]["position"] == "top") {
            top:
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, false);
            horizontal = true;
        } else if ((*conf)["bar"]["position"] == "bottom") {
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, false);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
            horizontal = true;
        } else if ((*conf)["bar"]["position"] == "left") {
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, false);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
            vertical = true;
        } else if ((*conf)["bar"]["position"] == "right") {
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, false);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
            vertical = true;
        }
        /*
        **********************************
        *           MARGINS              *
        ********************************** 
        */

        #define ASSERT_INT(conf_val) \
        if (!util::is_number(conf_val)) { \
            std::cerr << "ERROR: margin values have to be integers.\n"; \
            std::exit(1); \
        }

        if ((*conf).contains("bar", "margin-left")) {
            ASSERT_INT((*conf)["bar"]["margin-left"]);
            gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, std::stoi((*conf)["bar"]["margin-left"]));
        }
        if ((*conf).contains("bar", "margin-right")) {
            ASSERT_INT((*conf)["bar"]["margin-right"]);
            gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, std::stoi((*conf)["bar"]["margin-right"]));
        }
        if ((*conf).contains("bar", "margin-top")) {
            ASSERT_INT((*conf)["bar"]["margin-top"]);
            gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, std::stoi((*conf)["bar"]["margin-top"]));
        }
        
        if ((*conf).contains("bar", "margin-bottom")) {
            ASSERT_INT((*conf)["bar"]["margin-bottom"]);
            gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, std::stoi((*conf)["bar"]["margin-bottom"]));
        }
        
        /*
        **********************************
        *         THICKNESS              *
        ********************************** 
        */ 
        
        if ((*conf).contains("bar", "thickness")) {
            ASSERT_INT((*conf)["bar"]["thickness"]);
            int value = std::stoi((*conf)["bar"]["thickness"]);
            gtk_window_set_default_size(this->gobj(), vertical ? value : 0, horizontal ? value : 0);
        }
        #undef ASSERT_INT

        hyprland::Ipc i;
        i.get_initial_workspaces();
        
    }
}