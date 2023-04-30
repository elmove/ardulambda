const int PIN_ANALOGICO = A0;
const float VREF = 5.0;
const float RELACION_AIRE_COMBUSTIBLE_ESTOQUIOMETRICA = 14.7;
const float RESISTENCIA_CARGA = 100.0;
unsigned long ultimoTiempoLectura = 0;
const unsigned long intervaloLectura = 1000; // lectura cada 1 segundo

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long tiempoActual = millis();
  if (tiempoActual - ultimoTiempoLectura >= intervaloLectura) {
    ultimoTiempoLectura = tiempoActual;

    float voltaje = analogRead(PIN_ANALOGICO) * VREF / 1023.0;
    float corriente = voltaje / RESISTENCIA_CARGA;
    float relacionAireCombustible = RELACION_AIRE_COMBUSTIBLE_ESTOQUIOMETRICA / corriente;

    Serial.print("Relación aire/combustible: ");
    Serial.print(relacionAireCombustible, 2);
    Serial.print(", ");

    if (relacionAireCombustible > RELACION_AIRE_COMBUSTIBLE_ESTOQUIOMETRICA) {
      Serial.println("pobre");
    } else if (relacionAireCombustible < RELACION_AIRE_COMBUSTIBLE_ESTOQUIOMETRICA) {
      Serial.println("rica");
    } else {
      Serial.println("estequiométrica");
    }
  }
}