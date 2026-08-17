# Nameplate for Ashita 4.30

This is an unofficial Ashita 4.30 port of Shirk/BunnyBox Productions' Nameplate v0.5.1.0d plugin for Final Fantasy XI.

Original project: <https://github.com/Shirk/Nameplate>

Port repository: <https://github.com/SmithReact/Nameplate>

## Compatibility

- Ashita interface: 4.30
- Architecture: 32-bit/x86
- Tested with Ashita 4.3.0.0 and SDK interface 4.30
- Tested in game on August 16, 2026 with `FFXiMain.dll` SHA-256 `6F8844EB7F0380F30A3DB2FC3C435E1145F5C450BDD0999133CC75C516EC3C3B`

Nameplate modifies FFXI's in-memory rendering code using byte signatures. A future FFXI update can invalidate those signatures. If the plugin stops loading after a game update, unload it and check for an updated build before using it again.

## Installation

1. Close FFXI.
2. Back up any existing `Ashita\plugins\Nameplate.dll`.
3. Extract this archive into the Ashita installation directory. The DLL must end up at `Ashita\plugins\Nameplate.dll`.
4. Start FFXI and run `/load nameplate` if the plugin is not already loaded by a startup script.

On a successful load, the Ashita log and in-game chat report:

```text
[Nameplate] Ashita 4.30 port loaded; rendering patches are enabled.
```

Configuration is stored in `Ashita\config\nameplate\defaults.ini`.

## Commands

```text
/nameplate help
/nameplate load
/nameplate save
/nameplate fontsize <1-256>
/nameplate damagefontsize <1-256>
/nameplate hidestars
/nameplate showstars
/nameplate mode all
/nameplate mode none
/nameplate mode hideself
/nameplate mode hidepc
/nameplate mode hidepcself
/nameplate mode hidenpc
/nameplate mode hidenpcself
```

## Port changes

- Added Ashita 4's required `expDestroyPlugin` export and object destruction path.
- Compiles against the current Ashita 4.30 SDK and reports interface 4.30.
- Preserves the original command callbacks, configuration format, entity offsets, rendering behavior, and native FFXI patch approach.
- Replaced the C++ module-based signature scanner with a conventional C++20 header implementation that scans committed executable regions and supports live match diagnostics.
- Added a diagnostic-only build mode with all game-code writes disabled.
- Restricted the distributed DLL to the three current Ashita plugin exports.
- Added a reproducible 32-bit MSVC CMake configuration.

The two live `GetFrameDelta` matches in the tested client are identical stubs 0x30 bytes apart. Both reference the same pointer slot and live game object; the plugin preserves the original first-match behavior.

## Building from source

Requirements:

- A 32-bit-capable MSVC toolchain
- CMake 3.22 or newer
- The current Ashita 4 `plugins/sdk` directory

The SDK is a build dependency and is not redistributed by this repository.
The initial public release was built against Ashita interface 4.30.

Functional release build:

```powershell
cmake -S . -B build -A Win32 `
  -DASHITA_SDK_PATH="C:\path\to\Ashita\plugins\sdk" `
  -DNAMEPLATE_ENABLE_PATCHES=ON
cmake --build build --config Release
```

For a safe signature-reporting build that does not modify FFXI memory, omit `-DNAMEPLATE_ENABLE_PATCHES=ON`. Diagnostic mode is the default.

## License

Nameplate is distributed under the GNU General Public License version 3. See `LICENSE.md`. The corresponding port source is included in this archive.
