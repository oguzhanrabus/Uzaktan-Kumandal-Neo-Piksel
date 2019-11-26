#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>  //piksel Kütüphanesi
#include <IRremote.h> //Uzaktan kumanda Kütüphanesi

#define NEO_PIN 2 //piksel DI ucu Arduino 2 nolu pinine bağlı
#define IR_PIN 3  //Infared alıcı data ucu Arduino 3 nolu pinine bağlı
#define pikselsayisi 12 //piksel led sayısı
Adafruit_NeoPixel piksel = Adafruit_NeoPixel(pikselsayisi, NEO_PIN, NEO_GRB + NEO_KHZ800);

IRrecv irrecv(IR_PIN);
decode_results results;

#define BUTON1 16752735 // Parlalık Artır Butonu
#define BUTON2 16720095 // Parlalık Azalt Butonu
#define BUTON3 16736415 // Off Butonu
#define BUTON4 16769055 // On Butonu
#define BUTON5 16748655 // R Butonu
#define BUTON6 16716015 // G Butonu
#define BUTON7 16732335 // B Butonu
#define BUTON8 16764975 // W Butonu
#define BUTON9 16756815 // Kırmızı Butonu
#define BUTON10 16724175 // Yeşil Butonu
#define BUTON11 16740495 // Mavi Butonu
#define BUTON12 16773135 // Flash Butonu
#define BUTON13 16754775 // Turuncu Butonu
#define BUTON14 16722135 // Açık Mavi Butonu
#define BUTON15 16738455 // Mor Butonu
#define BUTON16 16771095 // Strobe Butonu
#define BUTON17 16750695 // Turuncu Butonu
#define BUTON18 16718055 // Mavi Butonu
#define BUTON19 16734375 // Mor Butonu
#define BUTON20 16767015 // Fade Butonu
#define BUTON21 16746615 // Sarı Butonu
#define BUTON22 16713975 // Mavi Butonu
#define BUTON23 16730295 // Pembe Butonu
#define BUTON24 16762935 // Smooth Butonu

int ledon = 4; //on/off ledi Arduino 4 nolu pinine bağlı
int parmax = 6;
int kirmizi = 0;
int yesil = 0;
int mavi = 0;
int parlaklik = EEPROM.read(0); //Başlangıçtaki parlaklık seviyesi

