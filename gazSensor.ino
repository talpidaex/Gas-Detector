//Gaz Sensörü,Buzzer

#include<LiquidCrystal.h>
LiquidCrystal lcd(8,7,6,5,4,3);  
//Sensör pinlerimizi tanımlıyoruz:
#define sensor_pin A0
#define buzzer_pin 9
//RGB LED'imizin çıkış pinlerini tanımlıyoruz:
#define led_r 10
#define led_g 11
#define led_b 12
#define fan 13
//Sensörün çalışması için gerekli ön ısıtma süresini 5sn olarak belirliyoruz
#define preheat_time 5000
//Alarmın çalması için gerekli eşik değerini 300 olarak belirliyoruz.
#define threshold 300



void setup() {
  //Alarm için kullanacağımız buzzer ve LED'leri çıkış olarak tanımlıyoruz
  lcd.begin(16,2);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(fan,OUTPUT);
  //Varsayılan olarak LED'in sönük kalmasını sağlıyoruz
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);
  digitalWrite(fan,LOW);

  //Sensör değerini seri monitörden görebilmemiz için seri haberleşmeyi başlatıyoruz:
  Serial.begin(9600);
  //İlk 5sn boyunca sensörün ısınmasını bekliyoruz. Bu esnada LED mavi renkte yanıyor:
  Serial.println("Sensor isitiliyor...");
  lcd.print("Sensor isiniyor...");
  digitalWrite(led_b, HIGH);
  delay(preheat_time);
  lcd.clear();
  //Isıma işlemi için gereken 5sn süre tamamlandığında mavi LED'i söndürüyoruz:
  digitalWrite(led_b, LOW);
  delay(1);

}

void loop() {
          //analogRead() fonksiyonu ile sensör değerini ölçüyoruz ve bir değişken içerisinde tutuyoruz:
        int sensorValue = analogRead(sensor_pin);
        delay(500);
        lcd.clear();
        lcd.print("Gaz Degeri ");
        lcd.print(sensorValue);
        //Sensör değeri belirlediğimiz eşik değerinden yüksek ise alarm() fonksiyonunu çağırıyoruz:
        if (sensorValue >= threshold){
        alarm(100);
        }
        //Alarmın çalmadığı durumda LED'in yeşil yanmasını istiyoruz:
        else{
        digitalWrite(led_g, HIGH);
        //Sensör değerini bilgisayarımızdan görebilmek için seri monitöre yazıyoruz:
        digitalWrite(fan,LOW);
        }
        Serial.println(sensorValue);
        delay(1);

}

//Alarm fonksiyonumuzu tanımlıyoruz. Bu fonksiyon parametre olarak buzzerın ötüp ve LED'in yanıp söneceği süreyi almakta.

void alarm(unsigned int duration)
{
//Buzzer'ın 440Hz'te (la notası) ses üretmesini istiyoruz:
tone(buzzer_pin, 440);
digitalWrite(fan,HIGH);
//Normal durumda yeşil yanmakta olan LED'i söndürüp kırmızı renkte yakıyoruz:
digitalWrite(led_r, HIGH);
digitalWrite(led_g, LOW);
delay(duration);
noTone(buzzer_pin);
digitalWrite(led_r, LOW);
digitalWrite(led_g, LOW);
delay(duration);
}


