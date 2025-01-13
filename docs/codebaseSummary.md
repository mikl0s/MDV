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
│   ├── core/              # Core functionality (pending)
│   ├── gui/               # Win32-optimized UI components
│   │   ├── MainWindow.hpp # Main window header
│   │   └── MainWindow.cpp # Main window implementation
│   ├── markdown/          # Markdown processing (pending)
│   ├── pdf/              # PDF export functionality (pending)
│   └── utils/            # Windows utility functions (pending)
│
└── CMakeLists.txt         # MinGW-w64 build configuration
```

## Key Components and Their Interactions

### Core Components
1. **MainWindow** (gui/)
   - Basic FLTK window implementation
   - Text display widget
   - Window management functions

Other components pending implementation:
- MarkdownRenderer (markdown/)
- FontManager (utils/)
- PDFExporter (pdf/)
- ConfigManager (core/)

## Data Flow
Initial implementation:
1. Application start → MainWindow creation → Window display

Pending implementations:
- Markdown file processing
- Theme management
- Font handling
- PDF export

## External Dependencies
- FLTK: Win32-optimized GUI (Integrated)
- md4c: Lightweight Markdown processing (Pending)
- libharu: PDF generation (Pending)

## Recent Changes
- Fresh start with clean codebase
- Basic FLTK window implementation
- Directory structure setup
- CMake build system configuration
- MinGW-w64 toolchain setup

## Development Status
Project has been reset with a fresh implementation focusing on:
- Clean, minimal codebase
- Windows-optimized FLTK integration
- Step-by-step feature implementation
- Performance-first approach

## User Feedback Integration
No user feedback yet as project is in initial implementation phase.