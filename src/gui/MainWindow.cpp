#include "MainWindow.hpp"
#include <FL/Fl.H>

namespace mdv {

MainWindow::MainWindow(int width, int height) {
    // Create main window
    window_ = std::make_unique<Fl_Window>(width, height, "MDV - Markdown Viewer");
    
    // Create text display widget that fills the window
    display_ = std::make_unique<Fl_Text_Display>(0, 0, width, height);
    display_->box(FL_FLAT_BOX);
    display_->textfont(FL_COURIER);
    
    window_->end();
    window_->resizable(display_.get());
}

void MainWindow::show() {
    window_->show();
    while (window_->shown()) {
        Fl::wait();
    }
}

void MainWindow::hide() {
    window_->hide();
}

bool MainWindow::visible() const {
    return window_->visible() != 0;
}

} // namespace mdv