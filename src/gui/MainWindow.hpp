#ifndef MDV_MAIN_WINDOW_HPP
#define MDV_MAIN_WINDOW_HPP

#include <wx/wx.h>
#include <wx/textctrl.h>

namespace mdv {

class MainWindow : public wxFrame {
public:
    MainWindow();

private:
    // Event handlers
    void OnOpen(wxCommandEvent& event);
    void OnExportPDF(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnThemeChange(wxCommandEvent& event);
    void OnFontSelect(wxCommandEvent& event);
    void OnPreferences(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    // Menu creation
    void CreateMenuBar();

    // Window components
    wxTextCtrl* display_;

    // Menu IDs
    enum {
        ID_Open = wxID_HIGHEST + 1,
        ID_ExportPDF,
        ID_ThemeDark,
        ID_ThemeLight,
        ID_FontSelect,
        ID_Preferences
    };

    wxDECLARE_EVENT_TABLE();
};

} // namespace mdv

#endif // MDV_MAIN_WINDOW_HPP