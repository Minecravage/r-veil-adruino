#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  // Commencer à afficher dans la console
  Serial.begin(9600);

  // Définition des boutons
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);

  // Setup de la clock
  if (! rtc.begin()) {
    Serial.println("RTC n'est pas branchée");
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC ne fonctionne pas");
  }


  // Setup de LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Par Elise");
  lcd.setCursor(0, 1);
  lcd.print("Et Aurelien");

  // Attente, effacement et démarrage
  delay(3000);
  lcd.clear();
}

String formater_heure() {

  // Chopper l'heure
  DateTime now = rtc.now();

  // Formatage
  return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

}

void loop() {

  String heure = formater_heure();
  String precedent_heure = heure;

  if (digitalRead(2) == 1) {

    short int heure_r = 0;
    short int minute_r = 0;
    short int seconde_r = 0;
    short int state = 1;
    lcd.clear() ;

    while (true) {
      if (digitalRead(4) == 1) {
        if (state == 1) {
          seconde_r =+ 1;
          if (seconde_r >= 60) {
            seconde_r = 0;
          }
        }
        if (state == 2) {
          minute_r =+ 1;
          if (minute_r >= 60) {
            minute_r = 0;
          }
        }
        if (state == 3) {
          heure_r =+ 1;
          if (heure_r >= 24) {
            heure_r = 0;
          }
        }
      }
      if (digitalRead(5) == 1) {
        
      }
      if (digitalRead(2) == 1) {
        
    }

    }

  }

  while (true) {
    if (precedent_heure != formater_heure()) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(heure);
      precedent_heure = heure;
      break;
    }
  }
}