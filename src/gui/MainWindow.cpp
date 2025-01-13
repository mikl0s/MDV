#include "MainWindow.hpp"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>

namespace mdv {

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(ID_Open, MainWindow::OnOpen)
    EVT_MENU(ID_ExportPDF, MainWindow::OnExportPDF)
    EVT_MENU(wxID_EXIT, MainWindow::OnExit)
    EVT_MENU(ID_ThemeDark, MainWindow::OnThemeChange)
    EVT_MENU(ID_ThemeLight, MainWindow::OnThemeChange)
    EVT_MENU(ID_FontSelect, MainWindow::OnFontSelect)
    EVT_MENU(ID_Preferences, MainWindow::OnPreferences)
    EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "MDV - Markdown Viewer",
              wxDefaultPosition, wxSize(800, 600))
{
    // Create menu bar
    CreateMenuBar();
    
    // Create text display
    display_ = new wxTextCtrl(this, wxID_ANY, wxEmptyString,
                            wxDefaultPosition, wxDefaultSize,
                            wxTE_MULTILINE | wxTE_READONLY | wxBORDER_NONE);
    
    // Set up sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(display_, 1, wxEXPAND);
    SetSizer(sizer);
    
    // Set window properties
    SetBackgroundColour(wxColour(255, 255, 255));
    Centre();
}

void MainWindow::CreateMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar();
    
    // File menu
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(ID_Open, "&Open...\tCtrl+O");
    fileMenu->Append(ID_ExportPDF, "&Export to PDF...\tCtrl+E");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);
    menuBar->Append(fileMenu, "&File");
    
    // Settings menu
    wxMenu* settingsMenu = new wxMenu();
    wxMenu* themeSubMenu = new wxMenu();
    themeSubMenu->Append(ID_ThemeDark, "&Dark");
    themeSubMenu->Append(ID_ThemeLight, "&Light");
    settingsMenu->AppendSubMenu(themeSubMenu, "&Theme");
    settingsMenu->Append(ID_FontSelect, "&Font...");
    settingsMenu->AppendSeparator();
    settingsMenu->Append(ID_Preferences, "&Preferences...");
    menuBar->Append(settingsMenu, "&Settings");
    
    // Help menu
    wxMenu* helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT);
    menuBar->Append(helpMenu, "&Help");
    
    SetMenuBar(menuBar);
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openDialog(this, "Open Markdown File", "", "",
                          "Markdown files (*.md)|*.md",
                          wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openDialog.ShowModal() == wxID_OK) {
        // TODO: Load and render markdown file
    }
}

void MainWindow::OnExportPDF(wxCommandEvent& event)
{
    wxFileDialog saveDialog(this, "Export PDF", "", "",
                          "PDF files (*.pdf)|*.pdf",
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (saveDialog.ShowModal() == wxID_OK) {
        // TODO: Export to PDF
    }
}

void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainWindow::OnThemeChange(wxCommandEvent& event)
{
    // TODO: Implement theme change
}

void MainWindow::OnFontSelect(wxCommandEvent& event)
{
    // TODO: Implement font selection
}

void MainWindow::OnPreferences(wxCommandEvent& event)
{
    // TODO: Show preferences dialog
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("MDV - Markdown Viewer\nVersion 0.1.0\n\nA lightweight Markdown viewer",
                "About MDV", wxOK | wxICON_INFORMATION);
}

} // namespace mdv