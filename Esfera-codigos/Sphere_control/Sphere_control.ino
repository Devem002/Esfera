#include <AltSoftSerial.h>

//#include <SoftwareSerial.h>

AltSoftSerial altser;
//SoftwareSerial ESP_Serial(3,2);

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
String arrayOut[20];



bool actionFlag = false;

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
    delay(300*((-angleAmount)/45));
    currentAngle =currentAngle+angleAmount;
    
  }
  if(angleAmount > 0 && currentAngle < 145){
    //rotates right
    analogWrite(A1O,speed);
    analogWrite(A2O,0);
    analogWrite(B1O,0);
    analogWrite(B2O,speed);
    delay(300*(angleAmount/45));
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
  return 9;
}


int waitForInput()
{
  if(altser.available()>0){
    while(altser.available()>0){
    
      char c = altser.read();
    payload.concat(c);
  }
   Serial.println(payload);

  String breakPay;
  int x = 0;
  
  for(int i =1; i<60;i++){
    
    if(!(payload[i]== ',' or payload[i]== '.' or payload[i]== ']'  or payload[i]== '[')){
      
         breakPay.concat(payload[i]);
      }
      //Serial.println(breakPay);
    else{
      //Serial.println(breakPay);
      arrayOut[x] = breakPay;
      x += 1;
      breakPay.remove(0);
      //Serial.println("cleaned String");
    }
    }
   
   actionFlag = true;
   
}else{
  delay(15000);
}

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

  Serial.begin(9600);
  altser.begin(115200);
   //ESP_Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

   
  
  
  if (actionFlag)
  {
    
  
  
  
    for(int i=0;i<20;i++) //size of inputs is the ammount of strings * 6, why? idk
    {
           
            Serial.print("input=  ");
            Serial.println(arrayOut[i]);
//            Serial.print("moveKey=  ");
//            Serial.println(getMoveKey(arrayOut[i]));

       switch(getMoveKey(arrayOut[i]))
       {
            
            
        case 0:
          {
           
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
           
            setAngle(45);
            analogWrite(A1O,0);
            analogWrite(A2O,speed);
            analogWrite(B1O,0);
            analogWrite(B2O,speed);
            delay(210);
        
          break;
         };
         default:
         break;
         //Serial.println("Case error!");
      } 
    }
    analogWrite(B1O,0);
        analogWrite(B2O,0);
        analogWrite(A1O,0);
        analogWrite(A2O,0);
    delay(3000);
    setAngle(0);
    actionFlag = false;
  }
  


else{
        analogWrite(B1O,0);
        analogWrite(B2O,0);
        analogWrite(A1O,0);
        analogWrite(A2O,0);
    waitForInput();
    
    }
}
