# Technology Stack

## Core Technologies

### GUI Framework
- **Win32 API with FLTK**
  - Version: Latest stable
  - Purpose: Native Windows GUI implementation
  - Chosen for: 
    - Lightweight footprint
    - Fast startup time
    - Minimal dependencies
    - Native Windows look and feel

### Markdown Processing
- **md4c**
  - Purpose: Markdown parsing and rendering
  - Chosen for:
    - Lightweight and fast
    - Pure C implementation
    - Small footprint
    - GitHub-compatible rendering

### PDF Generation
- **libharu**
  - Purpose: PDF export functionality
  - Chosen for:
    - Pure C implementation
    - Small footprint
    - Windows-optimized
    - Text and graphics capabilities

## Build System
- **CMake with MinGW-w64**
  - Purpose: Lightweight Windows build configuration
  - Features used:
    - MinGW-w64 toolchain
    - External dependency management
    - Installation rules

## Development Environment
- Compiler: MinGW-w64 GCC
- Build tools: CMake, MinGW-w64
- IDE: VSCode (optional)
- Target: Windows 10/11 x64

## Configuration
- Format: JSON
- Storage: %APPDATA%/MDV/config.json

## Dependencies Management
- Primary: CMake FetchContent
- Secondary: MinGW-w64 packages where available
- Vendored dependencies when necessary for stability

## Testing
- Framework: Catch2
- Coverage: gcov
- CI/CD: GitHub Actions (Windows runners)