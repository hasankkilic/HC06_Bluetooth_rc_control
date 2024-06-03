 
    
    #define Led_Far 2
    #define Led_Fren 3
    #define Led_Sol 12
    #define Led_Sag 13
    #define trigpini 7  // TRIG pini
    #define echopini 8  // ECHO pini
    #define IRSensor 4  //ir alici pini
    #define MotorSolIleriPin 11
    #define MotorSolGeriPin 10
    #define MotorSagIleriPin 6
    #define MotorSagGeriPin 5
    #define SesCikisi 9
    #define SensorSol A1
    #define SensorOrta A2
    #define SensorSag A3
    #define SensorSolPIN  A1
    #define SensorOrtaPIN A2
    #define SensorSagPIN  A3

int VeriGelmiyorSayac=0;
int BeepSayac=0;
boolean beepon=false;

//bluetooth uzerinden gelen bilginin alinmasi
char BT_rx(){
  char gelenveri='_';
  if (Serial.available() > 0) //Serial portun kontrollü
  {
    gelenveri = Serial.read(); //Telefondan gelen verilerin kontrollü  
    Serial.println(gelenveri);
    VeriGelmiyorSayac=0;
  }
  
  return gelenveri;
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(Led_Far,OUTPUT); 
  pinMode(Led_Fren,OUTPUT);
  pinMode(Led_Sol,OUTPUT); 
  pinMode(Led_Sag,OUTPUT);
  pinMode(9,OUTPUT);   
  Serial.println("Robot01 hazir");

          analogWrite(MotorSolIleriPin,0);
          analogWrite(MotorSolGeriPin,0);
          analogWrite(MotorSagIleriPin,0);
          analogWrite(MotorSagGeriPin,0);
}

void beep(){
  digitalWrite(9,1);
  delay(1);
  digitalWrite(9,0);
  delay(1);
  
}
void Robot_Dur(){
    analogWrite(MotorSolIleriPin,0);
    analogWrite(MotorSolGeriPin,0);
    analogWrite(MotorSagIleriPin,0);
    analogWrite(MotorSagGeriPin,0);
              
    digitalWrite(Led_Sol, 0);
    digitalWrite(Led_Sag, 0);
    digitalWrite(Led_Far, 0);
    digitalWrite(Led_Fren, 0);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay (1);

if (beepon==true){
  digitalWrite(9,1 - digitalRead(9));  
}
/*
  if (beepon==true){
    if(BeepSayac<100){
      digitalWrite(9,1 - digitalRead(9));
      BeepSayac++;
    }else{
      beepon=false;
    }

  }else{
    BeepSayac=0;  
  }
*/

  switch (BT_rx())
  {
    case '_': //veri gelmiyor ise 10sn sonra otomatik dursun
      if (VeriGelmiyorSayac<10000){
        VeriGelmiyorSayac++;
      }else{
        Robot_Dur();
        beepon=false;
      }
      
    break;
    
    case '8'://ileri
          analogWrite(MotorSolIleriPin,255);
          analogWrite(MotorSolGeriPin,0);
          analogWrite(MotorSagIleriPin,240);
          analogWrite(MotorSagGeriPin,0);
                    
          digitalWrite(Led_Sol, 0);
          digitalWrite(Led_Sag, 0);
          digitalWrite(Led_Far, 1);
          digitalWrite(Led_Fren, 0);
    break;
    
    case '2'://geri
          analogWrite(MotorSolIleriPin,0);
          analogWrite(MotorSolGeriPin,255);
          analogWrite(MotorSagIleriPin,0);
          analogWrite(MotorSagGeriPin,240);
              
          digitalWrite(Led_Sol, 0);
          digitalWrite(Led_Sag, 0);
          digitalWrite(Led_Far, 0);
          digitalWrite(Led_Fren, 1);
    break;
    
    case '0'://stop
      Robot_Dur();
    break;

    case '4'://sol
          analogWrite(MotorSolIleriPin,0);
          analogWrite(MotorSolGeriPin,200);
          analogWrite(MotorSagIleriPin,200);
          analogWrite(MotorSagGeriPin,0);
          
          digitalWrite(Led_Sol, 1);
          digitalWrite(Led_Sag, 0);
          digitalWrite(Led_Far, 0);
          digitalWrite(Led_Fren, 0);          
    break;

    case '6'://sag
          analogWrite(MotorSolIleriPin,200);
          analogWrite(MotorSolGeriPin,0);
          analogWrite(MotorSagIleriPin,0);
          analogWrite(MotorSagGeriPin,200);
              
          digitalWrite(Led_Sol, 0);
          digitalWrite(Led_Sag, 1);
          digitalWrite(Led_Far, 0);
          digitalWrite(Led_Fren, 0);
    break;
    
    case '5'://beep
      beepon=true;
      

    break;
    
    case '7'://ileri+sol
    break;

    case '9'://ileri+sag
    break;
    
    case '1'://gerii+sol
    break;

    case '3'://geri+sag
    break;
    
    case 'q'://korna on
      beepon=true;
    break;

    case 'a'://korna off
      beepon=false;
    break;

    case 13:
        Serial.println("ROBOS01 Ostim Mesleki ve Teknik Anadolu Lisesi");
        /*
        Serial.print("Batarya:");
        Serial.print(analogRead(A0));
        Serial.println(" "); 
        Serial.print("sensor:");
        Serial.print(Sensorler[0]);
        Serial.print(",");
        Serial.print(Sensorler[1]);
        Serial.print(",");
        Serial.print(Sensorler[2]);
        Serial.println(" ");
        */
    break;
    default:
    break;
  }  

}
