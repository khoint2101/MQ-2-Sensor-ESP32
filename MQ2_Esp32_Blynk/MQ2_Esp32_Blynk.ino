#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "JVWyJnFwf-C7jOXPmooNcMjrb-Exhz21";       // You should get Auth Token in the Blynk App.
char ssid[] = "Trun Nè";                    // Your Wi-Fi Credentials
char pass[] = "trunkhongchanh";

#define LED_GPIO 19               //led pin
#define BUZZER_GPIO 25            //Buzzer Pin
#define MQ_2 32                   //Sensor MQ-2 Pin


//add of lcd 1602
LiquidCrystal_I2C lcd(0x27, 16, 2);           //goi d/c chan lcd 1602
WidgetLCD phone_lcd(V1);                      

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER_GPIO, OUTPUT);
  pinMode(LED_GPIO, OUTPUT);
  delay(10);
  lcd.setCursor(0,0);
  lcd.print("Connecting to ");
  lcd.setCursor(0,1);
  lcd.println(ssid);
  
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  lcd.print(".");
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("WiFi connected");  delay(1000);
  Blynk.begin("JVWyJnFwf-C7jOXPmooNcMjrb-Exhz21", ssid, pass);
  lcd.clear();
  

}

void loop() {
  Blynk.run();
  int value = analogRead(32);
  Blynk.virtualWrite(V0, value);
  if (value >=1600) {
    Blynk.notify("Co phat hien ro ri GAS! Hay kiem tra!");
    digitalWrite(BUZZER_GPIO, HIGH);
    digitalWrite(LED_GPIO, HIGH);
    delay(100);
    digitalWrite(BUZZER_GPIO, LOW);
    digitalWrite(LED_GPIO, LOW);
    delay(100);
    lcd.setCursor(0,0);
    lcd.print("Khong khi:");lcd.print(value);lcd.print("      ");
    lcd.setCursor(0,1);
    lcd.print("Ro ri GAS     ");
    phone_lcd.print(0,0,"Ro ri GAS       ");
    phone_lcd.print(0,1,"Kiem tra van GAS  ");
  }else {                                     //khi binh thuong
    lcd.setCursor(0,0);
    lcd.print("Khong khi:");lcd.print(value);lcd.print("      ");
    lcd.setCursor(0,1);
    lcd.print("Binh thuong!    ");
    if(value <1000) {
    phone_lcd.print(0,0,"Khong khi: "); phone_lcd.print(11,0,value); phone_lcd.print(14,0,"  ");
    phone_lcd.print(0,1,"Binh thuong!    ");
    }else{
    phone_lcd.print(0,0,"Khong khi: "); phone_lcd.print(11,0,value);
    phone_lcd.print(0,1,"Binh thuong!    ");}
  };
  Serial.print(value);
  delay(500);
}
