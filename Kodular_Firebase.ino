#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "https://real-time-data-bc4d3-default-rtdb.asia-southeast1.firebasedatabase.app/" // link projek firebase
#define FIREBASE_AUTH "X6a1jDEJUcHqQzLAEUD9otEPqC4THvfC7GFsjHRw" // secret code projek firebase


#define WIFI_SSID "WIFI_ADHIT" // ssid wifi
#define WIFI_PASS "budumbaba" // pass wifi

#define pinLed1 D5
#define pinLed2 D7

unsigned long waktuAwal1 = 0;
unsigned long waktuAwal2 = 0;
float detik1 = 0;
float detik2 = 0;
bool hitung1  = 0;
bool hitung2  = 0;

FirebaseData firebaseData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting....");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected with IP : ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void hitungWaktu(){
  if(millis() > waktuAwal1 + 500){
    if(hitung1 == 1){
      detik1++;
      waktuAwal1 = millis();
    }
  }

  if(millis() > waktuAwal2 + 500){
    if(hitung2 == 1){
      detik2++;
      waktuAwal2 = millis();
    }
  }  
}

void aksi(bool istrue){
  
}

void loop() {

  hitungWaktu();
  
  if(Firebase.getString(firebaseData, "/Firebase_Kodular/lampuSatu")){
    String data1 = firebaseData.stringData();
    if(data1 == "true"){
      hitung1 = 1;
      digitalWrite(pinLed1, 1);
      Firebase.setInt(firebaseData, "Firebase_Kodular/detikNyalaR1", detik1);
    } else if(data1 == "false"){
      hitung1 = 0;
      digitalWrite(pinLed1, 0);
    }
  };

  if(Firebase.getString(firebaseData, "/Firebase_Kodular/lampuDua")){
    String data2 = firebaseData.stringData();
    if(data2 == "true"){
      hitung2 = 1;
      digitalWrite(pinLed2, 1);
      Firebase.setInt(firebaseData, "Firebase_Kodular/detikNyalaR2", detik2);
    } else if(data2 == "false"){
      hitung2 = 0;
      digitalWrite(pinLed2, 0);
    }
  };
}