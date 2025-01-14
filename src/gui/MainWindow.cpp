#include "MainWindow.hpp"
#include "SettingsDialog.hpp"
#include "../markdown/MarkdownRenderer.hpp"
#include <wx/aboutdlg.h>
#include <wx/config.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/textfile.h>
#include <windows.h>
#include <dwmapi.h>
#include <uxtheme.h>

// Define the dark mode attribute if not available
#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

// GitHub-style dimensions
#define GITHUB_WINDOW_WIDTH 1012
#define GITHUB_CONTENT_WIDTH 980
#define GITHUB_MIN_HEIGHT 600

namespace mdv {

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_EXIT, MainWindow::OnExit)
    EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
    EVT_MENU(wxID_OPEN, MainWindow::OnOpen)
    EVT_MENU(ID_DARK_THEME, MainWindow::OnThemeChange)
    EVT_MENU(ID_LIGHT_THEME, MainWindow::OnThemeChange)
    EVT_MENU(ID_FONT_SELECT, MainWindow::OnFontSelect)
    EVT_MENU(ID_INSTALL_FIRAMONO, MainWindow::OnInstallFiraMonoFont)
    EVT_MENU(ID_PREFERENCES, MainWindow::OnPreferences)
    EVT_SYS_COLOUR_CHANGED(MainWindow::OnSystemColorChange)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "MDV - Markdown Viewer")
    , m_fontManager(FontManager::Get())
{
    // Set window size to match GitHub's width
    SetMinSize(wxSize(GITHUB_WINDOW_WIDTH, GITHUB_MIN_HEIGHT));
    SetSize(GITHUB_WINDOW_WIDTH, GITHUB_MIN_HEIGHT);
    
    // Create rich text control with GitHub-style margins
    int margin = (GITHUB_WINDOW_WIDTH - GITHUB_CONTENT_WIDTH) / 2;
    m_textCtrl = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString,
                               wxDefaultPosition, wxDefaultSize,
                               wxRE_MULTILINE | wxRE_READONLY | 
                               wxNO_BORDER);
    m_textCtrl->SetMargins(margin, margin);
    
    // Disable text selection
    m_textCtrl->SetEditable(false);
    m_textCtrl->SetCursor(wxCursor(wxCURSOR_ARROW));
    
    // Initialize markdown renderer
    m_markdownRenderer = std::make_unique<MarkdownRenderer>(this);
    
    CreateMenuBar();
    
    // Load theme settings
    LoadThemeSettings();
    
    // Check Windows dark mode setting and apply theme
    bool isDarkMode = IsWindowsDarkMode();
    
    // Set initial theme state
    if (GetMenuBar()) {
        wxMenu* settingsMenu = GetMenuBar()->GetMenu(1); // Settings is second menu
        if (settingsMenu) {
            wxMenuItem* darkItem = settingsMenu->FindItem(ID_DARK_THEME);
            wxMenuItem* lightItem = settingsMenu->FindItem(ID_LIGHT_THEME);
            if (darkItem && lightItem) {
                darkItem->Check(isDarkMode);
                lightItem->Check(!isDarkMode);
            }
        }
    }
    
    // Apply theme after menu setup
    ApplyTheme(isDarkMode);
    
    // Load and apply font settings
    LoadFontSettings();
    
    // Center on screen
    CenterOnScreen();
}

void MainWindow::ClearContent() {
    if (m_textCtrl) {
        m_textCtrl->Clear();
    }
}

void MainWindow::AppendText(const wxString& text) {
    if (m_textCtrl) {
        m_textCtrl->WriteText(text);
    }
}

void MainWindow::CreateMenuBar() {
    wxMenuBar* menuBar = new wxMenuBar();
    CreateFileMenu(menuBar);
    CreateSettingsMenu(menuBar);
    CreateHelpMenu(menuBar);
    SetMenuBar(menuBar);
}

void MainWindow::CreateFileMenu(wxMenuBar* menuBar) {
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_OPEN, "&Open...\tCtrl+O", "Open a markdown file");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit MDV");
    menuBar->Append(fileMenu, "&File");
}

