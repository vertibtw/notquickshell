// I wanted to do this with <wp/wp.h> but I am too skill issued to do so, for now at least.
#include "wireplumber.hpp"
#include <charconv>
#include <glibmm.h>

namespace wp {

double wpctl_get_volume() {
    std::string out;
    try {
        Glib::spawn_command_line_sync("wpctl get-volume @DEFAULT_AUDIO_SINK@", &out);
    } catch (const Glib::Error &e) {
        return 0.0;
    }
    size_t pos = out.find("Volume:");
    if (pos == std::string::npos)
        return 0.0;
    pos += 7;
    while (pos < out.size() && (out[pos] == ' ' || out[pos] == '\t'))
        pos++;
    double val;
    auto r = std::from_chars(out.data() + pos, out.data() + out.size(), val);
    if (r.ec == std::errc{})
        return val;
    return 0.0;
}

bool wpctl_get_muted() {
    std::string out;
    try {
        Glib::spawn_command_line_sync("wpctl get-volume @DEFAULT_AUDIO_SINK@", &out);
    } catch (const Glib::Error &e) {
        return false;
    }
    return out.find("MUTED") != std::string::npos;
}

void wpctl_set_volume(int pct) {
    Glib::spawn_command_line_async("wpctl set-volume @DEFAULT_AUDIO_SINK@ " + std::to_string(pct) + "%");
}

void wpctl_set_muted(bool mute) {
    Glib::spawn_command_line_async(mute ? "wpctl set-mute @DEFAULT_AUDIO_SINK@ 1"
                                        : "wpctl set-mute @DEFAULT_AUDIO_SINK@ 0");
}

} // namespace wp
