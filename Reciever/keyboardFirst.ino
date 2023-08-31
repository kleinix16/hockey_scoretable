#include <Keyboard.h>

char receivedData; // Premenná pre uloženie prijatých dát zo sériovej linky
const long baudRate = 9600;  // Baud rate for the serial communication


void setup() {
  Serial.begin(9600);   // Inicializácia sériovej komunikácie s HC-12
  Keyboard.begin();     // Inicializácia knižnice Keyboard

  // Start the software serial connection
  Serial1.begin(baudRate);
  Serial.println("-START-");
}

void loop2() {
  Serial.println("-START-");
  Serial1.println("-START-");
  delay(1000);
}

void loop() {
  // Kontrola, či niečo prišlo zo sériovej linky
  if (Serial1.available() > 0) {
    receivedData = Serial1.read(); // Načítanie prijatých dát
    Serial.print("RECIEVED: ");
    Serial.println(receivedData);

    // Ovládanie klávesnice na základe prijatých dát
    switch (receivedData) {
      case '1':
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_F5);
        Serial.println("CTRL + F5");
        //delay(100); // Môžete upraviť dobu oneskorenia podľa potreby
        Keyboard.releaseAll();
        break;
      case '2':
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_F6);
        Serial.println("CTRL + F6");
        //delay(100); // Môžete upraviť dobu oneskorenia podľa potreby
        Keyboard.releaseAll();
        break;
      case '3':
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_F7);
        Serial.println("CTRL + F7");
        //delay(100); // Môžete upraviť dobu oneskorenia podľa potreby
        Keyboard.releaseAll();
        break;
      case '4':
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_F8);
        Serial.println("CTRL + F8");
        //delay(100); // Môžete upraviť dobu oneskorenia podľa potreby
        Keyboard.releaseAll();
        break;
      default:
        Serial.println("UNKNOWN");
        break;
    }
  }
}