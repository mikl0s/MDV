# Technology Stack

## Core Technologies

### GUI Framework
- **FLTK (Fast Light Toolkit)**
  - Version: Latest stable
  - Purpose: Cross-platform GUI implementation
  - Chosen for: 
    - Lightweight footprint
    - Fast startup time
    - Minimal dependencies
    - Native look and feel

### Markdown Processing
- **cmark-gfm**
  - Purpose: GitHub Flavored Markdown parsing and rendering
  - Chosen for:
    - GitHub-compatible rendering
    - Active maintenance
    - C/C++ native implementation
    - Performance and reliability

### Network Operations
- **libcurl**
  - Purpose: Font downloads and network operations
  - Features used:
    - HTTPS support
    - Progress monitoring
    - Async downloads
    - Error handling

### PDF Generation
- **libharu**
  - Purpose: PDF export functionality
  - Chosen for:
    - Pure C implementation
    - Small footprint
    - Cross-platform support
    - Text and graphics capabilities

### Compression
- **minizip**
  - Purpose: Font package extraction
  - Features used:
    - ZIP file handling
    - Cross-platform support
    - Simple integration

## Build System
- **CMake**
  - Purpose: Cross-platform build configuration
  - Features used:
    - External dependency management
    - Platform-specific configurations
    - Installation rules

## Development Environment
### Windows
- Compiler: MSVC or MinGW-w64
- Build tools: CMake, Visual Studio or VSCode

### Linux
- Compiler: GCC or Clang
- Build tools: CMake, Make
- Package formats: .deb, .rpm, or AppImage

## Configuration
- Format: JSON
- Storage:
  - Windows: %APPDATA%/MDV/config.json
  - Linux: ~/.mdvconfig

## Dependencies Management
- Primary: CMake FetchContent or Git submodules
- Secondary: System package managers where appropriate
- Vendored dependencies when necessary for stability

## Testing
- Framework: To be determined
- Coverage: To be determined
- CI/CD: To be determined