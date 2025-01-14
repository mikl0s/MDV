# Codebase Summary

## Project Structure
```
MDV/
├── docs/                    # Project documentation
│   ├── prompt.md           # Original project specification
│   ├── projectRoadmap.md   # Project goals and progress
│   ├── currentTask.md      # Current development focus
│   ├── techStack.md        # Technology choices and rationale
│   ├── knownIssues.md      # Known issues and limitations
│   └── codebaseSummary.md  # This file
│
├── fonts/                   # Font resources
│   └── FiraMono/           # Bundled FiraMono font
│
├── src/                    # Source code
│   ├── core/              # Core functionality (pending)
│   ├── gui/               # Windows-native UI components
│   │   ├── MainWindow.hpp    # Main window header
│   │   ├── MainWindow.cpp    # Main window implementation
│   │   ├── SettingsDialog.hpp# Settings dialog header
│   │   └── SettingsDialog.cpp# Settings dialog implementation
│   ├── markdown/          # Markdown processing (pending)
│   ├── pdf/              # PDF export functionality (pending)
│   └── utils/            # Windows utility functions
│       ├── FontManager.hpp   # Font management header
│       └── FontManager.cpp   # Font management implementation
│
└── CMakeLists.txt         # MinGW-w64 build configuration
```

## Key Components and Their Interactions

### Core Components
1. **MainWindow** (gui/)
   - wxWidgets window implementation
   - Native Windows menus and dialogs
   - Theme management
   - File handling
   - Text display

2. **SettingsDialog** (gui/)
   - Preferences management
   - Font installation interface
   - Theme selection
   - Configuration persistence

3. **FontManager** (utils/)
   - Windows Font API integration
   - FiraMono font installation
   - System font enumeration
   - Font selection dialog

Other components pending implementation:
- MarkdownRenderer (markdown/)
- PDFExporter (pdf/)
- ConfigManager (core/)

## Data Flow
Current implementation:
1. Application start → MainWindow creation
2. MainWindow loads settings → Applies theme/font
3. User opens file → Display raw markdown
4. User changes settings → Persist to registry

Pending implementations:
- Markdown parsing and rendering
- PDF export pipeline
- Image handling

## External Dependencies
- wxWidgets: Native Windows GUI (Integrated)
- md4c: Markdown processing (Pending)
- libharu: PDF generation (Pending)

## Recent Changes
- Switched from FLTK to wxWidgets for better Windows integration
- Implemented Windows Font API integration
- Added settings persistence via wxConfig
- Added dark mode support with DWM integration
- Created settings dialog
- Added file opening functionality
- Implemented theme system

## Development Status
Project is progressing with:
- Complete font management system
- Working theme integration
- Basic file handling
- Settings persistence
- Native Windows look and feel

## User Feedback Integration
Current feedback addressed:
- Improved dark mode integration
- Added settings dialog
- Fixed cursor visibility in text display
- Removed system beep on readonly text
- Added proper theme inheritance