void setup() {
  piksel.begin();
  piksel.show();
  irrecv.enableIRIn();
  pinMode(ledon, OUTPUT);
  pinMode(parmax, OUTPUT);
}
void loop() {
  piksel.setBrightness(EEPROM.read(0));
  if (irrecv.decode(&results))
   //----------on (Buton-4)----------
  if ((results.value == BUTON4) && (digitalRead(ledon) == LOW))
  {
    digitalWrite(ledon, HIGH);
  }
    //----------Off (Buton-3)----------

  if ((results.value == BUTON3) && (digitalRead(ledon) == HIGH))
  {
    digitalWrite(ledon, LOW);
    piksel.clear();
    piksel.show();
  }
    //----------Parlaklık Ayar (Buton-1 & Buton-2)----------
  {
    if ((results.value == BUTON1) && (digitalRead(ledon) == HIGH)) //Artırma

      parlaklik += 25;
    if (parlaklik > 255) {
      parlaklik = 255;
    }
    if ((results.value == BUTON2) && (digitalRead(ledon) == HIGH)) //Düşürme

      parlaklik -= 25;
    if (parlaklik < 0) {
      parlaklik = 0;
    }
     if (parlaklik >= 250)
  {
    digitalWrite(parmax, HIGH);
  }
  else
  {
    digitalWrite(parmax, LOW);
  }
    EEPROM.write(0, parlaklik);
  }
  //----------Kırmızı (Buton-5)----------

  if ((results.value == BUTON5) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 255, 0, 0);
      piksel.setPixelColor(2, 0, 255, 0);
      piksel.setPixelColor(6, 0, 255, 0);
      piksel.setPixelColor(8, 0, 255, 0);
      piksel.show();
    }
  //----------yeşil (Buton-6)----------

  if ((results.value == BUTON6) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 0, 255, 0);
      piksel.setPixelColor(2, 255, 0, 0);
      piksel.setPixelColor(6, 255, 0, 0);
      piksel.setPixelColor(8, 255, 0, 0);
      piksel.show();
    }
  //----------mavi (Buton-7)----------

  if ((results.value == BUTON7) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 0, 0, 255);
      piksel.show();
    }
  //----------beyaz (Buton-8)----------

  if ((results.value == BUTON8) && (digitalRead(ledon) == HIGH))
  {
    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 255, 255, 255);
      piksel.show();
    }
  }
  //----------döner kırmızı (Buton-9)----------

  if ((results.value == BUTON9) && (digitalRead(ledon) == HIGH))
  {
    for (int i = 0; i < pikselsayisi; i ++)

      if (i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 7 || i == 9 || i == 10 || i == 11 )
      {
        piksel.setPixelColor(i, 255, 0, 0);
        piksel.show();
        delay(50);
      }
      else  if  (i == 2 || i == 6 || i == 8)
      {
        piksel.setPixelColor(i, 0, 255, 0);
        piksel.show();
        delay(50);
      }
    for (int i = 0; i <  pikselsayisi; i++)
    {
      piksel.setPixelColor(i, 0, 0, 0);
      piksel.show();
      delay(50);
    }
  }
  //----------döner yeşil (Buton-10)----------

  if ((results.value == BUTON10) && (digitalRead(ledon) == HIGH))
  {
    for (int i = 0; i < pikselsayisi; i ++)

      if (i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 7 || i == 9 || i == 10 || i == 11 )
      {
        piksel.setPixelColor(i, 0, 255, 0);
        piksel.show();
        delay(50);
      }
      else  if  (i == 2 || i == 6 || i == 8)
      {
        piksel.setPixelColor(i, 255, 0, 0);
        piksel.show();
        delay(50);
      }
    for (int i = 0; i <  pikselsayisi; i++)
    {
      piksel.setPixelColor(i, 0, 0, 0);
      piksel.show();
      delay(50);
    }
  }
  //----------döner mavi (Buton-11)----------

  if ((results.value == BUTON11) && (digitalRead(ledon) == HIGH))
  {
    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 0, 0, 255);
      piksel.show();
      delay(50);
    }
    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 0, 0, 0);
      piksel.show();
      delay(50);
    }
  }
  //----------Flash (Buton-12)----------

  if ((results.value == BUTON12) && (digitalRead(ledon) == HIGH))
  {
    for (int i = 0; i < pikselsayisi; i ++)

      if (i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 7 || i == 9 || i == 10 || i == 11 )
      {
        piksel.setPixelColor(i, 255, 0, 0);
        piksel.show();
        delay(50);
      }
      else  if  (i == 2 || i == 6 || i == 8)
      {
        piksel.setPixelColor(i, 0, 255, 0);
        piksel.show();
        delay(50);
      }

    for (int i = 0; i < pikselsayisi; i ++)

      if (i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 7 || i == 9 || i == 10 || i == 11 )
      {
        piksel.setPixelColor(i, 0, 255, 0);
        piksel.show();
        delay(50);
      }
      else  if  (i == 2 || i == 6 || i == 8)
      {
        piksel.setPixelColor(i, 255, 0, 0);
        piksel.show();
        delay(50);
      }

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 0, 0, 255);
      piksel.show();
      delay(50);
    }
  }
  //----------Turuncu (Buton-13)----------

  if ((results.value == BUTON13) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 255, 165, 0);
      piksel.setPixelColor(2, 165, 255, 0);
      piksel.setPixelColor(6, 165, 255, 0);
      piksel.setPixelColor(8, 165, 255, 0);
      piksel.show();
    }
  //----------Mavi-1 (Buton-14)----------

  if ((results.value == BUTON14) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 0, 255, 255);
      piksel.setPixelColor(2, 255, 0, 255);
      piksel.setPixelColor(6, 255, 0, 255);
      piksel.setPixelColor(8, 255, 0, 255);
      piksel.show();
    }
  //----------Mor (Buton-15)----------

  if ((results.value == BUTON15) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 102, 0, 102);
      piksel.setPixelColor(2, 0, 102, 102);
      piksel.setPixelColor(6, 0, 102, 102);
      piksel.setPixelColor(8, 0, 102, 102);
      piksel.show();
    }
  //----------Strobe (Buton-16)----------

  if ((results.value == BUTON16) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i++) {
      piksel.setPixelColor(i, random(255), random(255), random(255));
      piksel.show();
      delay(25);
    }
  //----------Turuncu (Buton-17)----------

  if ((results.value == BUTON17) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 255, 178, 102);
      piksel.setPixelColor(2, 178, 255, 102);
      piksel.setPixelColor(6, 178, 255, 102);
      piksel.setPixelColor(8, 178, 255, 102);
      piksel.show();
    }
  //----------Mavi-2  (Buton-18)-----------

  if ((results.value == BUTON18) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 51, 153, 255);
      piksel.setPixelColor(2, 153, 51, 255);
      piksel.setPixelColor(6, 153, 51, 255);
      piksel.setPixelColor(8, 153, 51, 255);
      piksel.show();
    }

  //----------Açık Mor (Buton-19)----------

  if ((results.value == BUTON19) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 204, 0, 204);
      piksel.setPixelColor(2, 0, 204, 204);
      piksel.setPixelColor(6, 0, 204, 204);
      piksel.setPixelColor(8, 0, 204, 204);
      piksel.show();
    }
  //----------Fade (Buton-20)----------

  if ((results.value == BUTON20) && (digitalRead(ledon) == HIGH))
  {
    theaterChase(piksel.Color(127, 127, 127), 50);
    theaterChase(piksel.Color(127,   0,   0), 50);
    theaterChase(piksel.Color(  0,   0, 127), 50);
    theaterChaseRainbow(50);
  }
  //----------Sarı (Buton-21)----------

  if ((results.value == BUTON21) && (digitalRead(ledon) == HIGH))
  {
    for (int i = 0; i < pikselsayisi; i ++)
      piksel.setPixelColor(i, 255, 255, 0);
    piksel.show();
  }
  //----------Mavi-3 (Buton-22)----------

  if ((results.value == BUTON22) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 0, 128, 255);
      piksel.setPixelColor(2, 128, 0, 255);
      piksel.setPixelColor(6, 128, 0, 255);
      piksel.setPixelColor(8, 128, 0, 255);
      piksel.show();
    }
  //----------Pembe (Buton-23)----------

  if ((results.value == BUTON23) && (digitalRead(ledon) == HIGH))

    for (int i = 0; i < pikselsayisi; i ++)
    {
      piksel.setPixelColor(i, 255, 31, 153);
      piksel.setPixelColor(2, 31, 255, 153);
      piksel.setPixelColor(6, 31, 255, 153);
      piksel.setPixelColor(8, 31, 255, 153);
      piksel.show();
    }
  //----------Smooth (Buton-24)----------
  //
  if ((results.value == BUTON24) && (digitalRead(ledon) == HIGH))
  {
    rainbow(10);
  }
  //--------------------------------------------------------
  {
    irrecv.resume();
    delay(250);
  }
}
void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 3; b++) {
      piksel.clear();
      for (int c = b; c < piksel.numPixels(); c += 3) {
        piksel.setPixelColor(c, color);
      }
      piksel.show();
      delay(wait);
    }
  }
}
void rainbow(int wait) {

  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < piksel.numPixels(); i++) {

      int pixelHue = firstPixelHue + (i * 65536L / piksel.numPixels());
      piksel.setPixelColor(i, piksel.gamma32(piksel.ColorHSV(pixelHue)));
    }
    piksel.show();
    delay(wait);
  }
}
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;
  for (int a = 0; a < 30; a++) {
    for (int b = 0; b < 3; b++) {
      piksel.clear();

      for (int c = b; c < piksel.numPixels(); c += 3) {

        int      hue   = firstPixelHue + c * 65536L / piksel.numPixels();
        uint32_t color = piksel.gamma32(piksel.ColorHSV(hue));
        piksel.setPixelColor(c, color);
      }
      piksel.show();
      delay(wait);
      firstPixelHue += 65536 / 90;
    }
  }
}
