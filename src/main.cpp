#include "MainWindow.hpp"
#include <wx/wx.h>

namespace mdv {

class MDVApp : public wxApp {
public:
    virtual bool OnInit() {
        if (!wxApp::OnInit())
            return false;

        MainWindow* window = new MainWindow();
        window->Show(true);
        return true;
    }
};

} // namespace mdv

wxIMPLEMENT_APP(mdv::MDVApp);