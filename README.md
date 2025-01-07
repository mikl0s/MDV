<div align="center">

<img src="logo.png" alt="MDV Logo" width="150" height="150"/>

# Markdown Viewer (MDV)

🚀 A blazingly fast, Notepad-like Markdown viewer for Windows

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/platform-Windows-blue)](https://github.com/mikl0s/MDV)
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=c%2B%2B)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![FLTK](https://img.shields.io/badge/FLTK-1.4.1-orange)](https://www.fltk.org/)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)](https://github.com/mikl0s/MDV/pulls)

[Features](#features) • [Installation](#installation) • [Usage](#usage) • [Themes](#themes) • [Contributing](#contributing)

<img src="docs/assets/hero.png" alt="MDV Screenshot" width="800"/>

</div>

## ✨ Features

- 🎯 **Fast as Notepad** - Instant startup, minimal memory usage
- 🎨 **Windows-native Themes** - Follows your system theme
- 🔤 **Custom Fonts** - Bundled with FiraMono, use any system font
- 📑 **GitHub Flavored Markdown** - Tables, code blocks, and more
- 🖨️ **PDF Export** - Generate beautiful PDFs with a click
- 💡 **Ultra Lightweight** - Smaller than a typical web browser
- 🪟 **Windows Integration** - Native menus and dialogs

## 🚀 Quick Start

```powershell
# Download the latest release
winget install MDV

# Or build from source
cmake -B build -S . -G "Visual Studio 17 2022"
cmake --build build --config Release
```

## 🎨 Themes

MDV follows your Windows theme settings:

<div align="center">
<table>
<tr>
<td align="center">
<strong>Dark Theme (Windows Dark)</strong><br>
<img src="docs/assets/dark-theme.png" width="400"/>
</td>
<td align="center">
<strong>Light Theme (Windows Light)</strong><br>
<img src="docs/assets/light-theme.png" width="400"/>
</td>
</tr>
</table>
</div>

## 🏗️ Architecture

```mermaid
graph TD
    A[Win32 GUI] --> B[Markdown Parser]
    B --> C[Native Renderer]
    A --> D[Font Manager]
    D --> E[Windows Font API]
    A --> F[PDF Exporter]
    style A fill:#007ACC,color:white
    style B fill:#1E1E1E,color:white
    style C fill:#1E1E1E,color:white
    style D fill:#1E1E1E,color:white
    style E fill:#1E1E1E,color:white
    style F fill:#1E1E1E,color:white
```

## 🛠️ Building from Source

### Prerequisites

- Visual Studio 2022 or later
- CMake 3.15+
- Windows 10/11 SDK

### Build Steps

1. Clone the repository
```powershell
git clone git@github.com:mikl0s/MDV.git
cd MDV
```

2. Configure and build
```powershell
cmake -B build -S . -G "Visual Studio 17 2022"
cmake --build build --config Release
```

## 📖 Usage

1. Launch MDV
2. Open a Markdown file via File → Open or drag & drop
3. Use the menu to:
   - Switch themes (follows Windows theme)
   - Change fonts (Settings → Font)
   - Export to PDF (File → Export to PDF)

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