#include "wallpaper_selector.hpp"

WallpaperSelector::WallpaperSelector(std::string wallpaper_dir)
    : dir(wallpaper_dir) {
    this->get_wallpapers();
}

void WallpaperSelector::get_wallpapers() {
    for (const auto &f : std::filesystem::directory_iterator(this->dir)) {
        if (f.is_regular_file()) {
            this->wallpapers.push_back(f.path().string());
        }
    }
}
