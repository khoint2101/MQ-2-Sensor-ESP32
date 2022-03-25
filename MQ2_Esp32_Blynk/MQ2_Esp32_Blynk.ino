#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "JVWyJnFwf-C7jOXPmooNcMjrb-Exhz21";       // You should get Auth Token in the Blynk App.
char ssid[] = "Trun Nè";                    // Your Wi-Fi Credentials
char pass[] = "trunkhongchanh";

#define LED_GPIO 19
#define BUZZER_GPIO 25
#define MQ_2 32


//add of lcd 1602
LiquidCrystal_I2C lcd(0x27, 16, 2);
WidgetLCD phone_lcd(V1);

void setup() {
  Serial.begin(9600);
  lcd.init();
  
  lcd.backlight();
  pinMode(BUZZER_GPIO, OUTPUT);
  pinMode(LED_GPIO, OUTPUT);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Blynk.begin("JVWyJnFwf-C7jOXPmooNcMjrb-Exhz21", ssid, pass);
  

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
    lcd.print("Khong khi:");lcd.print(value);
    lcd.setCursor(0,1);
    lcd.print("Ro ri GAS     ");
    phone_lcd.print(2,0,"Ro ri GAS        ");
    phone_lcd.print(2,1,"Kiem tra van GAS");
  }else {
    lcd.setCursor(0,0);
    lcd.print("Khong khi:");lcd.print(value);
    lcd.setCursor(0,1);
    lcd.print("Binh thuong!    ");
    phone_lcd.print(0,0,"Khong khi: "); phone_lcd.print(11,0,value);
    phone_lcd.print(0,1,"Binh thuong!    ");
  };
  
  delay(500);
}
