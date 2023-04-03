#include <SoftwareSerial.h>


SoftwareSerial ESP_Serial(3,2);

String payload;

int A1O = 10;
int A2O = 11;
int B1O = 5;
int B2O = 6;

  //ATR 
  //ADL 
  //ADE 
  //AIZ 
  //IZQ 
  //DER 
  //DDE 
  //DIZ 

String movements[]={"ATR","ADL","ADE","AIZ","IZQ","DER","DDE","DIZ"};
int keys[]={0,1,2,3,4,5,6,7};
//{"ATR","ADL","ADE","AIZ","IZQ","DER","DDE","DIZ"}
//{0,1,2,3,4,5,6,7}

String inputs[] = {
  
};


bool actionFlag;

int speed = 153;
int currentAngle =0;

int direcc;


int setAngle(int angle)
{
  int neededAngle = angle;
  
  int angleAmount = neededAngle - currentAngle;
 

  rotate(angleAmount);
    return 1;
}


int rotate(int angleAmount){

  
  Serial.println("rotating");
  Serial.println( angleAmount);

  if(angleAmount < 0 && currentAngle>0){
    //rotates left
    analogWrite(A1O,0);
    analogWrite(A2O,speed);
    analogWrite(B1O,speed);
    analogWrite(B2O,0);
    delay(210*((-angleAmount)/45));
    currentAngle =currentAngle+angleAmount;
    
  }
  if(angleAmount > 0 && currentAngle < 145){
    //rotates right
    analogWrite(A1O,speed);
    analogWrite(A2O,0);
    analogWrite(B1O,0);
    analogWrite(B2O,speed);
    delay(210*(angleAmount/45));
    currentAngle += angleAmount;
    
  }
  
  return 1;
  
}

int getMoveKey(String moveInput)
{
  
  for(int i=0;i<8;i++){
    if(moveInput == movements[i]){
      return keys[i];
      break;
    }
    
  }
  return 0;
}


void setup() {
  // put your setup code here, to run once:
 

  pinMode(A1O,OUTPUT);
  pinMode(A2O,OUTPUT);
  pinMode(B1O,OUTPUT);
  pinMode(B2O,OUTPUT);

  digitalWrite(B1O,LOW);
  digitalWrite(B2O,LOW);
  digitalWrite(A1O,LOW);
  digitalWrite(A2O,LOW);

  if(sizeof(inputs)!=0){
    actionFlag = true;
  }else{
    actionFlag = false;
    }
  
  
  Serial.begin(9600);
   ESP_Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  payload = ESP_Serial.readString();
  Serial.println(payload);
  
  if (actionFlag)
  {
    
    for(int i=0;i<sizeof(inputs)/6;i++) //size of inputs is the ammount of strings * 6, why? idk
    {
           
            Serial.print("input=  ");
            Serial.println(inputs[i]);
            Serial.print("moveKey=  ");
            Serial.println(getMoveKey(inputs[i]));

       switch(getMoveKey(inputs[i]))
       {
            
            
        case 0:
          {
            Serial.print("case=");
            Serial.println("ATR");
            setAngle(0);
            analogWrite(A1O,0);
            analogWrite(A2O,speed);
            analogWrite(B1O,0);
            analogWrite(B2O,speed);
            delay(210);
        
          break;
         };
         case 1:
          {
            Serial.print("case=");
            Serial.println("ADL");
            setAngle(0);
            analogWrite(A1O,speed);
            analogWrite(A2O,0);
            analogWrite(B1O,speed);
            analogWrite(B2O,0);
            delay(210);
        
          break;
          };
          case 2:
          {
            Serial.print("case=");
            Serial.println("ADE");
            setAngle(45);
            analogWrite(A1O,speed);
            analogWrite(A2O,0);
            analogWrite(B1O,speed);
            analogWrite(B2O,0);
            delay(210);
        
          break;
         };
          case 3:
          {
            Serial.print("case=");
            Serial.println("AIZ");
            setAngle(145);
            analogWrite(A1O,0);
            analogWrite(A2O,speed);
            analogWrite(B1O,0);
            analogWrite(B2O,speed);
            delay(210);
        
          break;
         };
         case 4:
          {
            Serial.print("case=");
            Serial.println("IZQ");
            setAngle(90);
            analogWrite(A1O,0);
            analogWrite(A2O,speed);
            analogWrite(B1O,0);
            analogWrite(B2O,speed);
            delay(210);
        
          break;
         };
         case 5:
          {
            Serial.print("case=");
            Serial.println("DER");
            setAngle(90);
            analogWrite(A1O,speed);
            analogWrite(A2O,0);
            analogWrite(B1O,speed);
            analogWrite(B2O,0);
            delay(210);
        
          break;
         };
         case 6:
          {
            Serial.print("case=");
            Serial.println("DDE");
            setAngle(145);
            analogWrite(A1O,speed);
            analogWrite(A2O,0);
            analogWrite(B1O,speed);
            analogWrite(B2O,0);
            delay(210);
        
          break;
         };
         case 7:
          {
            Serial.print("case=");
            Serial.println("DIZ");
            setAngle(45);
            analogWrite(A1O,0);
            analogWrite(A2O,speed);
            analogWrite(B1O,0);
            analogWrite(B2O,speed);
            delay(210);
        
          break;
         };
         default:
         Serial.println("Case error!");
      } 
    }
    actionFlag = false;
    
    
  }else{
        analogWrite(B1O,0);
        analogWrite(B2O,0);
        analogWrite(A1O,0);
        analogWrite(A2O,0);
    delay(11000);
  }

}
