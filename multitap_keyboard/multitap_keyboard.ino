#define LATCH 2
#define CLOCK 3
#define DATA1 4
#define DATA2 5
#define IOPIN 6

int m_pad1 = 0;
int m_pad2 = 0;
int m_pad3 = 0;
int m_pad4 = 0;

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
    parseState(m_pad1, pad1);
    m_pad1 = pad1;
  }
  
  if (pad2 != m_pad2) {
    Serial.println("Pad 2: ");
    Serial.println(pad2, HEX);
    parseState(m_pad2, pad2);
    m_pad2 = pad2;
  }
  
  if (pad3 != m_pad3) {
    Serial.println("Pad 3: ");
    parseState(m_pad3, pad3);
    m_pad3 = pad3;
  }
  
  if (pad4 != m_pad4) {
    Serial.println("Pad 4: ");
    parseState(m_pad4, pad4);
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

void parseState(int old_state, int new_state)
{
  byte i, old_val, new_val;

  for (i = 0; i < 12; i++)
  {
      old_val = (old_state >> i) & 1;
      new_val = (new_state >> i) & 1;
      if ( (old_val == 0) && (new_val == 1) ) {
         Serial.print("Pressed ");
         PrintKey(i, 1);
      } else if ( (old_val == 1) && (new_val == 0) ) {
         Serial.print("Released ");
         PrintKey(i, 0);       
      }
  } 
}

void PrintKey( int code, int pr ) 
{
   switch (code) {
      case 0:
        Serial.println("B");
        if(pr == 1) 
          Keyboard.print('c');
        Joystick.button(1, pr);   
        break;
      case 1:
        Serial.println("Y");
        if(pr == 1) 
          Keyboard.print('x');
        break;     
      case 2:
        Serial.println("Select");
        if(pr == 1) {
          Keyboard.print(' ');
        }
        break;     
      case 3:
        Serial.println("Start");
        if(pr == 1) {
          Keyboard.set_key1(KEY_ENTER);
          Keyboard.send_now();
          Keyboard.set_key1(0);
          Keyboard.send_now();
        }
        break;    
      case 4:
        Serial.println("Up");
        if(pr == 1) {
          Keyboard.set_key2(KEY_UP);
          Keyboard.send_now();
        } else {
          Keyboard.set_key2(0);
          Keyboard.send_now(); 
        }
        break;      
      case 5:
        Serial.println("Down");
        if(pr == 1) {
          Keyboard.set_key2(KEY_DOWN);
          Keyboard.send_now();
        } else {
          Keyboard.set_key2(0);
          Keyboard.send_now(); 
        }
        break;      
      case 6:
        Serial.println("Left");
        if(pr == 1) {
          Keyboard.set_key3(KEY_LEFT);
          Keyboard.send_now();
        } else {
          Keyboard.set_key3(0);
          Keyboard.send_now(); 
        }
        break;      
      case 7:
        Serial.println("Right");
        if(pr == 1) {
          Keyboard.set_key3(KEY_RIGHT);
          Keyboard.send_now();
        } else {
          Keyboard.set_key3(0);
          Keyboard.send_now(); 
        }
        break;      
      case 8:
        Serial.println("A");
        if(pr == 1) 
          Keyboard.print('d');
        break;     
      case 9:
        Serial.println("X");
        if(pr == 1) 
          Keyboard.print('s');
        break;     
      case 10:
        Serial.println("L");
        if(pr == 1) 
          Keyboard.print('a');
        break;     
      case 11:
        Serial.println("R");
        if(pr == 1) 
          Keyboard.print('z');
        break;     
      default:
        break;  
    }     
}
