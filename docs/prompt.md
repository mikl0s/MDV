# Markdown Viewer (MDV) Specification — FLTK + libcurl + PDF Export  
**Last Updated**: (Insert Date Here)  
**Author**: (Your Name / Team)

---

## 1. Overview

- **Project Name**: **Markdown Viewer (MDV)**
- **Supported Platforms**: **Windows**
- **Goal**:
  Build a minimalistic Windows Markdown viewer in C++ using [wxWidgets](https://www.wxwidgets.org/) as the GUI toolkit.
  - Runs on Windows with native look and feel
  - Aims for small memory usage and fast startup (akin to a basic system Notepad).
  - Renders GitHub Flavored Markdown in a read-only manner.

- **Scope**:  
  1. **View-Only**: No editing, just display Markdown.  
  2. **Theming**: Default dark theme with blue highlights and a light theme.  
  3. **Fonts**: Bundle FiraMono and let the user download additional fonts (e.g., from [Nerd Fonts](https://www.nerdfonts.com/font-downloads)).  
  4. **PDF Export**: Allow the user to export the rendered Markdown to a PDF file.  
     - The user can then open/print the PDF with their OS’s native printing tools.  
  5. **Cross-Platform**: Build for Windows and Linux with minimal overhead.

---

## 2. Libraries & Components

### 2.1 wxWidgets (GUI)
- **Purpose**:
  - Create native Windows UI with proper menus, dialogs, and modern look and feel
  - Handle user interactions (open file, settings, about, etc.)
  - Provide native file dialogs and system integration

### 2.2 Markdown Rendering
- **Candidates**:  
  - [cmark-gfm](https://github.com/github/cmark-gfm) (GitHub Flavored Markdown).  
  - [md4c](https://github.com/mity/md4c) or [discount](https://www.pell.portland.or.us/~orc/Code/discount/).  
- **Integration**:  
  - Parse `.md` files into HTML or an internal structure.  
  - Display via a lightweight approach inside FLTK (custom drawing or a small HTML renderer, if available).

### 2.3 Windows Font API
- **Purpose**:
  - Install fonts directly into Windows
  - List available system fonts
  - Handle font installation from downloaded files
  - Provide native font selection dialog

### 2.4 PDF Export
- **Approach**:  
  - Convert rendered Markdown (text layout + styling) into a PDF document.  
  - **Recommended Libraries**: [libharu](http://libharu.org/), [PoDoFo](https://podofo.sourceforge.net/), or similar.  
- **Usage**:  
  - Provide a **File → Export to PDF** menu item.  
  - Generate the PDF with the user’s chosen theme or a default theme.  
  - Save the PDF in a user-chosen location.  
  - The user can then open/print the PDF externally.

---

## 3. Key Features

1. **Markdown Rendering**  
   - GitHub Flavored Markdown for headings, tables, code blocks, images, links, etc.  
   - Handle external images/badges if the user is online (optional).  
   - A “notepad-like” window that displays rendered content.

2. **Theming**  
   - **Default Dark Theme** with a dark gray background (#1E1E1E) and blue highlights (#007ACC).  
   - **Light Theme** with black text on white background.  
   - Allow user to switch themes in **Settings**.  
   - Apply theme colors to the Markdown render if feasible (or at least background/foreground text).
3. **Font Management**
   - **Default Font**: FiraMono Nerd Font with one-click installation
   - **System Integration**:
     1. Use Windows Font Management API to install fonts directly into Windows
     2. List and select from installed system fonts
     3. Provide direct download and installation of FiraMono Nerd Font
   - **Font Selection**:
     1. Use native Windows font dialog for selection
     2. Remember user's font preference
     3. Automatic font installation without requiring app restart
   - Provide a **Settings** combo box or list to select the active font.

4. **PDF Export**  
   - **File → Export to PDF** menu item.  
   - Render the current Markdown document into a PDF with the user’s chosen theme or default.  
   - Save the PDF to disk; the user can then open it or print via system tools.

5. **Settings & Persistence**  
   - Minimal config file (JSON or INI) to remember user preferences:  
     - Theme  
     - Font  
     - Last opened file (if “reopen on startup” is enabled)  
     - PDF export theme preference (default or forced light)  
   - Simple Settings dialog: theme switch, font selector, checkboxes for preferences.

6. **Cross-Platform Support**  
   - **Windows**:  
     - Build natively with MSVC or MinGW-w64.  
   - **Linux**:  
     - Build with GCC or Clang, package with `.deb`, `.rpm`, or an AppImage.  
   - For advanced users: cross-compile Windows binaries on Linux using MinGW-w64.  
   - Keep external dependencies minimal to maintain a small footprint.

7. **Menu Structure** (example)  
   - **File**  
     - Open...  
     - Export to PDF...  
     - Exit  
   - **Settings**  
     - Theme (Dark/Light)  
     - Font (Dropdown list)  
     - Other preferences...  
   - **Help**  
     - About MDV  

---

## 4. Implementation Outline

1. **Project Setup**  
   - Use CMake for cross-platform builds.  
   - Include FLTK, cmark (or your chosen Markdown lib), libcurl, PDF export library, etc.

2. **UI Prototype**  
   - Build a main FLTK window with a menubar.  
   - Center widget for displaying rendered Markdown (or a custom FLTK widget).

3. **Markdown Rendering**  
   - Convert `.md` text to either an internal structure or HTML.  
   - If HTML-based, embed a lightweight HTML renderer or parse/draw directly with FLTK.

4. **Theme Management**  
   - Create a function to apply dark or light color sets to FLTK elements (background, text color, highlight, etc.).  
   - Ensure the Markdown content respects those colors where possible.

5. **Font Loading**  
   - On startup, scan `fonts/` directory for `.otf`/`.ttf` files.  
   - Use FLTK’s `Fl::set_fonts()` or a custom approach to load them.  
   - Provide a Settings combobox to pick which font to use in the viewer.

6. **Font Downloads**  
   - Add a “Download Fonts” button or dialog in Settings.  
   - Use libcurl in a background thread to fetch the file.  
   - Unzip to `fonts/<FontName>`.  
   - Refresh the font list.

7. **PDF Export**  
   - **File → Export to PDF** triggers PDF creation.  
   - Use a library like **libharu** or **PoDoFo**.  
   - Map your Markdown layout to PDF pages.  
   - Save the generated PDF to a user-selected path.

8. **Settings Persistence**  
   - Use a small JSON or INI file, e.g. `~/.mdvconfig` (Linux), `%APPDATA%/MDV/config.json` (Windows).  
   - Load on startup; apply theme and font.  
   - Save changes on exit or when settings are updated.

9. **Testing & Packaging**  
   - Test on Linux and Windows with various Markdown files.  
   - Ensure PDF export works, theme switching, font installation, etc.  
   - Create installers or binaries for each OS:
     - `.exe` for Windows  
     - `.deb`, `.rpm`, or `.AppImage` for Linux  

---

## 5. Potential Future Enhancements

- **Markdown Editing**: A full editor with live preview.  
- **Plugins / Extensions**: Syntax highlighting, extended GFM features.  
- **Auto-Update**: Check for new releases, prompt the user.  
- **Custom CSS**: For advanced theming beyond simple color changes.

---

## 6. Prompt Summary

> **Build a C++ Markdown Viewer (MDV)** that uses **FLTK** for UI, **libcurl** for font downloads, and a **Markdown library** (cmark-gfm, etc.). The final app should:  
> 1. Run on **Windows** and **Linux** with minimal overhead.  
> 2. Render Markdown (GitHub-style) in a read-only manner.  
> 3. Offer dark/light themes and dynamic font selection.  
> 4. Allow the user to download additional fonts, unpack them, and load them on the fly.  
> 5. Export to **PDF** so users can print externally.  
> 6. Store user settings (theme, font, last opened file) in a simple config.

---

**End of Document**