void MainWindow::CreateSettingsMenu(wxMenuBar* menuBar) {
    wxMenu* settingsMenu = new wxMenu();
    
    // Theme submenu
    wxMenu* themeMenu = new wxMenu();
    m_darkThemeItem = themeMenu->AppendRadioItem(ID_DARK_THEME, "&Dark");
    m_lightThemeItem = themeMenu->AppendRadioItem(ID_LIGHT_THEME, "&Light");
    settingsMenu->AppendSubMenu(themeMenu, "&Theme");
    
    // Font options
    settingsMenu->AppendSeparator();
    settingsMenu->Append(ID_FONT_SELECT, "Select &Font...\tCtrl-F", "Choose display font");
    settingsMenu->Append(ID_INSTALL_FIRAMONO, "&Install FiraMono Font", "Install FiraMono Nerd Font");
    
    // Preferences
    settingsMenu->AppendSeparator();
    settingsMenu->Append(ID_PREFERENCES, "&Preferences...\tCtrl-P", "Configure MDV");
    
    menuBar->Append(settingsMenu, "&Settings");
}

void MainWindow::CreateHelpMenu(wxMenuBar* menuBar) {
    wxMenu* helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&About MDV", "About Markdown Viewer");
    menuBar->Append(helpMenu, "&Help");
}

void MainWindow::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent& event) {
    wxAboutDialogInfo info;
    info.SetName("MDV - Markdown Viewer");
    info.SetVersion("0.1.0");
    info.SetDescription("A minimalistic Markdown viewer for Windows");
    info.SetCopyright("(C) 2025");
    wxAboutBox(info);
}

void MainWindow::OnOpen(wxCommandEvent& event) {
    wxFileDialog openDialog(this, "Open Markdown File", "", "",
                          "Markdown files (*.md)|*.md|All files (*.*)|*.*",
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openDialog.ShowModal() == wxID_OK) {
        OpenFile(openDialog.GetPath());
    }
}

void MainWindow::OpenFile(const wxString& path) {
    wxString content = LoadFileContent(path);
    if (!content.empty()) {
        // Clear existing content
        ClearContent();
        
        // Render markdown
        if (m_markdownRenderer && m_markdownRenderer->RenderMarkdown(content)) {
            SetTitle(wxString::Format("MDV - %s", path.AfterLast('\\')));
            
            // Save as last opened file
            wxConfig config("MDV");
            config.Write("LastFile", path);
            config.Flush();
        } else {
            wxMessageBox("Failed to render markdown content.", "Error", wxICON_ERROR);
        }
    }
}

wxString MainWindow::LoadFileContent(const wxString& path) {
    wxTextFile file;
    if (!file.Open(path)) {
        wxMessageBox("Failed to open file.", "Error", wxICON_ERROR);
        return wxEmptyString;
    }
    
    wxString content;
    for (size_t i = 0; i < file.GetLineCount(); i++) {
        content += file[i];
        if (i < file.GetLineCount() - 1) {
            content += "\n";
        }
    }
    
    file.Close();
    return content;
}

void MainWindow::OnThemeChange(wxCommandEvent& event) {
    bool isDark = (event.GetId() == ID_DARK_THEME);
    ApplyTheme(isDark);
    
    // Save theme preference
    wxConfig config("MDV");
    config.Write("UseDarkTheme", isDark);
    config.Flush();
}

void MainWindow::OnSystemColorChange(wxSysColourChangedEvent& event) {
    bool isDark = IsWindowsDarkMode();
    ApplyTheme(isDark);
    event.Skip();
}

void MainWindow::OnFontSelect(wxCommandEvent& event) {
    wxFont currentFont = GetFont();
    if (m_fontManager.ShowFontDialog(this, currentFont)) {
        SetFont(currentFont);
        m_textCtrl->SetFont(currentFont);
        SaveFontSettings();
        Refresh();
    }
}

void MainWindow::OnInstallFiraMonoFont(wxCommandEvent& event) {
    if (m_fontManager.IsFiraMonoInstalled()) {
        wxMessageBox("FiraMono Nerd Font is already installed.",
                    "Font Installation",
                    wxICON_INFORMATION);
        return;
    }
    
    if (m_fontManager.InstallFiraMonoNerdFont()) {
        wxMessageBox("FiraMono Nerd Font was successfully installed.",
                    "Font Installation",
                    wxICON_INFORMATION);
        
        // Set as current font
        wxFont firaFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 
                       false, "FiraMono Nerd Font");
        SetFont(firaFont);
        m_textCtrl->SetFont(firaFont);
        SaveFontSettings();
        Refresh();
    }
}

void MainWindow::OnPreferences(wxCommandEvent& event) {
    SettingsDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        // Reload settings
        wxConfig config("MDV");
        
        // Apply theme if changed
        bool useDark = false;
        if (config.Read("UseDarkTheme", &useDark)) {
            ApplyTheme(useDark);
        }
        
        // Apply font if changed
        LoadFontSettings();
    }
}

