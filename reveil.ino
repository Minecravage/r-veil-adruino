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
  else {
    Serial.println("RTC fonctionne") ;
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

    while(digitalRead(2) == 1){}

    // Déclaration des variables globales
    byte heure_r = 0;
    byte minute_r = 0;
    byte seconde_r = 0;
    byte state = 1;
    lcd.clear() ;

    while (true) {
        

      // Si on appuie sur le +
      if (digitalRead(4) == 1) {

        // Si on règle les secondes
        if (state == 1) {
          seconde_r += 1;
          if (seconde_r >= 60) {
            seconde_r = 0;
          }
        }

        // Si on règle les minutes
        if (state == 2) {
          minute_r += 1;
          if (minute_r >= 60) {
            minute_r = 0;
          }
        }

        // Si on règle les heures
        if (state == 3) {
          heure_r += 1;
          if (heure_r >= 24) {
            heure_r = 0;
          }
        }
      }

        byte heure_n = heure_r;
        byte minute_n = minute_r;
        byte seconde_n = seconde_r;

      // Si on appuie sur le -
      if (digitalRead(5) == 1) {

        // Si on règle les secondes
        if (state == 1) {
          seconde_r -= 1;
          if (seconde_r < 60) {
            seconde_r = 59;
          }
        }

        // Si on règle les minutes
        if (state == 2) {
          minute_r -= 1;
          if (minute_r < 0) {
            minute_r = 59;
          }
        }

        // Si on règle les heures
        if (state == 3) {
          heure_r -= 1;
          if (heure_r == 0) {
            heure_r = 23;
          }
        }
        byte heure_n = heure_r;
        byte minute_n = minute_r;
        byte seconde_n = seconde_r;
      }

      // Si on appuie sur le changement de state
      if (digitalRead(2) == 1) {
        if (state > 4) {
          DateTime now = rtc.now();
          rtc.adjust(DateTime(now.year(), now.month(), now.day(), heure_r, minute_r, seconde_r));
          byte state = 0;
          break;
        }
        else {
          state += 1;
        }
      }
    if (seconde_n == seconde_r && minute_n == minute_r && heure_r == heure_n) {
        lcd.clear();
        lcd.home();
        lcd.print("réglage");

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
