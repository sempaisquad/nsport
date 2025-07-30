# NetSurf Mac OS 9 Port

This is a complete port of the NetSurf web browser to Mac OS 9, using the Carbon API and built with the Retro68 toolchain.

## Features

- Native Mac OS 9 Carbon application
- Full NetSurf rendering engine
- Support for HTML, CSS, and common image formats
- Integrated scrollbars and standard Mac OS interface
- Menu bar with standard File, Edit, View, and Go menus
- Keyboard shortcuts and mouse handling
- Basic HTTP fetching (expandable for full network support)

## Requirements

### Build Requirements
- Retro68 toolchain installed and configured
- Mac OS 9 development headers (Universal Interfaces)
- Git for fetching NetSurf libraries
- Standard Unix build tools (make, bash)

### Runtime Requirements  
- Mac OS 9.0 or later
- PowerPC or 68K Macintosh
- At least 2MB RAM (4MB recommended)
- Color QuickDraw

## Building

1. **Install Retro68**
   ```bash
   git clone https://github.com/autc04/Retro68.git
   cd Retro68
   ./build-toolchain.bash
   ```

2. **Clone this repository**
   ```bash
   git clone [this-repository-url] netsurf-macos9
   cd netsurf-macos9
   ```

3. **Build NetSurf**
   ```bash
   chmod +x build.sh
   ./build.sh
   ```

The build script will:
- Download and compile all required NetSurf libraries
- Build the Mac OS 9 frontend
- Create the final NetSurf application

## File Structure

```
netsurf-macos9/
├── CMakeLists.txt          # CMake build configuration
├── Makefile                # Traditional makefile
├── build.sh                # Complete build script
├── include/
│   └── macos9_gui.h        # Main header file
├── src/
│   ├── main.c              # Application entry point
│   ├── gui.c               # GUI operations
│   ├── window.c            # Window management
│   ├── bitmap.c            # Bitmap handling
│   ├── fetch.c             # Network operations
│   ├── schedule.c          # Event scheduling
│   ├── misc.c              # Miscellaneous operations
│   ├── layout.c            # Text layout
│   ├── utf8.c              # Text encoding
│   ├── file.c              # File operations
│   ├── download.c          # Download handling
│   ├── clipboard.c         # Clipboard operations
│   ├── search.c            # Search functionality
│   ├── local_history.c     # History management
│   ├── plotters.c          # Drawing operations
│   └── font.c              # Font handling
├── Resources/
│   └── NetSurf.r           # Resource definitions
└── README.md               # This file
```

## Testing

### In Emulator
Use LaunchAPPL (part of Retro68) to test:
```bash
LaunchAPPL -e classic NetSurf
```

### On Real Hardware
1. Transfer the NetSurf file to your Mac OS 9 system
2. Ensure the file type is set to 'APPL' 
3. Double-click to launch

## Current Limitations

- Network fetching is implemented as a basic stub (returns sample HTML)
- No JavaScript support (NetSurf limitation on resource-constrained systems)
- Limited font support (uses system fonts only)
- Downloads not fully implemented
- Some advanced CSS features may not render correctly

## Extending the Port

### Adding Real Network Support
Replace the stub implementation in `src/fetch.c` with:
- Mac OS 9 Internet Config
- Open Transport networking
- Or classic MacTCP support

### Enhancing Font Support
Modify `src/font.c` and `src/layout.c` to:
- Support TrueType fonts
- Implement better text measurement
- Add font fallback mechanisms

### Adding More Features
The port is structured to easily add:
- Bookmarks management
- Preferences dialog
- Print support
- Navigation history UI

## Contributing

This port follows NetSurf's architecture and coding standards. Key principles:

1. **Separation of Concerns**: GUI code is separate from core NetSurf
2. **Resource Management**: Proper allocation/deallocation of Mac OS resources
3. **Error Handling**: Graceful handling of system errors
4. **Carbon Compliance**: Uses Carbon API for Mac OS X compatibility

## License

This port is licensed under the same terms as NetSurf (GPL v2). The Retro68 toolchain components have their own licenses.

## Acknowledgments

- NetSurf development team for the excellent browser engine
- Wolfgang Thaller for the Retro68 toolchain
- Plan9 port developers for architectural guidance
- Classic Mac OS development community

---

*Built with ❤️ for the classic Macintosh community*
