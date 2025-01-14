#pragma once

#include <wx/wx.h>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <md4c.h>
#include <md4c-html.h>

namespace mdv {

// Forward declarations
class MainWindow;

/**
 * @brief Handles markdown parsing and rendering using md4c
 */
class MarkdownRenderer {
public:
    /**
     * @brief Constructs a new MarkdownRenderer
     * @param parent The parent window that will display the rendered content
     */
    explicit MarkdownRenderer(MainWindow* parent);
    ~MarkdownRenderer();

    /**
     * @brief Renders markdown text to styled wxTextCtrl content
     * @param markdown The markdown text to render
     * @return true if rendering was successful, false otherwise
     */
    bool RenderMarkdown(const wxString& markdown);

    /**
     * @brief Clears the current rendered content
     */
    void Clear();

private:
    // Internal rendering state
    struct RenderState {
        std::vector<MD_BLOCKTYPE> blockStack;
        std::vector<MD_SPANTYPE> spanStack;
        wxString currentText;
        std::map<wxString, wxBitmap> imageCache;
    };
    std::unique_ptr<RenderState> state;

    // Parent window reference
    MainWindow* parent;

    // Helper methods
    void ApplyBlockStyle(MD_BLOCKTYPE type, void* detail = nullptr);
    void ApplySpanStyle(MD_SPANTYPE type);
    void ProcessText(MD_TEXTTYPE type, const wxString& text);
    bool LoadImage(const wxString& url, wxBitmap& bitmap);
};

} // namespace mdv