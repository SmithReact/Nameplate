# Nameplate for Ashita 4.30

> Unofficial Ashita 4.30 port of
> [Shirk/Nameplate](https://github.com/Shirk/Nameplate), based on upstream
> `v0.5.1.0d`. The original project is archived; this fork preserves its
> behavior while restoring compatibility with the current Ashita plugin API.

[Download the latest tested build](https://github.com/SmithReact/Nameplate/releases/latest)
or see [ASHITA4-PORT.md](ASHITA4-PORT.md) for compatibility, installation,
and build details.

Nameplate is a plugin for [Ashita v4](https://github.com/AshitaXI/Ashita-v4beta) and [Windower 4](https://www.windower.net/) that corrects XI's nameplate aspect ratio.

With this plugin, nameplates will be less blurry and the same size regardless of window size: no more stretched nameplates or having to download hacked DAT files.

## Before and after

| Before: stretched and blurry | After: corrected proportions |
| --- | --- |
| ![A stretched FFXI character nameplate before loading Nameplate](docs/images/nameplate-before.png) | ![The same FFXI character nameplate with corrected proportions after loading Nameplate](docs/images/nameplate-after.png) |

## Installation for Ashita v4 users

1. Download and extract the [latest tested build](https://github.com/SmithReact/Nameplate/releases/latest).
2. Copy `Nameplate.dll` directly into Ashita's `plugins` directory. The final path must be `Ashita\plugins\Nameplate.dll`.
3. Do **not** place the DLL inside a separate `Nameplate` subfolder.
4. Start FFXI and run `/load Nameplate`.

Make sure the plugin api version matches the Ashita 4 api version.
This port requires ***Ashita 4 interface 4.30*** and a 32-bit FFXI client.

## Usage for Ashita v4 users

`/load Nameplate` to load the plugin.  `/nameplate help` to read the
in-game command help.

The font size can be configured via the `FontSizeInPx` setting in
`config\nameplate\defaults.ini`.

The damage font size can be configured via the `DamageFontSizeInPx` setting in
`config\nameplate\defaults.ini`.

Job Mastery stars can be hidden by setting `HideStars=1` in the configuration.

Nameplate visibility modes can be changed via the `NameMode` setting.

Changes apply immediately but are not autosaved. Run `/nameplate save` to
persist them to `config\nameplate\defaults.ini`; `/nameplate load` discards
unsaved changes and reloads that file.

### Complete Ashita command reference

| Command | Description |
| --- | --- |
| `/load Nameplate` | Load the plugin through Ashita. |
| `/unload Nameplate` | Unload the plugin and restore the patched game bytes. |
| `/nameplate help` | Show the in-game command reference. |
| `/nameplate load` | Reload `config\nameplate\defaults.ini`. |
| `/nameplate save` | Save the current settings to `config\nameplate\defaults.ini`. |
| `/nameplate fontsize <1-256>` | Set the nameplate font size in pixels. |
| `/nameplate fontsizeinpx <1-256>` | Alias of `fontsize`. |
| `/nameplate damagefontsize <1-256>` | Set the damage-number font size in pixels. |
| `/nameplate damagefontsizeinpx <1-256>` | Alias of `damagefontsize`. |
| `/nameplate dmgfontsize <1-256>` | Short alias of `damagefontsize`. |
| `/nameplate hidestars` | Hide Job Mastery stars. |
| `/nameplate showstars` | Show Job Mastery stars. |
| `/nameplate mode all` | Show every nameplate. |
| `/nameplate mode none` | Hide every nameplate. |
| `/nameplate mode hideself` | Hide only your own nameplate. |
| `/nameplate mode hidepc` | Hide player nameplates except charmed players; keep yours visible. |
| `/nameplate mode hidepcself` | Hide player nameplates except charmed players, and hide yours. |
| `/nameplate mode hidenpc` | Hide non-player nameplates; keep yours visible. |
| `/nameplate mode hidenpcself` | Hide non-player nameplates and hide yours. |

Plugin commands are case-insensitive. The parser accepts both `/nameplate`
and `//nameplate`; the single-slash Ashita form shown above is recommended.

## Installation for Windower 4 users

***Please report any and all issues with this plugin on the [Nameplate Issues](https://github.com/Shirk/Nameplate/issues) tracker. This is the *only* valid location to get any support or assistance for this plugin.***

Copy `plugins\Nameplate.dll` to `<***Windower 4 Folder***>\plugins\Nameplate.dll`

This version of Nameplate is compatible with the current version of Windower 4.

## Usage for Windower 4 users

***Please report any and all issues with this plugin on the [Nameplate Issues](https://github.com/Shirk/Nameplate/issues) tracker. This is the *only* valid location to get any support or assistance for this plugin.***

`//load Nameplate` to load the plugin.  `//nameplate help` to read the
in-game command help.

The font size can be configured via the `FontSizeInPx` setting in
`plugins\settings\nameplate\defaults.ini`.

The damage font size can be configured via the `DamageFontSizeInPx` setting in
`plugins\settings\nameplate\defaults.ini`.

Job Mastery stars can be hidden by setting `HideStars=1` in the configuration.

Nameplate visibility modes can be changed via the `NameMode` setting.

The configuration file is not autosaved when changing these settings in-game. The configuration
file can be saved and loaded by using the `//nameplate save` and `//nameplate load` commands.

| command                               | description                                                                        |
|---------------------------------------|------------------------------------------------------------------------------------|
| //nameplate help                      | You're reading it!                                                                 |
| //nameplate load                      | Load configuration from `plugins\settings\nameplate\defaults.ini`                  |
| //nameplate save                      | Save current configuration to `plugins\settings\nameplate\defaults.ini`            |
| //nameplate fontsize `<number>`       | Set the nameplate font size to `<number>` pixels                                   |
| //nameplate damagefontsize `<number>` | Set the damage font size to `<number>` pixels                                      |
| //nameplate hidestars                 | Hide all Job Mastery stars                                                         |
| //nameplate showstars                 | Re-enable displaying Job Mastery stars                                             |
| //nameplate mode all                  | Show all nameplates                                                                |
| //nameplate mode none                 | Hide all nameplates                                                                |
| //nameplate mode hideself             | Hide your own nameplate                                                            |
| //nameplate mode hidepc               | Hide all player nameplates, except when charmed                                    |
| //nameplate mode hidepcself           | Hide all player nameplates, except when charmed, but also always keep yours hidden |
| //nameplate mode hidenpc              | Hide all non-player nameplates                                                     |
| //nameplate mode hidenpcself          | Hide all non-player nameplates, but also always keep yours hidden                  |

## For more information

- [Ashita 4 port repository](https://github.com/SmithReact/Nameplate)
- [Ashita 4 port issues](https://github.com/SmithReact/Nameplate/issues)
- [Original archived project](https://github.com/Shirk/Nameplate)
- [Previous Homepage](https://ffxi.somepage.org/Nameplate/)
- [Changelog](./CHANGELOG.md)

## License

Nameplate is available under the [GNU General Public License, Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html).
The complete corresponding source for the distributed DLL is maintained in
this repository. See [LICENSE.md](LICENSE.md), [NOTICE.md](NOTICE.md), and
[ASHITA4-PORT.md](ASHITA4-PORT.md).

## Legal

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
