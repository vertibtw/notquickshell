#pragma once

namespace wp {
    double wpctl_get_volume();
    bool wpctl_get_muted();
    void wpctl_set_volume(int pct);
    void wpctl_set_muted(bool mute);
}
