# Technology Stack

## Core Technologies

### GUI Framework
- **wxWidgets**
  - Version: 3.0.5
  - Purpose: Native Windows GUI implementation
  - Chosen for: 
    - Native Windows look and feel
    - Built-in theme support
    - Rich widget set
    - Modern Windows 11 integration
    - Comprehensive font support

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

## Windows Integration
- **DWM API**
  - Purpose: Modern Windows theming
  - Features used:
    - Dark mode support
    - Window frame customization
    - System theme detection

- **Windows Font API**
  - Purpose: Font management
  - Features used:
    - Font installation
    - System font enumeration
    - Font resource management

## Build System
- **CMake with MinGW-w64**
  - Purpose: Windows build configuration
  - Features used:
    - MinGW-w64 toolchain
    - Static linking
    - External dependency management
    - Installation rules

## Development Environment
- Compiler: MinGW-w64 GCC 14.2.0
- Build tools: CMake 3.15+, MinGW-w64
- IDE: VSCode (optional)
- Target: Windows 10/11 x64

## Configuration
- System: Windows Registry
- Format: wxConfig API
- Storage: 
  - Settings: HKEY_CURRENT_USER\Software\MDV
  - Fonts: Windows Font Directory
  - Cache: %APPDATA%\MDV

## Dependencies Management
- Primary: CMake FetchContent
- Secondary: MinGW-w64 packages
- Static linking for portability

## Testing
- Framework: Catch2
- Coverage: gcov
- CI/CD: GitHub Actions (Windows runners)

## Key Design Decisions
1. **Native Over Custom**
   - Use Windows APIs where possible
   - Leverage system theme and fonts
   - Native dialogs and menus

2. **Static Over Dynamic**
   - Static linking for portability
   - Minimal runtime dependencies
   - Self-contained executable

3. **Performance Focus**
   - Fast startup time
   - Low memory footprint
   - Efficient rendering pipeline

4. **Modern Windows Support**
   - Windows 10/11 features
   - Dark mode integration
   - High DPI awareness