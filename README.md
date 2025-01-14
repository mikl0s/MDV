<div align="center">

<img src="logo.png" alt="MDV Logo" width="150" height="150"/>

# Markdown Viewer (MDV)

🚀 A blazingly fast, Notepad-like Markdown viewer for Windows

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-Windows-blue)](https://github.com/mikl0s/MDV)
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![wxWidgets](https://img.shields.io/badge/wxWidgets-3.0.5-green)](https://www.wxwidgets.org/)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://github.com/mikl0s/MDV/pulls)

[Features](#features) • [Installation](#installation) • [Usage](#usage) • [Themes](#themes) • [Contributing](#contributing)

</div>

## ✨ Features

- 🎯 **Fast as Notepad** - Instant startup, minimal memory usage
- 🎨 **Windows-native Themes** - Dark and light themes that follow your system
- 🔤 **Native Font Integration** - One-click FiraMono installation, use any system font
- 📝 **Basic Markdown Support** - View markdown files in a clean, distraction-free interface
- 🪟 **Windows Integration** - Native menus, dialogs, and system fonts
- ⚡ **Ultra Lightweight** - Small executable, minimal dependencies

## 🎨 Themes

MDV automatically follows your Windows theme settings:

- Dark theme with #1E1E1E background
- Light theme with system colors
- Proper Windows 11 dark mode integration
- Theme-aware font rendering

## 🏗️ Architecture

```mermaid
graph TD
    A[wxWidgets GUI] --> B[Text Display]
    A --> C[Font Manager]
    C --> D[Windows Font API]
    A --> E[Theme System]
    E --> F[Windows DWM]
    style A fill:#007ACC,color:white
    style B fill:#1E1E1E,color:white
    style C fill:#007ACC,color:white
    style D fill:#1E1E1E,color:white
    style E fill:#007ACC,color:white
    style F fill:#1E1E1E,color:white
```

## 🛠️ Building from Source

### Prerequisites

1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 and install required packages:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-wxWidgets mingw-w64-x86_64-make
```
3. Add MinGW-w64 bin directory to your PATH:
```
C:\msys64\mingw64\bin
```

### Build Steps

1. Clone the repository
```bash
git clone https://github.com/mikl0s/MDV.git
cd MDV
```

2. Configure and build
```bash
# Configure
cmake -B build -G "MinGW Makefiles"

# Build
cmake --build build --config Release
```

The executable will be in `build/mdv.exe`

## 📖 Usage

1. Launch MDV
2. Open a Markdown file via File → Open
3. Use the menu to:
   - Switch between dark and light themes
   - Install FiraMono Nerd Font (Settings → Install FiraMono)
   - Select system fonts (Settings → Font)
   - Configure preferences (Settings → Preferences)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

## 📄 License

This project is licensed under the MIT License - see below for details:

```
MIT License

Copyright (c) 2025 Mikkel Georgsen / Dataløs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

<div align="center">
Made with ❤️ by <a href="https://github.com/mikl0s">Mikkel Georgsen</a>
</div>