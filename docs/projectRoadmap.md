# MDV Project Roadmap

## Project Goals
- Create a minimalistic Markdown viewer for Windows
- Match Notepad's startup speed and memory footprint
- Provide essential features without bloat
- Enable PDF export functionality
- Support system and custom fonts
- Deliver native Windows look and feel

## Key Features
- [ ] Basic Application Structure
  - [ ] wxWidgets setup and configuration
  - [ ] Native Windows menubar and dialogs
  - [ ] Modern Windows UI styling

- [ ] Markdown Rendering
  - [ ] Integration with md4c library
  - [ ] Read-only display functionality
  - [ ] Image and badge support

- [ ] Theming System
  - [ ] Dark theme implementation (#1E1E1E with #007ACC highlights)
  - [ ] Light theme implementation
  - [ ] Windows theme integration
- [ ] Font Management
  - [ ] Windows Font API integration
  - [ ] One-click FiraMono Nerd Font installation
  - [ ] Native font selection dialog
  - [ ] Automatic font installation via Windows API
  - [ ] Dynamic font switching

- [ ] PDF Export
  - [ ] PDF generation with libharu
  - [ ] Export functionality
  - [ ] Theme-aware PDF generation

- [ ] Settings & Configuration
  - [ ] Windows registry/AppData config
  - [ ] Settings dialog
  - [ ] Preference persistence

## Completion Criteria
1. Application matches Notepad startup time
2. Markdown files render with full fidelity
3. Theme switching works seamlessly
4. Font management fully functional
5. PDF export produces correct output
6. Settings persist between sessions

## Completed Tasks
- [x] Initial project setup
- [x] FiraMono font bundling
- [x] CMake build system configuration
- [x] FLTK integration and build setup

## Future Considerations
- Markdown editing capabilities
- Shell integration
- File association handler
- Windows context menu integration