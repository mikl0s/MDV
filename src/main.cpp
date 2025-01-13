#include "gui/MainWindow.hpp"
#include <wx/wx.h>

// Implement the wxWidgets application
class MDVApp : public wxApp {
public:
    virtual bool OnInit() {
        // Create and show the main window
        mdv::MainWindow* window = new mdv::MainWindow();
        window->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MDVApp);