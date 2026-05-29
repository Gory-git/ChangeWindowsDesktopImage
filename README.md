# T-Dongle-S3_Desktop_Modifier

Firmware per LilyGo T-Dongle-S3 che emula una tastiera HID e avvia uno script PowerShell per cambiare lo sfondo di Windows.

ATTENZIONE: questo progetto può modificare computer remoti. Usalo solo su macchine di tua proprietà o con il consenso esplicito del proprietario. Testalo esclusivamente in ambiente controllato (macchina virtuale o laboratorio). L'autore non si assume responsabilità per usi impropri.

## Contenuto del repository

- `src/` - codice firmware (ESP32-S3 HID keyboard)
- `scripts/` - script PowerShell usati dallo payload (`bootstrap.ps1`, `Set-Wallpaper.ps1`, `Register-WallpaperTask.ps1`, ...)
- `platformio.ini` - configurazione PlatformIO per compilare e flashare il firmware

## Come funziona (breve)

Il firmware emula una tastiera USB. All'accensione apre la finestra Esegui di Windows e invia un comando PowerShell che scarica ed esegue `bootstrap.ps1` ospitato su GitHub. Il payload PowerShell scarica e imposta un'immagine come sfondo.

Per motivi di sicurezza e trasparenza:

- il comando da inviare è definito in `src/main.cpp` nella costante `URL`;
- puoi e DEVI personalizzare l'URL per puntare a uno script di test sotto il tuo controllo.

## Build e flash (sviluppo)

Prerequisiti: `PlatformIO` (estensione VS Code o CLI), driver per la board LilyGo T-Dongle-S3.

Esempio con PlatformIO CLI:

```powershell
# Compila
pio run

# Compila e carica (sostituisci <env> con l'environment corretto se necessario)
pio run -e <env> -t upload
```

Nell'IDE VS Code: apri la cartella, seleziona `PlatformIO > Build` o `Upload` dalla barra di PlatformIO.

## Personalizzazione

- Modifica `src/main.cpp` per cambiare il comando digitato (variabile `URL`).
- Modifica o ospita localmente gli script in `scripts/` se vuoi testare senza dipendere da Internet.

Esempio utile: sostituire l'URL con un comando che apra un prompt di testo locale invece di scaricare script remoti quando fai i test.

## Test consigliati (sicurezza)

- Esegui i test solo su una VM Windows o su un PC di laboratorio.
- Isola la rete o usa una VM snapshot per poter ripristinare lo stato.
- Verifica il comportamento del payload eseguendo prima lo script PowerShell manualmente per vedere cosa fa.

## Etica e responsabilità

Non distribuire né usare questo progetto su dispositivi altrui senza permesso esplicito. Non usare per scopi di intrusione, danno o molestia. Utilizza questo repository solo a scopo didattico e di ricerca legittima.

## Licenza

Questo repository è rilasciato sotto licenza MIT.

## Contatti

Per domande o migliori pratiche su test e sicurezza, scrivi qui (o apri un issue nel repository).
