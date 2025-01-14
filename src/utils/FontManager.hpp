#pragma once

#include <wx/wx.h>
#include <string>
#include <vector>

class FontManager {
public:
    // Singleton access
    static FontManager& Get();

    // Delete copy constructor and assignment operator
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    // Font installation
    bool InstallFont(const std::string& fontPath);
    bool UninstallFont(const std::string& fontPath);
    
    // Font selection
    bool ShowFontDialog(wxWindow* parent, wxFont& selectedFont);
    
    // System font enumeration
    std::vector<wxString> GetInstalledFonts();
    
    // FiraMono specific functions
    bool InstallFiraMonoNerdFont();
    bool IsFiraMonoInstalled();

private:
    FontManager() = default;  // Private constructor for singleton
    
    // Helper functions
    bool AddFontResource(const std::string& fontPath);
    bool RemoveFontResource(const std::string& fontPath);
    bool NotifyFontChange();  // Changed to return bool
    std::string GetFiraMonoPath();
};