#include "gui/MainWindow.hpp"
#include <FL/Fl.H>
#include <memory>

int main(int argc, char *argv[]) {
    // Set dark mode by default
    Fl::scheme("gtk+");
    Fl::background(30, 30, 30);
    Fl::background2(45, 45, 45);
    Fl::foreground(200, 200, 200);

    // Create and show main window
    auto window = std::make_unique<MainWindow>();
    window->show();

    // Start FLTK event loop
    return Fl::run();
}