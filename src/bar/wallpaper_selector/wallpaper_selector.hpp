#pragma once
#include <filesystem>
#include <gtkmm.h>
#include <string>
#include <vector>

class WSButton;

class WallpaperSelector : public Gtk::Popover {
    public:
    WallpaperSelector(std::string);
    ~WallpaperSelector() = default;

    private:
    std::string dir;
    std::vector<std::string> wallpapers;
    void get_wallpapers();
};
