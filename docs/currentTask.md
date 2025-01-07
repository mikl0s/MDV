# Current Task Status

## Current Objectives
1. Set up MinGW-w64 development environment
2. Test initial Windows build
3. Verify FLTK window creation

## Context
Moving to direct Windows development with MinGW-w64. The next phase involves:
- Setting up MSYS2/MinGW-w64 environment
- Testing lightweight build process
- Verifying FLTK Windows integration
- Initial performance benchmarking

## Next Steps
1. Install MSYS2 from https://www.msys2.org/
2. Install required packages:
   ```bash
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake make
   ```
3. Add to PATH: C:\msys64\mingw64\bin
4. Clone repository and build:
   ```bash
   git clone https://github.com/mikl0s/MDV.git
   cd MDV
   cmake -B build -G "MinGW Makefiles"
   cmake --build build --config Release
   ```
5. Test initial window creation

## Related Roadmap Items
References from projectRoadmap.md:
- Basic Application Structure
  - [x] Win32-optimized FLTK setup
  - [x] MinGW-w64 build configuration
  - [ ] Native Windows menubar

## Notes
- Development using lightweight MinGW-w64 toolchain
- MSYS2 provides necessary build tools
- Initial v0.0.1 tag created
- Focus on minimal, fast Windows development