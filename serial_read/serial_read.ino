int incomingByte = 0;   // for incoming serial data

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read() - 48;
                if (0 > incomingByte)
                {
                  return; 
 // makes sure that you don't get anything with an ASCII value below "0"
                }
                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }
}
