#include "bar.hpp"
#include <gtkmm/object.h>

namespace widgets {
    Bar::Bar (std::shared_ptr<ini> conf) {
        if (!(*conf).contains("bar")) {
            std::cerr << "ERROR: config does not contain a bar section, bar will not be created.\n";
            return;
        }
        this->set_title("v.shell.bar");
        this->set_default_size(67, 69);
        gtk_layer_init_for_window(this->gobj());

        this->ipc = std::make_shared<hyprland::Ipc>();

        gtk_layer_auto_exclusive_zone_enable(this->gobj());

        /*
        **********************************
        *             CSS                *
        ********************************** 
        */

        this->add_css_class("bar");

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
            this->horizontal = true;
        } else if ((*conf)["bar"]["position"] == "bottom") {
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, false);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
            this->horizontal = true;
        } else if ((*conf)["bar"]["position"] == "left") {
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, false);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
            this->vertical = true;
        } else if ((*conf)["bar"]["position"] == "right") {
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_LEFT, false);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_RIGHT, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_TOP, true);
            gtk_layer_set_anchor(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, true);
            this->vertical = true;
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
            gtk_layer_set_margin(this->gobj(), GTK_LAYER_SHELL_EDGE_BOTTOM, std::stoi((*conf)["bar"]["margin-bottom"]));
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

    
         /*
        **********************************
        *           MODULES              *
        ********************************** 
        */ 

        auto main_box = Gtk::make_managed<Gtk::CenterBox>();
        main_box->set_expand(true);
        this->set_child(*main_box);

        auto l_box = Gtk::make_managed<Gtk::Box>();
        auto c_box = Gtk::make_managed<Gtk::Box>();
        auto r_box = Gtk::make_managed<Gtk::Box>();
        
        if ((*conf).contains("bar", "spacing")) {
            int spacing = std::stoi((*conf)["bar"]["spacing"]);
            l_box->set_spacing(spacing);
            c_box->set_spacing(spacing);
            r_box->set_spacing(spacing);
        }

        // popups
        auto vol_window = Gtk::make_managed<VolumeWindow>();
        
        // actual bar layout
        l_box->add_css_class("left-box");
        c_box->add_css_class("center-box");
        r_box->add_css_class("right-box");

        main_box->set_start_widget(*l_box);
        main_box->set_center_widget(*c_box);
        main_box->set_end_widget(*r_box);

        auto mod_workspaces = Gtk::make_managed<bar::modules::Workspaces>(this->ipc);
        auto mod_clock = Gtk::make_managed<bar::modules::Clock>();        
        auto mod_vol_btn = Gtk::make_managed<VolumeButton>(vol_window);


        c_box->append(*mod_workspaces);
        r_box->append(*mod_clock);
        r_box->append(*mod_vol_btn);

        // lambdas :<
        ipc->on_event = [this, mod_workspaces] (std::string event, std::string arg) -> void {
            Glib::signal_idle().connect_once([this, mod_workspaces, event, arg]()-> void {
                if (event == "workspace") {
                    int ws_id = std::stoi(arg); // this has to be here and repeated, because some args are not numerical
                    mod_workspaces->change_active_ws(ws_id);
                  } else if (event == "createworkspace") {
                    int ws_id = std::stoi(arg);
                    mod_workspaces->create_ws(ws_id);
                  } else if (event == "destroyworkspace") {
                    int ws_id = std::stoi(arg);
                    mod_workspaces->destroy_ws(ws_id);
                  } else {
                    // std::cout << "ommited event: " << event << " >> " << arg << "\n";
                  }
            });
        };
    }
}
