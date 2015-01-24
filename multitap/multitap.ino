#define LATCH 2
#define CLOCK 3
#define DATA1 4
#define DATA2 5
#define IOPIN 6

int m_pad1 = 0;
int m_pad2 = 0;
int m_pad3 = 0;
int m_pad4 = 0;

int dpad = 0;
int first_dpad = -1;

void setup()
{
   Serial.begin(9600);
   
   pinMode(LATCH, OUTPUT);
   pinMode(CLOCK, OUTPUT);
   pinMode(DATA1, INPUT);
   pinMode(DATA2, INPUT);
   pinMode(IOPIN, OUTPUT);
} 
  

void loop()
{
  byte i;
   
  int pad1 = 0;
  int pad2 = 0;
  int pad3 = 0;
  int pad4 = 0;
  
  latch();
  
  digitalWrite(IOPIN, HIGH);
  delayMicroseconds(12);
  for (i = 0; i < 16; i++) {
     pad1 |= digitalRead(DATA1) << i;
     pad2 |= digitalRead(DATA2) << i;
     delayMicroseconds(12);
     digitalWrite(CLOCK, HIGH);
     delayMicroseconds(12);
     digitalWrite(CLOCK, LOW);
  }
  
  latch();
  
  digitalWrite(IOPIN, LOW);
  delayMicroseconds(12);
  for (i = 0; i < 16; i++) {
     pad3 |= digitalRead(DATA1) << i;
     pad4 |= digitalRead(DATA2) << i;
     delayMicroseconds(12);
     digitalWrite(CLOCK, HIGH);
     delayMicroseconds(12);
     digitalWrite(CLOCK, LOW);
  }
  
  pad1 = ~pad1;
  pad2 = ~pad2;
  pad3 = ~pad3;
  pad4 = ~pad4;
  
  if (pad1 != m_pad1) {
    Serial.println("Pad 1: ");
    parseState(m_pad1, pad1, 1);
    m_pad1 = pad1;
  }
  
  if (pad2 != m_pad2) {
    Serial.println("Pad 2: ");
    Serial.println(pad2, HEX);
    parseState(m_pad2, pad2, 2);
    m_pad2 = pad2;
  }
  
  if (pad3 != m_pad3) {
    Serial.println("Pad 3: ");
    parseState(m_pad3, pad3, 3);
    m_pad3 = pad3;
  }
  
  if (pad4 != m_pad4) {
    Serial.println("Pad 4: ");
    parseState(m_pad4, pad4, 4);
    m_pad4 = pad4;
  }
  
  //printState();
  
  delay(17);
  //delay(250);
}

void latch()
{
  digitalWrite(LATCH, HIGH);
  delayMicroseconds(12);
  digitalWrite(LATCH, LOW);  
}

void printState()
{
  Serial.print("Pad 1: ");
  Serial.println(m_pad1, HEX);
  Serial.print("Pad 2: ");
  Serial.println(m_pad2, HEX);
  Serial.print("Pad 3: ");
  Serial.println(m_pad3, HEX);
  Serial.print("Pad 4: ");
  Serial.println(m_pad4, HEX);  
}

void parseState(int old_state, int new_state, int ctrl)
{
  byte i, old_val, new_val;

  for (i = 0; i < 12; i++)
  {
      old_val = (old_state >> i) & 1;
      new_val = (new_state >> i) & 1;
      if ( (old_val == 0) && (new_val == 1) ) {
         Serial.print("Pressed ");
         PrintKey(i, 1, ctrl);
         //PressKey(i);
      } else if ( (old_val == 1) && (new_val == 0) ) {
         Serial.print("Released ");
         PrintKey(i, 0, ctrl);
         //ReleaseKey(i);         
      }
  } 
}

void PrintKey( int code, int pr, int ctrl ) 
{
   switch (code) {
      case 0:
        Serial.println("B");
        if (ctrl == 1)
            Joystick.button(1, pr);
        if (ctrl == 3)
            Joystick.button(9, pr);
        break;
      case 1:
        Serial.println("Y");
        if (ctrl == 1)
          Joystick.button(2, pr);
        if (ctrl == 3)
          Joystick.button(10, pr);
        break;     
      case 2:
        Serial.println("Select");
        if (ctrl == 1)
          Joystick.button(6, pr);
        if (ctrl == 3)
          Joystick.button(11, pr);        
        break;     
      case 3:
        Serial.println("Start");
        if (ctrl == 1)
          Joystick.button(5, pr);
        if (ctrl == 3)
          Joystick.button(12, pr);
        break;    
      case 4:
        Serial.println("Up");
        if (ctrl == 1) 
          Joystick.button(21, pr);
        if (ctrl == 3)
          Joystick.button(13, pr);
        break;      
      case 5:
        Serial.println("Down");
        if (ctrl == 1) 
          Joystick.button(22, pr);
        if (ctrl == 3)
          Joystick.button(14, pr);        
        break;      
      case 6:
        Serial.println("Left");
        if (ctrl == 1) 
          Joystick.button(23, pr);
        if (ctrl == 3)
          Joystick.button(15, pr);        
        break;      
      case 7:
        Serial.println("Right");
        if (ctrl == 1) 
          Joystick.button(24, pr);
        if (ctrl == 3)
          Joystick.button(16, pr);        
        break;      
      case 8:
        Serial.println("A");
        if (ctrl == 1)
          Joystick.button(3, pr);
        if (ctrl == 3)
          Joystick.button(17, pr);        
        break;     
      case 9:
        Serial.println("X");
        if (ctrl == 1)
          Joystick.button(4, pr);
        if (ctrl == 3)
          Joystick.button(18, pr);        
        break;     
      case 10:
        Serial.println("L");
        if (ctrl == 1)
          Joystick.button(7, pr);
        if (ctrl == 3)
          Joystick.button(19, pr);        
        break;     
      case 11:
        Serial.println("R");
        if (ctrl == 1)
          Joystick.button(8, pr);
        if (ctrl == 3)
          Joystick.button(20, pr);
        break;     
      default:
        break;  
    }     
}
