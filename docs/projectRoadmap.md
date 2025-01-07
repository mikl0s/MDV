# MDV Project Roadmap

## Project Goals
- Create a minimalistic, cross-platform Markdown viewer in C++
- Ensure fast startup and small memory footprint
- Support both Windows and Linux platforms
- Provide PDF export functionality
- Enable dynamic font management

## Key Features
- [ ] Basic Application Structure
  - [ ] FLTK-based GUI setup
  - [ ] Cross-platform CMake configuration
  - [ ] Basic window with menubar

- [ ] Markdown Rendering
  - [ ] Integration with GitHub Flavored Markdown library
  - [ ] Read-only display functionality
  - [ ] Image and badge support

- [ ] Theming System
  - [ ] Dark theme implementation (#1E1E1E with #007ACC highlights)
  - [ ] Light theme implementation
  - [ ] Theme switching functionality

- [ ] Font Management
  - [x] Bundle FiraMono font
  - [ ] Font directory scanning
  - [ ] Font download system (libcurl)
  - [ ] Font extraction and installation
  - [ ] Dynamic font switching

- [ ] PDF Export
  - [ ] PDF generation library integration
  - [ ] Export functionality
  - [ ] Theme-aware PDF generation

- [ ] Settings & Configuration
  - [ ] Config file implementation
  - [ ] Settings dialog
  - [ ] Preference persistence

## Completion Criteria
1. Application successfully builds on both Windows and Linux
2. Markdown files render correctly with GFM support
3. Theme switching works seamlessly
4. Font management system fully functional
5. PDF export produces correct output
6. Settings persist between sessions

## Completed Tasks
- [x] Initial project setup
- [x] FiraMono font bundling

## Future Considerations
- Markdown editing capabilities
- Plugin system
- Auto-update functionality
- Custom CSS support