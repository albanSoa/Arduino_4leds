// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // Cette librairie permet la communication avec les périphériques I2C.

const int MPU_ADDR = 0x68; // Adresse I2C du MPU-6050. Si la broche AD0 est à HIGH, l'adresse devient 0x69.

int16_t accelerometre_x, accelerometre_y, accelerometre_z; // Variables pour les données brutes de l'accéléromètre
int16_t gyroscope_x, gyroscope_y, gyroscope_z; // Variables pour les données brutes du gyroscope
int16_t temperature; // Variable pour la température

#define LED_LB 2 // LED en bas à gauche
#define LED_RB 3 // LED en bas à droite
#define LED_RT 4 // LED en haut à droite
#define LED_LT 5 // LED en haut à gauche

char tmp_str[7]; // Variable temporaire utilisée pour convertir les entiers en chaînes

// Fonction de conversion d'un int16_t en chaîne de caractères
char* convertir_int16_en_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_LB, OUTPUT);
  pinMode(LED_RB, OUTPUT);
  pinMode(LED_RT, OUTPUT);
  pinMode(LED_LT, OUTPUT);
  digitalWrite(LED_LB, LOW);
  digitalWrite(LED_RB, LOW);
  digitalWrite(LED_RT, LOW);
  digitalWrite(LED_LT, LOW);
  
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Registre PWR_MGMT_1
  Wire.write(0); // Mettre à zéro pour sortir du mode veille
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Commencer à lire à partir du registre 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // Demander 14 octets (7 valeurs de 2 octets)

  // Lecture des valeurs de l'accéléromètre
  accelerometre_x = Wire.read() << 8 | Wire.read();
  accelerometre_y = Wire.read() << 8 | Wire.read();
  accelerometre_z = Wire.read() << 8 | Wire.read();
  
  // Lecture de la température
  temperature = Wire.read() << 8 | Wire.read();
  
  // Lecture des valeurs du gyroscope
  gyroscope_x = Wire.read() << 8 | Wire.read();
  gyroscope_y = Wire.read() << 8 | Wire.read();
  gyroscope_z = Wire.read() << 8 | Wire.read();

  // Affichage des données sur le moniteur série
  Serial.print("aX = "); Serial.print(convertir_int16_en_str(accelerometre_x));
  Serial.print(" | aY = "); Serial.print(convertir_int16_en_str(accelerometre_y));
  Serial.print(" | aZ = "); Serial.print(convertir_int16_en_str(accelerometre_z));
  Serial.print(" | Temp = "); Serial.print(temperature / 340.00 + 36.53);
  Serial.print(" | gX = "); Serial.print(convertir_int16_en_str(gyroscope_x));
  Serial.print(" | gY = "); Serial.print(convertir_int16_en_str(gyroscope_y));
  Serial.print(" | gZ = "); Serial.print(convertir_int16_en_str(gyroscope_z));
  Serial.println();

  // Logique d'allumage des LEDs en fonction des valeurs de l'accéléromètre
  if (accelerometre_x < 500 && accelerometre_y < -4000) {
    digitalWrite(LED_LB, HIGH);
    digitalWrite(LED_RB, HIGH);
    digitalWrite(LED_RT, LOW);
    digitalWrite(LED_LT, LOW);
  } else if (accelerometre_y > 4000) {
    digitalWrite(LED_LB, LOW);
    digitalWrite(LED_RB, LOW);
    digitalWrite(LED_RT, HIGH);
    digitalWrite(LED_LT, HIGH);  
  } else if (accelerometre_x > 4000) {
    digitalWrite(LED_LB, LOW);
    digitalWrite(LED_RB, HIGH);
    digitalWrite(LED_RT, HIGH);
    digitalWrite(LED_LT, LOW); 
  } else if (accelerometre_x < -4000 && accelerometre_y < 500) {
    digitalWrite(LED_LB, HIGH);
    digitalWrite(LED_RB, LOW);
    digitalWrite(LED_RT, LOW);
    digitalWrite(LED_LT, HIGH);
  } else {
    digitalWrite(LED_LB, LOW);
    digitalWrite(LED_RB, LOW);
    digitalWrite(LED_RT, LOW);
    digitalWrite(LED_LT, LOW);
  }

  delay(10); // Petite pause pour éviter un rafraîchissement trop rapide
}