bool MainWindow::IsWindowsDarkMode() {
    DWORD value = 0;
    DWORD size = sizeof(value);
    
    // Check Windows 10 dark mode setting
    if (RegGetValueA(HKEY_CURRENT_USER,
                    "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                    "AppsUseLightTheme",
                    RRF_RT_REG_DWORD,
                    nullptr,
                    &value,
                    &size) == ERROR_SUCCESS) {
        return value == 0;  // 0 means dark mode is enabled
    }
    
    return false;  // Default to light mode if we can't determine
}

void MainWindow::ApplyTheme(bool isDark) {
    // Set dark mode for the window frame
    BOOL darkMode = isDark ? TRUE : FALSE;
    DwmSetWindowAttribute(GetHandle(), DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
    
    // Allow dark mode for window frame
    BOOL allowDark = TRUE;
    DwmSetWindowAttribute(GetHandle(), 19, &allowDark, sizeof(allowDark));
    
    // GitHub colors
    wxColour bgColor, fgColor;
    if (isDark) {
        bgColor = wxColour(13, 17, 23);    // #0d1117 - GitHub dark mode background
        fgColor = wxColour(201, 209, 217); // #c9d1d9 - GitHub dark mode text
        SetWindowTheme(GetHandle(), L"DarkMode_Explorer", nullptr);
    } else {
        bgColor = wxColour(255, 255, 255); // #ffffff - GitHub light mode background
        fgColor = wxColour(36, 41, 47);    // #24292f - GitHub light mode text
        SetWindowTheme(GetHandle(), L"Explorer", nullptr);
    }
    
    // Apply colors to window and text control
    SetBackgroundColour(bgColor);
    SetForegroundColour(fgColor);
    m_textCtrl->SetBackgroundColour(bgColor);
    m_textCtrl->SetForegroundColour(fgColor);
    
    // Update menu checkmarks
    if (GetMenuBar()) {
        wxMenu* settingsMenu = GetMenuBar()->GetMenu(1); // Settings is second menu
        if (settingsMenu) {
            wxMenuItem* darkItem = settingsMenu->FindItem(ID_DARK_THEME);
            wxMenuItem* lightItem = settingsMenu->FindItem(ID_LIGHT_THEME);
            if (darkItem && lightItem) {
                darkItem->Check(isDark);
                lightItem->Check(!isDark);
            }
        }
    }
    
    // Force a complete redraw
    Refresh();
    Update();
}

void MainWindow::LoadThemeSettings() {
    wxConfig config("MDV");
    
    // Load accent color
    wxString accentColorStr;
    if (config.Read("AccentColor", &accentColorStr)) {
        m_accentColor.Set(accentColorStr);
    } else {
        // Default accent colors (GitHub style)
        m_accentColor = IsWindowsDarkMode() ? 
            wxColour(255, 255, 255) :  // White in dark mode
            wxColour(36, 41, 47);      // Dark gray in light mode
    }
}

void MainWindow::SaveThemeSettings() {
    wxConfig config("MDV");
    config.Write("AccentColor", m_accentColor.GetAsString(wxC2S_HTML_SYNTAX));
    config.Flush();
}

void MainWindow::SetAccentColor(const wxColour& color) {
    m_accentColor = color;
    SaveThemeSettings();
    
    // Refresh content to apply new color
    if (m_textCtrl && m_textCtrl->GetValue().Length() > 0) {
        wxString content = m_textCtrl->GetValue();
        ClearContent();
        if (m_markdownRenderer) {
            m_markdownRenderer->RenderMarkdown(content);
        }
    }
}

void MainWindow::LoadFontSettings() {
    wxConfig config("MDV");
    wxString fontFamily;
    int fontSize = 12;  // Default size
    
    if (config.Read("FontFamily", &fontFamily) && !fontFamily.empty()) {
        config.Read("FontSize", &fontSize);
        wxFont font(fontSize, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, 
                   false, fontFamily);
        SetFont(font);
        m_textCtrl->SetFont(font);
        Refresh();
    }
}

void MainWindow::SaveFontSettings() {
    wxConfig config("MDV");
    wxFont currentFont = GetFont();
    
    config.Write("FontFamily", currentFont.GetFaceName());
    config.Write("FontSize", currentFont.GetPointSize());
    config.Flush();
}

} // namespace mdv