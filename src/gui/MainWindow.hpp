#ifndef MDV_MAIN_WINDOW_HPP
#define MDV_MAIN_WINDOW_HPP

#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <memory>

namespace mdv {

class MainWindow {
public:
    MainWindow(int width = 800, int height = 600);
    ~MainWindow() = default;

    void show();
    void hide();
    bool visible() const;

private:
    std::unique_ptr<Fl_Window> window_;
    std::unique_ptr<Fl_Text_Display> display_;
};

} // namespace mdv

#endif // MDV_MAIN_WINDOW_HPP