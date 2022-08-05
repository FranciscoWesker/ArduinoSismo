#include<LiquidCrystal.h> // Declaramos la pantalla
LiquidCrystal lcd(7,6,5,4,3,2); // Pins que vamos a usar
#define buzzer 12 // Pin del piezo buzzer 
 
#define x A0 // x_out pin of Accelerometer
#define y A1 // y_out pin of Accelerometer
#define z A2 // z_out pin of Accelerometer
 
/*variables*/
int xsample=0;
int ysample=0;
int zsample=0;
long start;
int buz=0;
 
/*Macros*/
#define samples 50
#define maxVal 20 // Denifinmos el limite maximo
#define minVal -20 // Definimos el limite minimo
#define buzTime 5000 // Tiempo del buzzer
void setup()
{
lcd.begin(16,2); //iniciamos la pantalla
Serial.begin(9600);
delay(1000);
lcd.print("Terremoto ");
lcd.setCursor(0,1);
lcd.print("Detectando ");
delay(2000);
lcd.clear();
lcd.print("Calibrando.....");
lcd.setCursor(0,1);
pinMode(buzzer, OUTPUT);
buz=0;
digitalWrite(buzzer, buz);
for(int i=0;i<samples;i++) // Tomando muestras para calibracion
{
xsample+=analogRead(x);
ysample+=analogRead(y);
zsample+=analogRead(z);
}
 
xsample/=samples; // Tomando el promedio de x
ysample/=samples; // tomando el promedio de y
zsample/=samples; // yomando el promedio de z
 
delay(3000);
lcd.clear();
lcd.print("Estamos calibrando");
delay(1000);
lcd.clear();
lcd.print("El dispositivo esta listo");
delay(1000);
lcd.clear();
lcd.print(" X Y Z ");
}
 
void loop()
{
int value1=analogRead(x); // leyendo a x 
int value2=analogRead(y); //leyendo a y 
int value3=analogRead(z); //leyendo a z 
 
int xValue=xsample-value1; // buscando cambios en x
int yValue=ysample-value2; // buscando cambios en y
int zValue=zsample-value3; // buscando cambios en z
//mostrando los cambios de valores en los ejes x,y y z en la pantalla lcd*/
lcd.setCursor(0,1);
lcd.print(xValue);
lcd.setCursor(6,1);
lcd.print(yValue);
lcd.setCursor(12,1);
lcd.print(zValue);
delay(100);
 
// Comparando el cambio con los limites definidos
if(xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal)
{
if(buz == 0)
start=millis(); 
buz=1; // buzzer /
}
 
else if(buz == 1) //El buzzer hace una alerta de terremoto
{
lcd.setCursor(0,0);
lcd.print("Earthquake Alert ");
if(millis()>= start+buzTime)
buz=0;
}
 
else
{
lcd.clear();
lcd.print(" X Y Z ");
}
 
digitalWrite(buzzer, buz); // Encendido y apagado del buzzer
 
//Enviando valores para procesarlos en la grafica
Serial.print("x=");
Serial.println(xValue);
Serial.print("y=");
Serial.println(yValue);
Serial.print("z=");
Serial.println(zValue);
Serial.println(" $");
}
