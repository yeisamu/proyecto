
//#include <Servo.h>
// include the library code:
#include <LiquidCrystal.h>
#include <DHT11.h>
const int sensorPin= A0;
const int sensorventi = 6;
const int controlagua = 10;
//Sensor Humedad
int pin=7;
DHT11 dht11(pin);
//Leds
int led_1 = 13;
int led_2 = 8;
int led_3 = 9;
byte grado[8] =
 {
    0b00001100,     // Los definimos como binarios 0bxxxxxxx
    0b00010010,
    0b00010010,
    0b00001100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
 };
 byte porcen[8] =
 {
    0b00011000,     // Los definimos como binarios 0bxxxxxxx
    0b00011000,
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00000011,
    0b00000011
 };
//Servo motor;
// Iniciar la libreria con los pins de la interfaz de la libreria
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {

  pinMode(sensorventi, OUTPUT);
//  lcd.begin(16, 2);
  Serial.begin(9600);
 lcd.begin(16,2); //Decimos que la pantalla tiene 16 caracteres y dos líneas
  lcd.createChar(1, grado);
  lcd.createChar(2, porcen);
  lcd.setCursor(0,0); //Ponemos el cursor en la primer línea y el primer caracter
  lcd.print("Temp & RH"); //Se escribe el mensaje en la primer línea
  lcd.setCursor(0,1); //Movemos el cursor al primer caracter y segunda línea 
  lcd.print("Monitor"); //Escribimos el mensaje
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  
  pinMode(controlagua, OUTPUT);//motor.attach(6);
 // 
  delay(2000); //Esperamos dos segundos
  lcd.clear();
 
}

void loop() {
  
   digitalWrite(led_1, LOW);
   digitalWrite(led_2, LOW);
   digitalWrite(led_3, LOW);
  
  // Establece el cursor de la columna 0, linea 1
  /*int value = analogRead(sensorPin);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10; */  
  int humedad = analogRead(sensorPin);
   if(humedad <= 500)
   {
       //activar agua
       // digitalWrite(sensorventi, LOW);
       lcd.setCursor(0, 0);
       lcd.print(humedad);
       lcd.print(" Tierra Muy mojada");  
       digitalWrite(led_1, LOW);
       digitalWrite(led_2, LOW);
       digitalWrite(led_3, HIGH);
       digitalWrite(controlagua, HIGH);
       // motor.write(360);
       //delay(1000);
      // lcd.clear();
   }
   
   if(humedad > 500 && humedad <= 700){
      //activar agua
      lcd.setCursor(0, 0);
       lcd.print(humedad);
       lcd.print(" Tierra humeda");  
       digitalWrite(led_1, LOW);
       digitalWrite(led_2, HIGH);
       digitalWrite(led_3, LOW);
       // motor.write(360);
       digitalWrite(controlagua, LOW);
         //delay(1000);
   }
   
   if(humedad > 700){
       lcd.setCursor(0, 0);
       lcd.print(humedad);
       lcd.print(" Tierra seca");  
       digitalWrite(led_1, HIGH);
       digitalWrite(led_2, LOW);
       digitalWrite(led_3, LOW);
       digitalWrite(controlagua, HIGH);
       // motor.write(90);
       // delay(1000);
   }
    delay(2000);
    int err;
    float temp, hum;
     lcd.clear();
   if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
    {
      if(hum >= 80 && hum <=100){  
         // motor.write(-360);
          lcd.setCursor(0, 0);    
           digitalWrite(sensorventi, HIGH);
           lcd.print("  HR : ");
           lcd.print(hum,0);
            lcd.write(2); 
      }else{
        lcd.setCursor(0, 0);
        digitalWrite(sensorventi, LOW);
        lcd.print("  HR: ");
        lcd.print(hum,0);
        lcd.write(2); 
      }
      //lcd.clear();
      if(temp >= 20){ 
          lcd.setCursor(0,1); 
          for ( int n = 0 ; n < 255 ; n++)
           {
                digitalWrite(sensorventi, HIGH);
               delay(15) ;
           }    
         
           lcd.print("  Temp: ");
           lcd.print(temp,0);
           lcd.write(1); 
      }else{
        
        digitalWrite(sensorventi, LOW);
         lcd.print("  Temp : ");
         lcd.print(temp,0);
          lcd.write(1); 
      }
              
   }
   else
   {
            // Serial.println();
            lcd.print("Error Temperatura :");
             lcd.print(err);
             lcd.println();
   }
   
      delay(4000);
}
