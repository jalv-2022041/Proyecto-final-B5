int Valuable;                // Variable que almacena el valor raw (0 a 1023)
float VOLTAGE;               // Variable que almacena el voltaje (0.0 a 25.0)
float Sensibilidad = 0.185;
const int pinAnalogico = A0;    // Pin analógico para medir la resistencia 
const float resistenciaConocida = 1000.0; // Resistencia(1k ohm)
unsigned long tiempoAnterior = 0;
const unsigned long intervaloMedicion = 1000; // Intervalo de medición en milisegundos
void setup() ;
  Serial.begin(9600);    // Iniciar la comunicación serial
  BLUEE.begin(9600);}
char recep;
void loop() {
  // Verificar si hay datos disponibles desde la aplicación Bluetooth
  if (BLUEE.available()) {
    recep = BLUEE.read();
    Serial.println(recep);
    // Procesar comandos según corresponda
    if (recep == 'A') {
      medirVoltaje();
    }
    else if (recep == 'B') {
      medirResistencia();
    }
    else if (recep == 'C') {
      medirCorriente(); } }
  unsigned long tiempoActual = millis();
  if (tiempoActual - tiempoAnterior >= intervaloMedicion) {
    tiempoAnterior = tiempoActual;  }}
void medirVoltaje() {
  digitalWrite(MED1, HIGH);
  digitalWrite(MED2, HIGH);
  Valuable = analogRead(A1); // Realizar la lectura
  VOLTAGE = map(Valuable, 0, 1023, 0, 250) / 10.0;  // Escalar a 0.0 - 25.0
  Serial.print("Voltaje: ");
  Serial.println(VOLTAGE); // Mostrar el valor
  BLUEE.print(VOLTAGE);
  BLUEE.print(";");}
void medirResistencia() {
  digitalWrite(MED1, LOW);
  digitalWrite(MED2, LOW);
  int valorAnalogico = analogRead(pinAnalogico);
  float tensionMedida = (float)valorAnalogico * (5.0 / 1023.0);// Convertir la tención 
  float corriente = tensionMedida / resistenciaConocida ; //I = V / R
  float resistenciaDesconocida = tensionMedida / corriente;  //ley de Ohm: R = V / I
  Serial.print("Resistencia: ");
  Serial.println(resistenciaDesconocida);
  BLUEE.print(resistenciaDesconocida);
  BLUEE.print(";");
}

void medirCorriente() {
  float Corriente=calculo(500);
      Serial.print("Corriente: ");
      Serial.println(Corriente,3);
      BLUEE.print(Corriente,3);
      BLUEE.print(";");
}
float calculo(int numeroMuestral)
{
float LeerSenso = 0;
float inten = 0;
for(int i=0;i<numeroMuestral;i++)
{
  LeerSenso= analogRead(A2) * (5.0 / 1023.0);
  inten=inten+(LeerSenso-2.5)/Sensibilidad;
inten=inten/numeroMuestral;
return(inten);}
