# Gods Defense

Gods Defense is a homebrew tower defense game for the PlayStation Portable (PSP), inspired by Greek mythology. Defend Olympus from waves of mythic enemies using strategic tower placement and unique abilities. The game supports both single-player and Adhoc multiplayer modes.

## Features

- **Classic Tower Defense Gameplay**: Place and upgrade towers to stop waves of enemies.
- **Mythological Theme**: Battle creatures from Greek mythology, including Cerberus, Cyclops, and more.
- **Multiple Maps**: Play on a variety of maps, each with unique layouts and challenges.
- **MiniMaps**: Preview and select maps with minimap previews.
- **Trophies**: Coming soon!
- **Adhoc Multiplayer**: Play with friends using PSP's Adhoc mode.
- **Custom Graphics and Music**: Enjoy original graphics and background music.
- **Performance Options**: Show FPS, debug info, and memory usage with build flags.

## Getting Started

### Prerequisites

- PSP with custom firmware, or a PSP emulator (e.g., PPSSPP, JPCSP)
- PSP SDK and toolchain for building from source

### Building the Game

1. Clone or download this repository.
2. Ensure you have the PSP toolchain and required libraries installed.
3. Build the project using the provided Makefile:

   ```sh
   cd "PSP Project"
   make
   ```

4. The output EBOOT.PBP will be generated for deployment to your PSP or emulator.

#### Build Flags

- `-DJPCSP_EMULATOR`: Ignore WLAN coding for emulator compatibility
- `-DMEMORY_DEBUG`: Show memory info
- `-D_DEBUG`: Show debug info
- `-DSHOW_FPS`: Show FPS info

You can add these flags to `CXXFLAGS` in the Makefile as needed.

### Running the Game

1. Copy the generated EBOOT.PBP to your PSP's `/PSP/GAME/GodsDefense/` directory.
2. Launch the game from the PSP Game menu or your emulator.

## Project Structure

- `Gods-Defense/` — Xcode project files (for reference)
- `PSP Project/` — Main source code, resources, and build scripts
  - `Include/` — Header files
  - `Src/` — Source files
  - `Res/` — Game resources (graphics, music, maps, etc.)
  - `tinyxml/` — XML parsing library
- `dtd/` — DTD files for map, enemy, and tower definitions
- `Doc/` — Documentation
- `PSD/` — Art assets
- `tools/` — Utility scripts and fonts

## Changelog

See [`PSP Project/Changelog.txt`](PSP%20Project/Changelog.txt) for full details.

## Credits

- **Development**: Dogo
- **Graphics & Music**: See `PSD/` and `Res/` folders
- **Special Thanks**: PSP homebrew community

## License

*Specify your license here (e.g., MIT, GPL, or custom)*

---

For more information, see the documentation in the `Doc/` folder or contact the author.
