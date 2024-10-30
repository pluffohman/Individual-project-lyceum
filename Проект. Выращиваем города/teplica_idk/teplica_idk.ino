#include <Wire.h>                   
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 


int VLAG_PIN_OUT = 12;
#define VLAG_PIN_IN A0
int RELE1_PIN_PUMP = 11; //помпа 
int RELE2_PIN_LAMP = 10; //свет 
#define PHOTO_PIN A1

int very_moist_value = 327;   
void setup()
{
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);        
  lcd.init();                   
  lcd.backlight();                     
  lcd.setCursor(0, 0);       
  lcd.print("VLAGA:");  
  Serial.begin(9600);
  digitalWrite(RELE1_PIN_PUMP, 0);
  digitalWrite(RELE2_PIN_LAMP, 0);


}

void loop()
{
  delay(200);
  lcd.setCursor(12, 0);
  lcd.print("    ");
  lcd.setCursor(13, 0);           
      
  lcd.print(ask_vlaga());
  lcd.print("%");

  lcd.print("   ");
  lcd.setCursor(0, 1);
  lcd.print(analogRead(PHOTO_PIN));
  Serial.println(analogRead(PHOTO_PIN));

  check_photo();
  //check_vlaga();      
}

int ask_vlaga()
{
  digitalWrite(VLAG_PIN_OUT, HIGH);  
  delay(10);
  int moisture_value = analogRead(VLAG_PIN_IN);  
  digitalWrite(VLAG_PIN_OUT, LOW);
  int vlaga = map(moisture_value,very_moist_value,1023,100,0);
  return vlaga;
}

void check_photo()
{
  if(analogRead(PHOTO_PIN) < 15){
    digitalWrite(RELE2_PIN_LAMP, HIGH);
  }
  else if(analogRead(PHOTO_PIN) >= 15)
  {
    digitalWrite(RELE2_PIN_LAMP, LOW);
  }
}
void check_vlaga()
{
  int vlag = ask_vlaga();
  if(vlag <= 70)
  {
    digitalWrite(RELE1_PIN_PUMP, HIGH); //включаем помпу
    //delay(10000);
    digitalWrite(RELE1_PIN_PUMP, LOW);
  }
 // delay(120000); //ждем 2 минуты для пропитки почвы, для избежания перелива
}

