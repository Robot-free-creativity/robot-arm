#include <Servo.h>

Servo servo1;  // Servo pour la pince
Servo servo2;  // Servo pour le poignet
Servo servo3;  // Servo pour le coude inférieur (lié inversement au supérieur)
Servo servo4;  // Servo pour le coude supérieur
Servo servo5;  // Servo pour l'épaule

int pot1 = A0;  // Potentiomètre pour la pince
int pot2 = A1;  // Potentiomètre pour le poignet
int pot3 = A2;  // Potentiomètre pour le coude
int pot4 = A3;  // Potentiomètre pour l'épaule

int val1, val2, val3, val4;  
int ANGLE1, ANGLE2, ANGLE3, ANGLE4, ANGLE5;

void setup() {
  Serial.begin(9600);

  servo1.attach(2);  // Pince
  servo2.attach(3);  // Poignet
  servo3.attach(4);  // Coude inférieur
  servo4.attach(5);  // Coude supérieur
  servo5.attach(6);  // Épaule

  // Initialiser chaque servo à la position correspondant à la valeur du potentiomètre
  val1 = analogRead(pot1);            
  ANGLE1 = map(val1, 0, 1023, 0, 90);  // Pince
  servo1.write(ANGLE1);

  val2 = analogRead(pot2);            
  ANGLE2 = map(val2, 0, 1023, 0, 180);  // Poignet
  servo2.write(ANGLE2);

  val3 = analogRead(pot3);            
  ANGLE3 = map(val3, 0, 1023, 0, 180);  // Coude inférieur
  ANGLE4 = map(val3, 0, 1023, 180, 0);  // Coude supérieur (inverse)
  servo3.write(ANGLE3);
  servo4.write(ANGLE4);

  val4 = analogRead(pot4);            
  ANGLE5 = map(val4, 0, 1023, 0, 180);  // Épaule
  servo5.write(ANGLE5);

  delay(500);
}

void loop() {
  // Lire les potentiomètres et mapper les valeurs aux angles
  val1 = analogRead(pot1);            
  int targetAngle1 = map(val1, 0, 1023, 0, 90);  // Pince

  val2 = analogRead(pot2);            
  int targetAngle2 = map(val2, 0, 1023, 0, 180);  // Poignet

  val3 = analogRead(pot3);            
  int targetAngle3 = map(val3, 0, 1023, 0, 180);  // Coude inférieur
  int targetAngle4 = map(val3, 0, 1023, 180, 0);  // Coude supérieur

  val4 = analogRead(pot4);            
  int targetAngle5 = map(val4, 0, 1023, 0, 180);  // Épaule

  // Ajustement dynamique du poignet en fonction du coude
  if (targetAngle4 > 70) {  // Si le coude supérieur dépasse 70 degrés
    targetAngle2 = constrain(targetAngle2, 0, 165);  // Limite la flexion du poignet
  }

  if (targetAngle4 > 120) {
    targetAngle2 = constrain(targetAngle2, 0, 155);  // Limite la flexion du poignet
  }
  if (targetAngle4 > 130) {
    targetAngle2 = constrain(targetAngle2, 0, 140);  // Limite la flexion du poignet
  }
  if (targetAngle4 > 135) {
    targetAngle2 = constrain(targetAngle2, 0, 125);  // Limite la flexion du poignet
  }
  if (targetAngle4 > 140) {
    targetAngle2 = constrain(targetAngle2, 0, 110);  // Limite la flexion du poignet
  }
  if (targetAngle4 > 150) {
    targetAngle2 = constrain(targetAngle2, 0, 95);  // Limite la flexion du poignet
  }
  if (targetAngle4 > 160) {
    targetAngle2 = constrain(targetAngle2, 0, 70);  // Limite la flexion du poignet
  }
  if (targetAngle4 > 170) {
    targetAngle2 = constrain(targetAngle2, 0, 55);  // Limite la flexion du poignet
  }
  if (targetAngle4 > 175) {
    targetAngle2 = constrain(targetAngle2, 0, 40);  // Limite la flexion du poignet
  }
  

  // Déplacer les servos progressivement
  moveServoTo(servo1, targetAngle1);  // Pince
  moveServoTo(servo2, targetAngle2);  // Poignet
  moveServoTo(servo3, targetAngle3);  // Coude inférieur
  moveServoTo(servo4, targetAngle4);  // Coude supérieur
  moveServoTo(servo5, targetAngle5);  // Épaule

  delay(100);  // Ajusté pour un mouvement plus réactif                       

  Serial.print("Pince = ");
  Serial.println(val1);
  Serial.print("Poignet = ");
  Serial.println(val2);
  Serial.print("Coude (sup) = ");
  Serial.println(val4);
  Serial.print("Coude (inf) = ");
  Serial.println(val3);
  Serial.print("Épaule = ");
  Serial.println(val4);
}

void moveServoTo(Servo &servo, int targetAngle) {
  int currentAngle = servo.read();
  if (targetAngle > currentAngle) {
    for (int i = currentAngle; i <= targetAngle; i++) {
      servo.write(i);
      delay(15);
    }
  } else {
    for (int i = currentAngle; i >= targetAngle; i--) {
      servo.write(i);
      delay(15);
    }
  }
}
