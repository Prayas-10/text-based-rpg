# Dharmadeva's Blade — Windows Build

## Build

Use Visual Studio 2026 with the CMake project and configure an MSVC x64 preset.

The project uses:

- C++17
- Windows `winmm.lib` for the existing MCI audio system
- no SFML or other third-party runtime library

## Local signing

The Release executable is signed after a successful build when this file exists:

`C:\LocalDevSigningKey.pfx`

The current local PFX password is:

`Developer123`

The PFX is intentionally not part of the repository.

The CMake file automatically searches for `signtool.exe`. If it cannot find the PFX or signtool, the build continues but emits a warning and leaves the executable unsigned.

For manual signing:

```powershell
.\tools\sign-local.ps1 -ExePath ".\out\build\x64-Release\DharmadevasBlade.exe"
```
