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
├── src/                    # Source code (to be implemented)
│   ├── core/              # Core functionality
│   ├── gui/               # FLTK-based UI components
│   ├── markdown/          # Markdown processing
│   ├── pdf/               # PDF export functionality
│   └── utils/             # Utility functions
│
└── CMakeLists.txt         # Main CMake configuration (to be implemented)
```

## Key Components and Their Interactions

### Core Components (Planned)
1. **MainWindow** (gui/)
   - Primary FLTK window
   - Manages menu bar and layout
   - Coordinates between components

2. **MarkdownRenderer** (markdown/)
   - Interfaces with cmark-gfm
   - Converts Markdown to displayable format
   - Handles theme application to content

3. **FontManager** (utils/)
   - Manages font directory
   - Handles font downloads and installation
   - Provides font selection interface

4. **PDFExporter** (pdf/)
   - Converts rendered content to PDF
   - Applies current theme to output
   - Manages export process

5. **ConfigManager** (core/)
   - Handles settings persistence
   - Manages user preferences
   - Coordinates theme changes

## Data Flow
1. User opens Markdown file → MainWindow → MarkdownRenderer → Display
2. Theme change → ConfigManager → MainWindow → MarkdownRenderer → Refresh
3. Font download → FontManager → libcurl → minizip → Refresh
4. PDF export → MarkdownRenderer → PDFExporter → Save file

## External Dependencies
- FLTK: GUI framework
- cmark-gfm: Markdown processing
- libcurl: Network operations
- libharu: PDF generation
- minizip: Font package extraction

## Recent Changes
- Initial project setup
- Documentation structure established
- FiraMono font bundled

## Development Status
Project is in initial setup phase. Core implementation has not yet begun.

## User Feedback Integration
No user feedback yet as project is in initial phase.