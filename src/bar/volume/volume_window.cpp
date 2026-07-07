#include "volume_window.hpp"
// TODO: fix volume muting on first open for some reason
// I will not be fixing this probably

bool VolumeWindow::poll_vol () {
    int current = get_vol();

    if (current != this->VOLUME) {
        this->VOLUME = current;
        this->s->set_value(current);
    }

    return true;
}

void VolumeWindow::watch_vol () {
    poll_vol(); // no delay speed speed vroom vroom

    this->poll_conn = Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &VolumeWindow::poll_vol),
        500 
    );
}

int VolumeWindow::get_vol () {
    std::string output;
    try {
        Glib::spawn_command_line_sync("wpctl get-volume @DEFAULT_AUDIO_SINK@", &output);
    } catch (const Glib::Error& e) {
        return -1;
    }

    std::smatch m;
    if (std::regex_search(output, m, std::regex(R"(Volume:\s*([\d.]+))"))) {
        double fraction = std::stod(m[1]);
        return static_cast<int>(std::round(fraction * 100));
    }

    return -1;
}

bool VolumeWindow::is_muted() {
    std::string output;
    try {
        Glib::spawn_command_line_sync("wpctl get-volume @DEFAULT_AUDIO_SINK@", &output);
    } catch (const Glib::Error& e) {
        return false;
    }

    return output.find("MUTED") != std::string::npos;
}

VolumeWindow::VolumeWindow () {
    // TODO: orientation based on bar position (this is todo like everywhere but whatever)
    auto scale = Gtk::make_managed <Gtk::Scale>(Gtk::Orientation::HORIZONTAL);
    scale->set_range(0.0, 100.0);
    scale->set_value(1);
    scale->set_digits(0);
    scale->set_draw_value(false);
    scale->set_digits(0);
    scale->set_round_digits(0);
    scale->set_increments(1.0, 10.0);

    scale->signal_value_changed().connect([scale]() {
        int val = static_cast<int>(std::round(scale->get_value()));
        std::string cmd = "wpctl set-volume @DEFAULT_AUDIO_SINK@ " + std::to_string(val) + "%";
        Glib::spawn_command_line_async(cmd);
    });

    this->s = scale;
    this->set_child(*scale);
    this->add_css_class("volume_window");


    this->signal_show().connect(sigc::mem_fun(*this, &VolumeWindow::watch_vol));
    this->signal_hide().connect([this]() {
        this->poll_conn.disconnect();
    });
}
