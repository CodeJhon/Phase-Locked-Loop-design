#include <PWM.h>                    // Inicia la codificación
int32_t frequency = 9090;          // Establezca la Frecuencia en Hertz (Hz), se pueden operar frecuencias 
                                    // de entre 10Hz a 300kHz aproximadamente.
void setup()
{
  InitTimersSafe();
  bool success = SetPinFrequencySafe(9, frequency);   //Establece la frecuencia para el pin especificado
  if(success) {              //Si la frecuencia en el pin se configuró correctamente, que se encienda el pin 13.
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
  }
}
void loop()
{                                   //Potenciometro de 10Kohms para ajustar el DUTY CYCLE (D)
  //int sensorValue = analogRead(A5); //Conectar las dos terminales laterales del potenciometro a +5V y Gnd 
                                    //(Lado izquierdo(pin 1) a GND y lado derecho (Pin 3) a +5V
  pwmWrite(9, 512 / 4);     //la terminal de enmedio(2) conectarla a una entrada analogica (A5) o la que se desee.
  delay(30);                        //La salida PWM será el pin digital (9) con respecto a tierra.
}                                   // FIN DE LA CODIFICACIÓN....................................
