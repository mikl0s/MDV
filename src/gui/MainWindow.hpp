#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <memory>

class MainWindow {
public:
    MainWindow();
    ~MainWindow() = default;

    void show();
    bool handle_menu(const char* label);

private:
    static void menu_cb(Fl_Widget*, void* v);
    void setup_menu();
    
    std::unique_ptr<Fl_Window> window_;
    Fl_Menu_Bar* menu_bar_;
};