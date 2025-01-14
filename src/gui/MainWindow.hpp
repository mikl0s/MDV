#pragma once

#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <memory>
#include "FontManager.hpp"

namespace mdv {
    class MarkdownRenderer;

class MainWindow : public wxFrame {
public:
    MainWindow();

    // Methods used by MarkdownRenderer
    void ClearContent();
    void AppendText(const wxString& text);
    wxRichTextCtrl* GetTextCtrl() { return m_textCtrl; }
    bool IsWindowsDarkMode();

    // Theme colors
    wxColour GetAccentColor() const { return m_accentColor; }
    void SetAccentColor(const wxColour& color);

private:
    // Menu creation
    void CreateMenuBar();
    void CreateFileMenu(wxMenuBar* menuBar);
    void CreateSettingsMenu(wxMenuBar* menuBar);
    void CreateHelpMenu(wxMenuBar* menuBar);

    // Event handlers
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnThemeChange(wxCommandEvent& event);
    void OnFontSelect(wxCommandEvent& event);
    void OnInstallFiraMonoFont(wxCommandEvent& event);
    void OnPreferences(wxCommandEvent& event);
    void OnSystemColorChange(wxSysColourChangedEvent& event);
    void OnOpen(wxCommandEvent& event);

    // Theme management
    void ApplyTheme(bool isDark);
    void LoadThemeSettings();
    void SaveThemeSettings();

    // Font management
    void LoadFontSettings();
    void SaveFontSettings();

    // File management
    void OpenFile(const wxString& path);
    wxString LoadFileContent(const wxString& path);

    // Menu items
    wxMenuItem* m_darkThemeItem;
    wxMenuItem* m_lightThemeItem;

    // Font management
    FontManager& m_fontManager;

    // Markdown rendering
    std::unique_ptr<MarkdownRenderer> m_markdownRenderer;

    // UI elements
    wxRichTextCtrl* m_textCtrl;

    // Theme colors
    wxColour m_accentColor;

    enum {
        ID_DARK_THEME = wxID_HIGHEST + 1,
        ID_LIGHT_THEME,
        ID_FONT_SELECT,
        ID_INSTALL_FIRAMONO,
        ID_PREFERENCES
    };

    friend class MarkdownRenderer;
    wxDECLARE_EVENT_TABLE();
};

} // namespace mdv