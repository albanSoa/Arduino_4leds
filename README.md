# 📄 Lecture du MPU6050 avec contrôle de LEDs - Arduino

## 🎯 Description

Ce projet utilise un capteur **MPU6050** connecté à un Arduino pour lire les données d'**accélération**, de **vitesse angulaire** et de **température**.  
Selon les valeurs de l'accéléromètre, des **LEDs** sont allumées pour indiquer l'orientation.

---

## 🛠 Matériel nécessaire

- 1 × Arduino Uno (ou compatible)
- 1 × Capteur MPU6050
- 4 × LEDs
- 4 × Résistances (220Ω recommandées)
- Câbles de connexion
- (Optionnel) Breadboard

---

## 🔌 Schéma de connexion

| Module           | Arduino         |
|:-----------------|:----------------|
| VCC (MPU6050)     | 5V              |
| GND (MPU6050)     | GND             |
| SDA (MPU6050)     | A4 (I2C data)   |
| SCL (MPU6050)     | A5 (I2C clock)  |
| LED LB (Gauche Bas) | D2             |
| LED RB (Droite Bas) | D3             |
| LED RT (Droite Haut) | D4            |
| LED LT (Gauche Haut) | D5            |

---

## 📚 Librairies utilisées

- **Wire.h** → pour la communication I2C avec le MPU6050.

Cette librairie est **incluse de base** dans l'IDE Arduino.

---

## ⚙️ Fonctionnement du programme

1. **Initialisation** de la communication I2C avec le capteur MPU6050.
2. **Réveil** du MPU6050 (sort du mode veille).
3. **Lecture** des valeurs d'accélération, de gyroscope et de température.
4. **Affichage** des données dans le moniteur série.
5. **Allumage de LEDs** selon les seuils d'inclinaison détectés par l'accéléromètre.

---

## 🧠 Notes techniques

- Le MPU6050 fournit 14 octets de données à chaque lecture.
- Les seuils pour l'allumage des LEDs sont basés sur les axes X et Y de l'accéléromètre.
- La température est calculée selon la formule officielle du capteur.

---
