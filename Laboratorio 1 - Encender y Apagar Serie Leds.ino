// Defina constantes para los pines LED y el pin del botón pulsador
const int LED_START_PIN = 2;
const int LED_END_PIN = 9;
const int BUTTON_PIN = 10;

//Defina una variable para almacenar el estado actual del pulsador y el estado del parpadeo del LED
int buttonState = 0;
bool blinkLEDs = false;

void setup() {
  // Inicializan los pines LED como salidas y enciéndalos todos
  for (int i = LED_START_PIN; i <= LED_END_PIN; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  // Inicialice el pin del botón pulsador como una entrada
  pinMode(BUTTON_PIN, INPUT);

  // Inicializar la comunicación serie
  Serial.begin(9600);
}

void loop() {
  // Compruebe si el botón está presionado
  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    // Si se presiona el botón, apague el parpadeo y encienda y apague los LED en secuencia
    blinkLEDs = false;
    for (int i = LED_START_PIN; i <= LED_END_PIN; i++) {
      digitalWrite(i, LOW);
      delay(100);
      digitalWrite(i, HIGH);
    }
  } else if (blinkLEDs) {
    // Si el botón no está presionado pero los LED deben parpadear, enciéndalos y apáguelos con un retraso de 2 segundos
    for (int i = LED_START_PIN; i <= LED_END_PIN; i++) {
      digitalWrite(i, LOW);
    }
    delay(2000);
    for (int i = LED_START_PIN; i <= LED_END_PIN; i++) {
      digitalWrite(i, HIGH);
    }
    delay(2000);
  }

  if (Serial.available() > 0) {
    // Lea el mensaje entrante del monitor serial
    int message = Serial.parseInt();

    if (message == 2) {
      // Si el mensaje es 2, enciende el LED parpadeando
      blinkLEDs = true;
    }
  }
}