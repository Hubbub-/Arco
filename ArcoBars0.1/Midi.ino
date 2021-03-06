
void midiTrig(int in){
  // Side buttons
  if(in == 2){    // top side button selects blueHue
    controlling = 0;
    hue = blueHue;
    sat = 255;
  }
  else if(in == 3){  // 2nd side button selects redHue
    controlling = 1;
    hue = redHue;
    sat = 255;
  }
  else if(in == 4){
    controlling = 2;
    hue = WARMHUE;
    sat = whiteSat;
  }
  else if(in == 5){   // 4th side button reverses direction
    
  }
  else if(in == 6){  // bottom side button resets timing
    beatStart = millis()+50;
  }
//
//
//  //top row
//  else if(in == 44){
//    setting[0]=0;
//  }
//  else if(in == 45){
//    setting[0]=1; 
//  }
//  else if(in == 46){
//    setting[0]=2;
//  }
//  else if(in == 47){
//    setting[0]=3; 
//  }
//
  //top big row
  else if(in == 40){
    hue = blueHue;
    sat = 255;
    bright = 255;
  }
  else if(in == 41){
    hue = redHue;
    sat = 255;
    bright = 255;
  }
  else if(in == 42){
    hue = WARMHUE;
    sat = whiteSat;
    bright = 255;
  }
  else if(in == 43){
    bright = 0;
  }
//  
//  // bottom big row
  else if(in == 36){
    pulsing=false;
    bright = 255;
  }
  else if(in == 37){
    pulsing = true;
    pulseSpeed = 1;
  }
  else if(in == 38){
    pulsing = true;
    pulseSpeed = 2;
  }
  else if(in == 39){
    delay(4000);
    
    for(int i=0; i<NUMLEDS; i++){
      byte b = map(i,0,NUMLEDS,0,255);
      allBars(i,0,0,b);
      FastLED.show();
      delay(1);
    }
    for(int i=NUMLEDS-1; i>0; i--){
      allBars(i,0,0,255);
      FastLED.show();
      delay(1);
    }
    hue = WARMHUE;
    sat = whiteSat;
    bright = 255;
  }
//
//  //bottom row
//  if(in == 32){
//    setting[2]=0;
//  }
//  else if(in == 33){
//    setting[2]=1;
//  }
//  else if(in == 34){
//    setting[2]=2;
//  }
//  else if(in == 35){
//    setting[2]=3;
//  }
//
//  // update preset when bottom row pressed
//  if(in >= 32 && in <= 35) preset(settingMap[setting[0]][setting[1]][setting[2]]);
//  Serial.println(" ");
}

void slideControl(int val){
  if(controlling==0){        // bluehue
    blueHue = map(val,0,127,GREENHUE,BLUEHUE);
    EEPROM.write(blueHueAddr, blueHue);
    hue = blueHue;
    sat = 255;
  }
  else if(controlling==1){    // redhue
    int r = map(val,0,127,REDHUE,255+ORANGEHUE);
    if(r>255) r-=255;
    redHue = r;
    EEPROM.write(redHueAddr, redHue);
    hue = redHue;
    sat = 255;
  }
  else if(controlling==2){    // warmth
    whiteSat = map(val,0,127,0,WARMSAT);
    EEPROM.write(whiteSatAddr, whiteSat);
    hue = WARMHUE;
    sat = whiteSat;
  }

}



void OnNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("MIDI note=");
  Serial.print(note, DEC);
  Serial.println();
  midiTrig(note);
}

void OnControlChange(byte channel, byte control, byte value) {
  Serial.print("Slider value=");
  Serial.print(value, DEC);
  Serial.println();
  slideControl(value);

}
