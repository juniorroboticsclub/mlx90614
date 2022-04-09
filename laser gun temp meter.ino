#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define echoPin 3 
#define trigPin 4 


const int Laser_Pin=5;  
const int buzzer = 2;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();


long duration; 
int distance;
void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test"); 
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  pinMode(Laser_Pin,OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  

  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 35);
  display.println("Initializing Temp");
  display.display();
  delay(250);
  display.clearDisplay();

  mlx.begin(); 
  
}

void loop() {

 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
 digitalWrite(buzzer, LOW);
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
    display.clearDisplay();
    display.setTextSize(2);  
    display.setCursor(25, 10);
    display.print(distance);
    display.setCursor(95, 10);
    display.print("Cm");
   if (distance<20) {
   
    digitalWrite(Laser_Pin, LOW);
    digitalWrite(buzzer, HIGH);
    display.clearDisplay();
     display.clearDisplay();
    display.setTextSize(2);  
    display.setCursor(25, 10);
    display.print(distance);
    display.setCursor(95, 10);
    display.print("Cm");
    display.setTextSize(2);
    display.setCursor(25, 36);
    display.print(mlx.readObjectTempF()-6);
    display.setCursor(95, 36);
    display.print("F");
    display.display();
   
    if(mlx.readObjectTempF()-6>98)
    {
      
    display.clearDisplay();
    display.setTextSize(2);  
    display.setCursor(25, 10);
    display.print(distance);
    display.setCursor(95, 10);
    display.print("Cm");
      display.setTextSize(2);
      display.setCursor(25, 36);
      display.print(mlx.readObjectTempF()-6);
      display.setCursor(95, 36);
      display.print("F");
      display.display();
     
    for (int i=0; i<20; i++)
    {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
    }
   
   delay(5000);  
    }
    
  } else {
    // turn LED off:
    digitalWrite(Laser_Pin, HIGH);
    digitalWrite(buzzer, LOW);

  
    display.print("");
    display.setTextSize(2);
    display.setCursor(35, 36);
    display.print("-----");
    display.setCursor(105, 36);
    display.print("");
    display.display();
    
    
  }

  Serial.println();
  delay(500);
}
