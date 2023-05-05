#include <LiquidCrystal.h>

#define RS 6
#define enable 7
#define D7 2
#define D6 3
#define D5 4
#define D4 5
#define trig A1
#define echo A0
#define Buzzer 8

int Distancia;
int Duracion;
int conteo = 0;
int Fre = 440;

LiquidCrystal LCD_Roberto(RS, enable, D4, D5, D6, D7);

byte umpalumpas1[] = {
  B01110,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};

byte umpalumpas2[] = {
  B01110,
  B11111,
  B01110,
  B01110,
  B00100,
  B11111,
  B01010,
  B01010
};

void configurarPines() {
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(Buzzer, OUTPUT);
}

void configurarLCD() {
  LCD_Roberto.begin(16, 2);
  LCD_Roberto.setCursor(0, 0);
  LCD_Roberto.print("Num de umpalumpas");
  LCD_Roberto.setCursor(0, 0);
  LCD_Roberto.createChar(1, umpalumpas1);
  LCD_Roberto.createChar(2, umpalumpas2);
}

void setup() {
  configurarPines();
  configurarLCD();
}

void loop() {
  LCD_Roberto.write(1);
  LCD_Roberto.write(2);

  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  Duracion = pulseIn(echo, HIGH);
  Distancia = Duracion / 59;
  Serial.println(Distancia);
  delay(500);

  if (Distancia > 0 && Distancia < 10) {
    conteo = incrementarConteo(conteo);
  }

  actualizarDisplay(conteo);
  reproducirBuzzer(conteo);
}

int incrementarConteo(int conteoActual) {
  return conteoActual + 1;
}

void actualizarDisplay(int conteoActual) {
  if (conteoActual < 16) {
    int columna = 0;
    int i = 0;
    while (i < conteoActual) {
      if (columna == 0) {
        LCD_Roberto.setCursor(i, 1);
        LCD_Roberto.write(1);
        columna = 1;
        i++;
      } else if (columna == 1) {
        LCD_Roberto.setCursor(i, 1);
        LCD_Roberto.write(2);
        columna = 0;
        i++;
      }
    }
    for (i = i; i < 16; i++) {
      LCD_Roberto.setCursor(i, 1);
      LCD_Roberto.write(' ');
    }
  } else {
    LCD_Roberto.setCursor(15, 1);
    LCD_Roberto.write(2);
    delay(600);
    LCD_Roberto.setCursor(15, 1);
    LCD_Roberto.write(1);
    delay(600);
  }
}

void reproducirBuzzer(int conteoActual) {
  if (conteoActual >= 16) {
    tone(Buzzer, Fre, 440);
  } else {
    noTone(Buzzer);
  }
}
