#include "FontManager.hpp"
#include <windows.h>
#include <shlobj.h>
#include <wx/fontdlg.h>
#include <wx/msgdlg.h>
#include <wx/fontenum.h>
#include <filesystem>

FontManager& FontManager::Get() {
    static FontManager instance;
    return instance;
}

bool FontManager::InstallFont(const std::string& fontPath) {
    if (!std::filesystem::exists(fontPath)) {
        return false;
    }
    
    return AddFontResource(fontPath) && NotifyFontChange();
}

bool FontManager::UninstallFont(const std::string& fontPath) {
    return RemoveFontResource(fontPath) && NotifyFontChange();
}

bool FontManager::ShowFontDialog(wxWindow* parent, wxFont& selectedFont) {
    wxFontDialog dialog(parent, wxFontData());
    if (dialog.ShowModal() == wxID_OK) {
        selectedFont = dialog.GetFontData().GetChosenFont();
        return true;
    }
    return false;
}

std::vector<wxString> FontManager::GetInstalledFonts() {
    std::vector<wxString> fonts;
    wxArrayString systemFonts = wxFontEnumerator::GetFacenames();
    
    for (size_t i = 0; i < systemFonts.GetCount(); i++) {
        fonts.push_back(systemFonts[i]);
    }
    
    return fonts;
}

bool FontManager::InstallFiraMonoNerdFont() {
    std::string fontPath = GetFiraMonoPath();
    if (fontPath.empty() || !std::filesystem::exists(fontPath)) {
        wxMessageBox("FiraMono font file not found in the fonts directory.", 
                    "Font Installation Error", 
                    wxICON_ERROR);
        return false;
    }
    
    return InstallFont(fontPath);
}

bool FontManager::IsFiraMonoInstalled() {
    wxArrayString fonts = wxFontEnumerator::GetFacenames();
    return fonts.Index("FiraMono Nerd Font") != wxNOT_FOUND;
}

bool FontManager::AddFontResource(const std::string& fontPath) {
    if (AddFontResourceA(fontPath.c_str()) != 0) {
        return true;
    }
    
    DWORD error = GetLastError();
    wxMessageBox("Failed to add font resource. Error code: " + std::to_string(error),
                "Font Installation Error",
                wxICON_ERROR);
    return false;
}

bool FontManager::RemoveFontResource(const std::string& fontPath) {
    return RemoveFontResourceA(fontPath.c_str()) != 0;
}

bool FontManager::NotifyFontChange() {
    // Notify all windows of the font change
    if (SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0) == 0) {
        return false;
    }
    
    // Notify shell of the system parameters change
    return SystemParametersInfoA(SPI_SETFONTSMOOTHING,
                               0,
                               nullptr,
                               SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != 0;
}

std::string FontManager::GetFiraMonoPath() {
    std::filesystem::path exePath = std::filesystem::current_path();
    std::filesystem::path fontPath = exePath / "fonts" / "FiraMono" / "FiraMonoNerdFont-Regular.ttf";
    
    if (std::filesystem::exists(fontPath)) {
        return fontPath.string();
    }
    
    return "";
}