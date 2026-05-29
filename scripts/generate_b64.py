import base64

# ── Modifica questi valori ─────────────────────────────────────────────────────
GITHUB_RAW_BASE  = "https://raw.githubusercontent.com/Gory-git/ChangeWindowsDesktopImage/main/scripts"
SCRIPT_WALLPAPER = "Set-Wallpaper.ps1"
SCRIPT_TASK      = "Register-WallpaperTask.ps1"
# ──────────────────────────────────────────────────────────────────────────────

url1 = f"{GITHUB_RAW_BASE}/{SCRIPT_WALLPAPER}"
url2 = f"{GITHUB_RAW_BASE}/{SCRIPT_TASK}"

ps_command = (
    f'$s="$env:USERPROFILE\\Scripts";'
    f'New-Item $s -ItemType Directory -Force | Out-Null;'
    f'Invoke-WebRequest "{url1}" -OutFile "$s\\{SCRIPT_WALLPAPER}";'
    f'Invoke-WebRequest "{url2}" -OutFile "$s\\{SCRIPT_TASK}";'
    f'Start-Process powershell.exe '
    f'-ArgumentList "-ExecutionPolicy Bypass -WindowStyle Hidden -File \\"$s\\{SCRIPT_TASK}\\"" '
    f'-Wait'
)

encoded = base64.b64encode(ps_command.encode("utf-16-le")).decode("ascii")

print("=" * 60)
print("Copia questa riga in main.cpp come ENCODED_CMD:")
print("=" * 60)
print(f'static const char ENCODED_CMD[] = "{encoded}";')
