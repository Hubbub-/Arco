
// Read from serial
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  // A newline arrives:
  if (stringComplete) {
    Serial.println("-----------------------");
    Serial.print("String in: ");
    Serial.println(inputString);

    String numberString = inputString.substring(2,8);  // Get number following letter
    int numberIn = numberString.toInt();        // Convert number string to int

    // Get info by sending "i"
    if(inputString.startsWith("i")){  
      Serial.print("lastActed: ");
      Serial.println(lastActed);
      Serial.print("printBlocks(pb): ");
      Serial.println(printLDRs);
      Serial.print("printLDRs(pl): ");
      Serial.println(printBlocks);
      Serial.print("printTrigs(pt): ");
      Serial.println(printTrigs);
      Serial.print("printMoves(pm): ");
      Serial.println(printMoves);
      Serial.print("printStrips(ps): ");
      Serial.println(printStrips);
      Serial.print("bright(br...): ");
      Serial.println(bright);
      Serial.println("force trigger(ft...) 0-13");
      Serial.println("force mode(fm...) 0-3");
      Serial.println("force preset(fp...) 1-33");
    }
    

    // Control printing block values with "p"
    else if(inputString.startsWith("pb")){
      printBlocks=!printBlocks;
      byte eepromIn = printBlocks;
      EEPROM.write(printBlocksAddr, eepromIn);
      Serial.print("printBlocks(p): ");
      Serial.println(printBlocks);
    }

    // Control printing LDR values with "l"
    else if(inputString.startsWith("pl")){
      printLDRs=!printLDRs;
      byte eepromIn = printLDRs;
      EEPROM.write(printLDRAddr, eepromIn);
      Serial.print("printLDRs(l): ");
      Serial.println(printLDRs);
    }

    // Control printing trigger values with "t"
    else if(inputString.startsWith("pt")){
      printTrigs=!printTrigs;
      byte eepromIn = printTrigs;
      EEPROM.write(printTrigAddr, eepromIn);
      Serial.print("printTrigs(t): ");
      Serial.println(printTrigs);
    }
    
    // Control printing movement with "pm"
    else if(inputString.startsWith("pm")){
      printMoves=!printMoves;
      byte eepromIn = printMoves;
      EEPROM.write(printMovesAddr, eepromIn);
      Serial.print("printMoves(m): ");
      Serial.println(printMoves);
    }

    // Control printing strips with "ps"
    else if(inputString.startsWith("ps")){
      printStrips=!printStrips;
      byte eepromIn = printStrips;
      EEPROM.write(printStripsAddr, eepromIn);
      Serial.print("printStrips(s): ");
      Serial.println(printStrips);
    }

    
    // Control the brightness with string, examples: "br13" "br0" "br255"
    else if(inputString.startsWith("br")){  // Volume string
      if(inBounds(numberIn,0,255)){
        bright = numberIn;              // Change the volume
        FastLED.setBrightness(bright);
        EEPROM.write(brightAddress, bright);  // Save the brightness to eeprom
        Serial.print("bright(b...): ");
        Serial.println(bright);
      }
    }

    // Force trigger with "ft..."
    else if(inputString.startsWith("ft")){
      if(inBounds(numberIn,0,NUMLDRS-1)){
        trig(numberIn);
      }
    }

    // Force mode with "fm..."
    else if(inputString.startsWith("fm")){
      if(inBounds(numberIn,0,3)){
        forceMode = numberIn;
        mode = numberIn;
        Serial.print("forceMode: ");
        Serial.println(forceMode);
      }
    }

    // Force preset with "fp..."
    else if(inputString.startsWith("fp")){
      if(inBounds(numberIn,1,33)){
        preset(numberIn);
        Serial.print("Force preset");
        Serial.println(numberIn);
      }
    }


    Serial.println("-----------------------");

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

bool inBounds(int in, int low, int high){
  bool result = false;
  if(in >= low && in <= high) result = true;
  else{
    Serial.print("Value entered must be between ");
    Serial.print(low);
    Serial.print(" & ");
    Serial.println(low);
  }
  return result;
}

