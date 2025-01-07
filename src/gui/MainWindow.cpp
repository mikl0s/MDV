#include "MainWindow.hpp"
#include <FL/Fl_Menu_Item.H>
#include <FL/fl_ask.H>

namespace {
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    constexpr int MENU_HEIGHT = 25;
}

MainWindow::MainWindow() {
    // Create main window
    window_ = std::make_unique<Fl_Window>(WINDOW_WIDTH, WINDOW_HEIGHT, "MDV - Markdown Viewer");
    
    // Create menu bar
    menu_bar_ = new Fl_Menu_Bar(0, 0, WINDOW_WIDTH, MENU_HEIGHT);
    setup_menu();

    window_->end();
}

void MainWindow::show() {
    window_->show();
}

void MainWindow::menu_cb(Fl_Widget*, void* v) {
    MainWindow* window = static_cast<MainWindow*>(v);
    const char* label = window->menu_bar_->mvalue()->label();
    window->handle_menu(label);
}

bool MainWindow::handle_menu(const char* label) {
    if (strcmp(label, "About") == 0) {
        fl_message("MDV - Markdown Viewer\nVersion 0.1.0");
        return true;
    }
    else if (strcmp(label, "Exit") == 0) {
        window_->hide();
        return true;
    }
    return false;
}

void MainWindow::setup_menu() {
    menu_bar_->add("&File/&Open...", FL_COMMAND+'o', menu_cb, this);
    menu_bar_->add("&File/&Export to PDF...", FL_COMMAND+'e', menu_cb, this);
    menu_bar_->add("File/Exit", FL_COMMAND+'q', menu_cb, this);
    
    menu_bar_->add("&Settings/&Theme/Dark", 0, menu_cb, this);
    menu_bar_->add("&Settings/&Theme/Light", 0, menu_cb, this);
    menu_bar_->add("&Settings/&Font", 0, menu_cb, this);
    menu_bar_->add("&Settings/&Preferences...", 0, menu_cb, this);
    
    menu_bar_->add("&Help/&About", 0, menu_cb, this);
}