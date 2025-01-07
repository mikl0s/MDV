# Codebase Summary

## Project Structure
```
MDV/
├── docs/                    # Project documentation
│   ├── prompt.md           # Original project specification
│   ├── projectRoadmap.md   # Project goals and progress
│   ├── currentTask.md      # Current development focus
│   ├── techStack.md        # Technology choices and rationale
│   └── codebaseSummary.md  # This file
│
├── fonts/                   # Font resources
│   └── FiraMono/           # Bundled FiraMono font
│
├── src/                    # Source code
│   ├── core/              # Core functionality
│   ├── gui/               # Win32-optimized UI components
│   │   ├── MainWindow.hpp # Main window header
│   │   └── MainWindow.cpp # Main window implementation
│   ├── markdown/          # Markdown processing
│   ├── pdf/               # PDF export functionality
│   └── utils/             # Windows utility functions
│
└── CMakeLists.txt         # MSVC build configuration
```

## Key Components and Their Interactions

### Core Components
1. **MainWindow** (gui/)
   - Win32-optimized FLTK window
   - Native Windows menubar
   - Windows theme integration

2. **MarkdownRenderer** (markdown/)
   - Interfaces with md4c
   - Fast markdown parsing
   - Windows-optimized display

3. **FontManager** (utils/)
   - Windows font directory scanning
   - User space font installation
   - System font integration

4. **PDFExporter** (pdf/)
   - Windows-styled PDF generation
   - Theme-aware output
   - Fast export process

5. **ConfigManager** (core/)
   - Windows registry/AppData config
   - Windows theme detection
   - Settings persistence

## Data Flow
1. User opens Markdown file → MainWindow → MarkdownRenderer → Display
2. Theme change → ConfigManager → Windows theme API → Refresh
3. Font management → FontManager → Windows Font API → Refresh
4. PDF export → MarkdownRenderer → PDFExporter → Save file

## External Dependencies
- FLTK: Win32-optimized GUI (Integrated)
- md4c: Lightweight Markdown processing (Pending)
- libharu: PDF generation (Pending)

## Recent Changes
- Removed cross-platform support
- Optimized for Windows performance
- Simplified dependency structure
- Enhanced Windows integration
- Streamlined build process

## Development Status
Project is being refocused for Windows-only support with emphasis on matching Notepad's performance characteristics. Build system is optimized for MSVC and Windows development.

## User Feedback Integration
No user feedback yet as project is in Windows optimization phase.