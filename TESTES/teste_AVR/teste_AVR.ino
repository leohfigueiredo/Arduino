#include <Arduino.h>
#include <LiquidCrystal.h>

#include <util/delay.h>

extern "C" {
    #include <os.h>
}

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

spinlock_t testLock;

void kernel_task(void *arg) {
    while(1) {
        spinlock_acquire(&testLock);
        lcd.setCursor(0, 0);
        lcd.print("kernel: " + String((long)os_get_uptime()));
        spinlock_release(&testLock);
        os_sleep(1000);
    }
}

void user_task(void *arg) {
    int x = 0;
    while(1) {
        spinlock_acquire(&testLock);
        lcd.setCursor(0, 1);
        lcd.print("user_task: " + String(x++));
        spinlock_release(&testLock);
        os_sleep(5000);
    }
}

void setup() {
    os_init();
    lcd.begin(16, 2);
    lcd.print("Starting up...");
}

void loop() {
    spinlock_init(&testLock);

    os_schedule_task(kernel_task, NULL, 0);
    os_schedule_task(user_task, NULL, 0);
    lcd.clear();
    os_loop(); 
}
