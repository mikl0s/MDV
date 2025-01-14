#include "MarkdownRenderer.hpp"
#include "../gui/MainWindow.hpp"
#include <md4c.h>
#include <wx/richtext/richtextctrl.h>

namespace mdv {

MarkdownRenderer::MarkdownRenderer(MainWindow* parent)
    : parent(parent)
    , state(std::make_unique<RenderState>()) {
}

MarkdownRenderer::~MarkdownRenderer() = default;

bool MarkdownRenderer::RenderMarkdown(const wxString& markdown) {
    Clear();

    // Set up md4c parser options
    MD_PARSER parser = {};
    parser.flags = MD_FLAG_TABLES | MD_FLAG_STRIKETHROUGH | MD_FLAG_TASKLISTS;
    parser.enter_block = [](MD_BLOCKTYPE type, void* detail, void* userdata) -> int {
        auto* renderer = static_cast<MarkdownRenderer*>(userdata);
        if (renderer) {
            renderer->state->blockStack.push_back(type);
            renderer->ApplyBlockStyle(type);

            // Special handling for headers
            if (type == MD_BLOCK_H && detail != nullptr) {
                auto* h_detail = static_cast<MD_BLOCK_H_DETAIL*>(detail);
                renderer->parent->AppendText("\n");
            }
        }
        return 0;
    };
    parser.leave_block = [](MD_BLOCKTYPE type, void* detail, void* userdata) -> int {
        auto* renderer = static_cast<MarkdownRenderer*>(userdata);
        if (renderer && !renderer->state->blockStack.empty()) {
            renderer->state->blockStack.pop_back();
            
            // Add appropriate spacing after blocks
            if (renderer->parent) {
                renderer->parent->AppendText("\n");
                if (type == MD_BLOCK_H || type == MD_BLOCK_CODE || 
                    type == MD_BLOCK_QUOTE) {
                    renderer->parent->AppendText("\n");
                }
            }
        }
        return 0;
    };
    parser.enter_span = [](MD_SPANTYPE type, void* detail, void* userdata) -> int {
        auto* renderer = static_cast<MarkdownRenderer*>(userdata);
        if (renderer) {
            renderer->state->spanStack.push_back(type);
            renderer->ApplySpanStyle(type);
        }
        return 0;
    };
    parser.leave_span = [](MD_SPANTYPE type, void* detail, void* userdata) -> int {
        auto* renderer = static_cast<MarkdownRenderer*>(userdata);
        if (renderer && !renderer->state->spanStack.empty()) {
            renderer->state->spanStack.pop_back();
            if (!renderer->state->spanStack.empty()) {
                renderer->ApplySpanStyle(renderer->state->spanStack.back());
            }
        }
        return 0;
    };
    parser.text = [](MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata) -> int {
        auto* renderer = static_cast<MarkdownRenderer*>(userdata);
        if (renderer && text) {
            wxString content(text, wxConvUTF8, size);
            renderer->ProcessText(type, content);
        }
        return 0;
    };

    // Parse the markdown
    int result = md_parse(
        markdown.utf8_str(),
        markdown.length(),
        &parser,
        this
    );

    return result == 0;
}

void MarkdownRenderer::Clear() {
    if (state) {
        state->blockStack.clear();
        state->spanStack.clear();
        state->currentText.Clear();
        state->imageCache.clear();
    }

    // Clear the display in MainWindow
    if (parent) {
        parent->ClearContent();
    }
}

void MarkdownRenderer::ApplyBlockStyle(MD_BLOCKTYPE type, void* detail) {
    if (!parent) return;

    wxRichTextCtrl* textCtrl = parent->GetTextCtrl();
    if (!textCtrl) return;

    wxRichTextAttr style;
    style.SetAlignment(wxTEXT_ALIGNMENT_LEFT);

    bool isDark = parent->IsWindowsDarkMode();

    // GitHub's exact theme colors
    wxColour bgColor = isDark ? wxColour(13, 17, 23) : wxColour(255, 255, 255);    // #0d1117 or #ffffff
    wxColour textColor = isDark ? wxColour(240, 246, 252) : wxColour(31, 35, 40);  // #f0f6fc or #1f2328
    wxColour headerColor = isDark ? wxColour(255, 255, 255) : wxColour(31, 35, 40); // #ffffff or #1f2328
    wxColour codeBackground = isDark ? wxColour(21, 27, 35) : wxColour(246, 248, 250); // #151b23 or #f6f8fa
    wxColour quoteColor = isDark ? wxColour(145, 152, 161) : wxColour(89, 99, 110);    // #9198a1 or #59636e

    // Set window background color
    textCtrl->SetBackgroundColour(bgColor);
    style.SetBackgroundColour(bgColor);
    style.SetTextColour(textColor);

    // Set base font size and family
    style.SetFontSize(16);  // GitHub's base size
    style.SetFontFamily(wxFONTFAMILY_DEFAULT);
    style.SetLineSpacing(15);  // 1.5 line height

    // Ensure the text control is refreshed with new background
    textCtrl->Refresh();

    switch (type) {
        case MD_BLOCK_H: {
            auto* h_detail = static_cast<MD_BLOCK_H_DETAIL*>(detail);
            if (h_detail) {
                switch (h_detail->level) {
                    case 1:
                        // h1 - GitHub style
                        style.SetFontSize(32);  // 2em
                        style.SetFontWeight(wxFONTWEIGHT_BOLD);
                        style.SetTextColour(headerColor);  // Pure white in dark mode
                        style.SetParagraphSpacingBefore(24);  // 1.5rem
                        style.SetParagraphSpacingAfter(24);   // 1.5rem
                        style.SetLeftIndent(0);  // Reset any indentation
                        break;
                    case 2:
                        // h2 - GitHub style
                        style.SetFontSize(24);  // 1.5em
                        style.SetFontWeight(wxFONTWEIGHT_BOLD);
                        style.SetTextColour(headerColor);  // Pure white in dark mode
                        style.SetParagraphSpacingBefore(24);  // 1.5rem
                        style.SetParagraphSpacingAfter(24);   // 1.5rem
                        style.SetLeftIndent(0);  // Reset any indentation
                        break;
                    case 3:
                        // h3 - GitHub style
                        style.SetFontSize(20);  // 1.25em
                        style.SetFontWeight(wxFONTWEIGHT_BOLD);
                        style.SetTextColour(headerColor);  // Pure white in dark mode
                        style.SetParagraphSpacingBefore(24);  // 1.5rem
                        style.SetParagraphSpacingAfter(16);   // 1rem
                        style.SetLeftIndent(0);  // Reset any indentation
                        break;
                    case 4:
                        // h4 - GitHub style
                        style.SetFontSize(16);  // 1em
                        style.SetFontWeight(wxFONTWEIGHT_BOLD);
                        style.SetTextColour(headerColor);  // Pure white in dark mode
                        style.SetParagraphSpacingBefore(24);  // 1.5rem
                        style.SetParagraphSpacingAfter(16);   // 1rem
                        style.SetLeftIndent(0);  // Reset any indentation
                        break;
                    case 5:
                        // h5 - GitHub style
                        style.SetFontSize(14);  // 0.875em
                        style.SetFontWeight(wxFONTWEIGHT_BOLD);
                        style.SetTextColour(headerColor);  // Pure white in dark mode
                        style.SetParagraphSpacingBefore(24);  // 1.5rem
                        style.SetParagraphSpacingAfter(16);   // 1rem
                        style.SetLeftIndent(0);  // Reset any indentation
                        break;
                    case 6:
                        // h6 - GitHub style (muted)
                        style.SetFontSize(14);  // 0.85em
                        style.SetFontWeight(wxFONTWEIGHT_BOLD);
                        style.SetTextColour(quoteColor);  // Muted color
                        style.SetParagraphSpacingBefore(24);  // 1.5rem
                        style.SetParagraphSpacingAfter(16);   // 1rem
                        style.SetLeftIndent(0);  // Reset any indentation
                        break;
                }
            }
            break;
        }
        case MD_BLOCK_CODE:
            // Code blocks from github-markdown-dark.css
            style.SetFontFamily(wxFONTFAMILY_TELETYPE);
            style.SetFontSize(14);  // 85% of base size (16px * 0.85)
            style.SetBackgroundColour(codeBackground);  // #151b23 in dark mode
            style.SetTextColour(textColor);
            // GitHub's exact padding and margins
            style.SetLeftIndent(16);  // 1rem padding
            style.SetRightIndent(16); // 1rem padding
            style.SetParagraphSpacingBefore(16);  // 1rem margin
            style.SetParagraphSpacingAfter(16);   // 1rem margin
            style.SetLineSpacing(15);  // 1.45 line height
            // Reset any previous styling
            style.SetFontWeight(wxFONTWEIGHT_NORMAL);
            style.SetFontStyle(wxFONTSTYLE_NORMAL);
            break;
        case MD_BLOCK_QUOTE:
            // Blockquote styling from github-markdown-dark.css
            style.SetTextColour(quoteColor);  // Muted color
            style.SetFontSize(16);  // Same as base size
            style.SetLineSpacing(15);  // 1.5 line height
            // Padding and border simulation
            style.SetLeftIndent(32);  // 1rem padding + space for border
            style.SetRightIndent(0);  // Reset any right indent
            style.SetParagraphSpacingBefore(16);  // 1rem margin
            style.SetParagraphSpacingAfter(16);   // 1rem margin
            // Reset any previous styling
            style.SetFontWeight(wxFONTWEIGHT_NORMAL);
            style.SetFontStyle(wxFONTSTYLE_NORMAL);
            break;
        case MD_BLOCK_P:
            style.SetFontSize(16);    // GitHub's base font size
            style.SetTextColour(textColor);
            style.SetParagraphSpacingBefore(0);   // margin-top: 0
            style.SetParagraphSpacingAfter(16);   // margin-bottom: 1rem
            style.SetLineSpacing(15);  // 1.5 line height
            break;
        default:
            // Default text styling from github-markdown-dark.css
            style.SetFontSize(16);    // GitHub's base font size
            style.SetTextColour(textColor);
            style.SetParagraphSpacingBefore(0);   // margin-top: 0
            style.SetParagraphSpacingAfter(16);   // margin-bottom: 1rem
            style.SetLineSpacing(15);  // 1.5 line height
            style.SetLeftIndent(0);   // Reset any indentation
            style.SetRightIndent(0);  // Reset any indentation
            // Reset any previous styling
            style.SetFontWeight(wxFONTWEIGHT_NORMAL);
            style.SetFontStyle(wxFONTSTYLE_NORMAL);
            style.SetBackgroundColour(bgColor);
            break;
    }

    textCtrl->SetDefaultStyle(style);
}

void MarkdownRenderer::ApplySpanStyle(MD_SPANTYPE type) {
    if (!parent) return;

    wxRichTextCtrl* textCtrl = parent->GetTextCtrl();
    if (!textCtrl) return;

    wxRichTextAttr style = textCtrl->GetDefaultStyle();
    bool isDark = parent->IsWindowsDarkMode();

    // GitHub's exact theme colors (matching ApplyBlockStyle)
    wxColour textColor = isDark ? wxColour(240, 246, 252) : wxColour(31, 35, 40);        // #f0f6fc or #1f2328
    wxColour codeBackground = isDark ? wxColour(21, 27, 35) : wxColour(246, 248, 250);   // #151b23 or #f6f8fa
    wxColour inlineCodeText = isDark ? wxColour(240, 246, 252) : wxColour(31, 35, 40);   // #f0f6fc or #1f2328

    switch (type) {
        case MD_SPAN_EM:
            style.SetFontStyle(wxFONTSTYLE_ITALIC);
            break;
        case MD_SPAN_STRONG:
            style.SetFontWeight(wxFONTWEIGHT_BOLD);
            style.SetTextColour(textColor);
            break;
        case MD_SPAN_CODE:
            // Inline code styling from github-markdown-dark.css
            style.SetFontFamily(wxFONTFAMILY_TELETYPE);
            style.SetFontSize(14);  // 85% of base size (16px * 0.85)
            style.SetBackgroundColour(codeBackground);  // #151b23 in dark mode
            style.SetTextColour(textColor);
            // Add exact GitHub padding
            style.SetLeftIndent(8);   // .4em padding
            style.SetRightIndent(8);  // .4em padding
            // Reset any previous styling that might interfere
            style.SetFontWeight(wxFONTWEIGHT_NORMAL);
            style.SetFontStyle(wxFONTSTYLE_NORMAL);
            break;
        case MD_SPAN_DEL:
            style.SetFontStrikethrough(true);
            break;
        default:
            break;
    }

    textCtrl->SetDefaultStyle(style);
}

void MarkdownRenderer::ProcessText(MD_TEXTTYPE type, const wxString& text) {
    if (!parent) return;

    switch (type) {
        case MD_TEXT_NORMAL:
        case MD_TEXT_CODE:
            parent->AppendText(text);
            break;
        case MD_TEXT_NULLCHAR:
            parent->AppendText("");
            break;
        case MD_TEXT_BR:
            parent->AppendText("\n");
            break;
        case MD_TEXT_SOFTBR:
            parent->AppendText(" ");
            break;
        case MD_TEXT_HTML:
            // Skip HTML tags for now
            break;
        default:
            parent->AppendText(text);
            break;
    }
}

bool MarkdownRenderer::LoadImage(const wxString& url, wxBitmap& bitmap) {
    // Check cache first
    auto it = state->imageCache.find(url);
    if (it != state->imageCache.end()) {
        bitmap = it->second;
        return true;
    }

    // TODO: Implement image loading
    // For now, return false to indicate image loading is not implemented
    return false;
}

} // namespace mdv