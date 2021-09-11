/*
* NOTE: Button center is positive wire. Borders eq. ground
*/

#include "OneWire.h"

#define used_pin 10
#define _DEBUG

// KEY_TO_WRITE. SET KEY YOU WANNA WRITE RIGHT HERE
byte key_to_write[] = { 0x01, 0x5F, 0x69, 0xB, 0x1, 0x0, 0x0, 0xEA };

OneWire  ds(used_pin);  // pin 10 is 1-Wire interface pin now

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  byte i;
  byte read_data[8];

  delay(1000); // 1 sec
  
  read_key(read_data);
  
  if (print_key_connected_status(read_data))
    return;
  
  print_key(read_data, 8);
  
  if (validate_key(read_data))
    return;
  
  if (!checkTypeRW1990()){
    Serial.println("Not RW1990. Not supported.");
    return;
  }
  // UNCOMMENT THIS SECTION FOR FLASHING KEY
  /*
  flash(); 
  read_key(read_data);
  print_key(read_data, 8);
  */
}

void read_key(byte* read_data){ 
  ds.reset();
  ds.write(0x33); // "READ" command
  ds.read_bytes(read_data, 8);
}
boolean print_key_connected_status(byte read_data[]){
  // Check if FF:FF:FF:FF:FF:FF:FF:FF . MOST LIKELY (but not always) NOTHING IS PLUGGED IN
  if (read_data[0] & read_data[1] & read_data[2] & read_data[3] & read_data[4] & read_data[5] & read_data[6] & read_data[7] == 0xFF){
    Serial.print("."); 
    return true;
  }
  return false;
}

void print_key(byte *key_array, int size){
  Serial.println();
  Serial.print("[");
  for(int i = 0; i < size; i++) {
    Serial.print(key_array[i], HEX);
    if (i != 7) 
      Serial.print(":");
  }
  Serial.println("]");
}

boolean validate_key(byte read_data[]){
  // Check if read key is equal to one that has to be programmed
  for (int i = 0; i < 8; i++){
    if (read_data[i] != key_to_write[i])
        return false;
  }
  Serial.print(" programmed to KEY requested");
  return true;
}

boolean checkTypeRW1990(){
  ds.reset();
  ds.write(0xD1);          // attend to remove write flag
  ds.write_bit(1);
  delay(10);
  pinMode(used_pin, INPUT); 

  ds.reset();
  ds.write(0xB5);          // Request write flag stat
  byte reply = ds.read();
  #ifdef DEBUG
  Serial.print("Reply RW-1990.1: "); 
  Serial.println(reply, HEX);
  #endif
  if (reply == 0xFE)       // 0xFE eq. RW-1990, RW-1990.1, ТМ-08, ТМ-08v2 
    return true;
  return false;
}

void flash(){
  ds.reset();
  ds.write(0xD1);                    // write command
  ds.write_bit(0);
  delay(10);
  pinMode(used_pin, INPUT); 
  ds.reset();
  ds.write(0xD5);     
  for (byte i = 0; i < 8; i++){
    BurnByte(~key_to_write[i]);      // invert 4 RW1990.1
    Serial.print('+');
  } 
  
  ds.write(0xD1);                         // write flag
  ds.write_bit(1);                        // stop
  pinMode(used_pin, INPUT); 
  delay(10);
}

void BurnByte(byte data){
  for(byte n_bit = 0; n_bit < 8; n_bit++){ 
    ds.write_bit(data & 1);  
    delay(5);                        // даем время на прошивку каждого бита до 10 мс
    data = data >> 1;                // переходим к следующему bit
  }
  pinMode(used_pin, INPUT);
}
