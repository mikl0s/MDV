#include "SettingsDialog.hpp"
#include <wx/statline.h>
#include <wx/config.h>

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
    EVT_BUTTON(ID_INSTALL_FONT, SettingsDialog::OnInstallFont)
    EVT_BUTTON(ID_SELECT_FONT, SettingsDialog::OnSelectFont)
    EVT_BUTTON(wxID_OK, SettingsDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Settings", wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
    , m_fontManager(FontManager::Get())
{
    CreateControls();
    LoadSettings();
    
    // Set minimum size
    SetMinSize(wxSize(400, 300));
    
    // Center on parent
    CenterOnParent();
}

void SettingsDialog::CreateControls() {
    // Create main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);
    
    // Add font section
    wxStaticBoxSizer* fontSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Font Settings");
    
    // Font buttons
    m_installFontButton = new wxButton(this, ID_INSTALL_FONT, "Install FiraMono Font");
    m_selectFontButton = new wxButton(this, ID_SELECT_FONT, "Select Font...");
    
    fontSizer->Add(m_installFontButton, 0, wxALL | wxEXPAND, 5);
    fontSizer->Add(m_selectFontButton, 0, wxALL | wxEXPAND, 5);
    
    mainSizer->Add(fontSizer, 0, wxALL | wxEXPAND, 5);
    
    // Add general settings section
    wxStaticBoxSizer* generalSizer = new wxStaticBoxSizer(wxVERTICAL, this, "General Settings");
    
    m_reopenLastFile = new wxCheckBox(this, wxID_ANY, "Reopen last file on startup");
    m_useDarkTheme = new wxCheckBox(this, wxID_ANY, "Use dark theme");
    
    generalSizer->Add(m_reopenLastFile, 0, wxALL, 5);
    generalSizer->Add(m_useDarkTheme, 0, wxALL, 5);
    
    mainSizer->Add(generalSizer, 0, wxALL | wxEXPAND, 5);
    
    // Add separator line
    mainSizer->Add(new wxStaticLine(this), 0, wxEXPAND | wxALL, 5);
    
    // Add standard buttons
    wxStdDialogButtonSizer* buttonSizer = new wxStdDialogButtonSizer();
    buttonSizer->AddButton(new wxButton(this, wxID_OK));
    buttonSizer->AddButton(new wxButton(this, wxID_CANCEL));
    buttonSizer->Realize();
    
    mainSizer->Add(buttonSizer, 0, wxALL | wxEXPAND, 5);
    
    // Update font button state
    m_installFontButton->Enable(!m_fontManager.IsFiraMonoInstalled());
}

void SettingsDialog::LoadSettings() {
    wxConfig config("MDV");
    
    bool reopenLast = false;
    config.Read("ReopenLastFile", &reopenLast);
    m_reopenLastFile->SetValue(reopenLast);
    
    bool useDark = false;
    config.Read("UseDarkTheme", &useDark);
    m_useDarkTheme->SetValue(useDark);
}

void SettingsDialog::SaveSettings() {
    wxConfig config("MDV");
    
    config.Write("ReopenLastFile", m_reopenLastFile->GetValue());
    config.Write("UseDarkTheme", m_useDarkTheme->GetValue());
    
    config.Flush();
}

void SettingsDialog::OnInstallFont(wxCommandEvent& event) {
    if (m_fontManager.InstallFiraMonoNerdFont()) {
        wxMessageBox("FiraMono Nerd Font was successfully installed.",
                    "Font Installation",
                    wxICON_INFORMATION);
        
        // Disable the install button since font is now installed
        m_installFontButton->Enable(false);
    }
}

void SettingsDialog::OnSelectFont(wxCommandEvent& event) {
    wxFont currentFont = GetFont();
    if (m_fontManager.ShowFontDialog(this, currentFont)) {
        // Save the selected font in config
        wxConfig config("MDV");
        config.Write("FontFamily", currentFont.GetFaceName());
        config.Write("FontSize", currentFont.GetPointSize());
        config.Flush();
    }
}

void SettingsDialog::OnOK(wxCommandEvent& event) {
    SaveSettings();
    EndModal(wxID_OK);
}

void SettingsDialog::OnCancel(wxCommandEvent& event) {
    EndModal(wxID_CANCEL);
}