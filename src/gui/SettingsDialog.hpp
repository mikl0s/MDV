#pragma once

#include <wx/wx.h>
#include <wx/dialog.h>
#include "FontManager.hpp"

class SettingsDialog : public wxDialog {
public:
    SettingsDialog(wxWindow* parent);

private:
    // UI Elements
    wxButton* m_installFontButton;
    wxButton* m_selectFontButton;
    wxCheckBox* m_reopenLastFile;
    wxCheckBox* m_useDarkTheme;

    // Font management
    FontManager& m_fontManager;

    // Event handlers
    void OnInstallFont(wxCommandEvent& event);
    void OnSelectFont(wxCommandEvent& event);
    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    // Helper functions
    void CreateControls();
    void LoadSettings();
    void SaveSettings();

    enum {
        ID_INSTALL_FONT = wxID_HIGHEST + 1,
        ID_SELECT_FONT
    };

    wxDECLARE_EVENT_TABLE();
};