# Current Task Status

## Current Objectives
1. Implement Windows-native font management
2. Create one-click FiraMono Nerd Font installation
3. Add native font selection dialog

## Context
Project has been updated to:
- Focus exclusively on Windows
- Use wxWidgets for native UI
- Integrate with Windows Font Management API
- Simplify font installation process

## Next Steps
1. Research Windows Font API:
   - AddFontResource/RemoveFontResource functions
   - Font installation permissions and requirements
   - System font enumeration
2. Create FontManager class:
   - Download FiraMono Nerd Font directly
   - Install fonts using Windows API
   - List system fonts
   - Handle font selection via native dialog
3. Update Settings dialog:
   - Add "Install FiraMono" button
   - Add font selection button
   - Save font preferences

## Related Roadmap Items
References from projectRoadmap.md:
- Markdown Rendering
  - [ ] Integration with md4c library
  - [ ] Read-only display functionality
  - [ ] Image and badge support

## Notes
- Use md4c for GFM-compatible parsing
- Focus on efficient rendering
- Implement proper text styling
- Consider image loading requirements