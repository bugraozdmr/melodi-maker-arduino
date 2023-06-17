#include <LiquidCrystal.h>

int buzzer=1, kirmizi=9, yesil=10, buton=6;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int kdo=262;
int re=294;
int mi=330;
int fa=349;
int sol=392;
int la=440;
int si=494;
int ido=523;

int cavbella[23]={mi,la,si,kdo,la,mi,la,si,kdo,la,mi,la,si,kdo,si,la,kdo,si,la,mi,mi,re,mi};

void setup()
{
  pinMode(kirmizi,OUTPUT);
  pinMode(yesil,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(buton,INPUT);
  lcd.begin(16, 2);
}

int mod = 1; // Başlangıçta mod 1 olarak ayarlanır
int melodiIndex = 0;
int randint;
boolean melodiCalisiyor = false;

//buranın mantigi:
//eger melodi full calinirsa butona bassak bile degisme olur buton ancak sonda calinabilir
//bu durumda kısa sureli olcagi 1sn bile surmeden direkt degisme olur..
void loop()
{
  if (melodiCalisiyor)
  {
    lcd.clear();
    lcd.home();
    if (mod == 1)
    {
      lcd.print("cav bella ...");
      lcd.setCursor(0, 1);
      lcd.print("caliyor *-*  ");
      digitalWrite(kirmizi,1);
      digitalWrite(yesil,0);

    }
    else if (mod == 2)
    {
      lcd.print("karma melodi ...");
      lcd.setCursor(0, 1);
      lcd.print("caliyor *-*  ");
      randint=random(0,23);
      digitalWrite(kirmizi,0);
      digitalWrite(yesil,1);
      
    }
    if(mod==1){
      lcd.print(cavbella[melodiIndex]);
      tone(buzzer, cavbella[melodiIndex]);
    }else if(mod==2){
      lcd.print(cavbella[randint]);
      tone(buzzer,cavbella[randint]);
    }
    //burasi ortak
    delay(200);
    noTone(buzzer);
    delay(150);
    melodiIndex = (melodiIndex + 1) % 23; // Sonraki melodinin dizideki indeksini güncelle
  }
  else
  {
    lcd.clear();
    lcd.home();
    lcd.print("butona bas :)");
    delay(150);
  }

  if (digitalRead(buton) != 0)
  {
    mod = (mod == 1) ? 2 : 1; // Modu değiştir
    melodiIndex = 0; // Yeni modda başlangıç indeksini sıfırla
    melodiCalisiyor = true; // Melodiyi çalma durumunu başlat
    delay(500); // Buton tepkisini engellemek için kısa bir gecikme eklendi
  }
}
