# Fix log

1. UI
   - Removed automatic maximize.
   - Disabled Quick Edit freeze behavior.
   - Preserved normal title-bar/window interaction.
   - Removed full-screen `system("cls")` behavior.
   - Menu redraws in place.
   - Added safe word wrapping.
   - Corrected HP/MP maximums.
   - Added post-prologue RPG layout.

2. Story/prologue
   - Prologue remains cinematic/typewriter-based.
   - Text now advances cleanly after ENTER.
   - Prologue music starts/stops with the prologue only.
   - RPG layout appears after the prologue finishes.

3. Audio
   - Background music and event effects now use separate MCI aliases.
   - Battle effects no longer replace chapter music.
   - Chapter music is scoped to the active chapter.

4. Windows application identity
   - Added executable icon.
   - Added application manifest.
   - Added local development code-signing helper.

5. Build
   - CMake now includes the Windows resource file.
   - `winmm` is linked explicitly.
   - Game data is copied beside the executable.
