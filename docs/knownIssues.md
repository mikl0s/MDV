# Known Issues

## UI and Theming

### Dark Mode Integration
- **Menu Bar Theming**: The menu bar does not properly inherit the dark theme when Windows dark mode is enabled
  - **Impact**: Visual inconsistency between the application window and menu bar
  - **Current Status**: Attempted solutions:
    1. Using wxSystemSettings colors
    2. Using wxAUI for custom theming
    3. Using Windows UxTheme API
    4. Using DWM window frame attributes
  - **Technical Details**: 
    - The wxWidgets menu bar does not fully support Windows 10/11 dark mode
    - DwmSetWindowAttribute affects the window frame but not the menu bar
    - SetWindowTheme has limited effect on wxWidgets controls
  - **Workaround**: None currently available, waiting for better wxWidgets dark mode support

## Font Management

### Font Installation
- **System Integration**: Font installation requires proper Windows permissions
  - **Impact**: May fail on systems with restricted user permissions
  - **Workaround**: Run application as administrator when installing fonts

## Future Considerations

### Theme System
- Need to implement a more robust theme system that can:
  - Handle custom color schemes
  - Support user-defined themes
  - Better integrate with Windows system theme changes
  - Provide consistent appearance across all UI elements

### Menu System
- Consider alternatives to standard wxMenuBar:
  - Custom-drawn menu implementation
  - Alternative UI layout that doesn't rely on native menu bar
  - Ribbon-style interface for better theme control