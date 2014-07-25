int clk = 8;
int data = 9;
int silent = 10;

int halfPeriod = 5;
int currentVal = 0;

double R2 = 10e3;
double Cap = 0.1e-6;

// 1   713
// 2   683
int S = 1;
int A = 53;
int B = 66;
int C = 72;
int Cs = 76;
int D = 82;
int E = 90;
int F = 94;
int Fs = 98;
int G = 103;
int Gs = 106;
int Ap = 109;

int keys[] = {
  18, // G
  26, // G#
  35,  // A
  40,     // A# + 4
  48,  // B + 7
  55,  // C + 6
  60,  // C# + +4
  65,  // D 6
  69  ,   // D# 4
  74,  // E 4
  79,  // F 4
  83,  // F# 4
  87, // G 5
  90, // G# 3
  94, // A 3
  98, // A# 
  100, // B
  103, // C
  106, // C#
  109, // D
  111, // D#
  114, // E
  116, // F
  118, // F#
  120, // G
  122, // G#
  123, // A
};


void doNPulses(int n) {
  for (int i = 0; i < n; i++) {
    delayMicroseconds(halfPeriod);
    digitalWrite(clk, LOW);
    delayMicroseconds(halfPeriod);
    digitalWrite(clk, HIGH);
  }
  delayMicroseconds(halfPeriod);
}

void setVal(int val) {
  digitalWrite(data, HIGH);
  doNPulses(127);
  digitalWrite(data, LOW);
  doNPulses(val);
}

void setR(double r) {
  setVal(r * (66e3/128.0));
}

void setFreq(double f) {
  double r = 1.44/(f*C)-2*R2;
  Serial.println(r);
  setR(r);
}

void setup() {
  Serial.begin(115200);
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(silent, OUTPUT);
  digitalWrite(silent, LOW);
  setVal(1);
  //digitalWrite(data, LOW);
  //digitalWrite(clk, HIGH);
}

int notes[] = {Cs, B, A, B, Cs, Cs, Cs, S, B, B ,B, S, Cs, E ,E, S,
Cs, B, A, B, Cs, Cs, Cs, Cs, B, B, Cs, B, A, S, S, S};

void p(int val) { 
  setVal(val);
  delay(200);
}

void loop() {
 /** digitalWrite(10, HIGH);
    int num = Serial.parseInt();
    if (num == -1)
      setVal(0);
    else if (num > 0)
      setVal(num);
    Serial.println(num);
   */

    for(int i = 0; i < 32; i++) { 
     // if (notes[i] == S) {
     //   digitalWrite(silent, LOW);
     //   delay(200);
     // } else {
     //   digitalWrite(silent, HIGH);
     // p(notes[i]);}
      if (Serial.available() > 0) {
        int n = Serial.read();
        if (n == 255) { digitalWrite(silent, LOW); }
          
        else {
          digitalWrite(silent, HIGH);
          setVal(keys[n]);
        }
        Serial.println(n);
      }
    }
  
    
 // while(int num = Serial.parseInt() > 0) {
   
//  for(int i = 0;i < 100e3; i++) {
//  setR(i);
//  delayMicroseconds(1);
//  }
  //for(int i = 1; i < 128; i++) {
  //  setVal(i);
 //   delay(100);
 // }
 // for(int i = 128; i > 0; i--) {
  //  setVal(i);
  //  delay(100);
 // }
  //setVal(64);
  //setVal(128);
  //delay(10000);
}
