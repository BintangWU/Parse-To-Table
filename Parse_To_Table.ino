int table[10][15];

String dataIn;
bool inCommingByte = false;

String tableName = "";
String buff[12];

byte cnt, ID, index;

//Data TX
//FT#31,30,30,30,30,32,34,34,34,32,32,33,33,30,1#31,30,30,30,30,32,34,34,34,32,32,33,33,30,2#

void setup() {
  Serial.begin(115200);
  Serial.flush();
  Serial.println("Ready!!!");
}

void loop() {
  if (inCommingByte) {
    int cnt = 0;
    buff[cnt] = ""; //Buffer nilai tabel per ID

    byte separatorOne = dataIn.indexOf('#');
    tableName = dataIn.substring(0, separatorOne);

    for (int i = separatorOne + 1; i < dataIn.length(); i++) {
      if (dataIn[i] == '#') {
        if (cnt < 10) cnt++;
        else          cnt = 0;
        buff[cnt] = "";
      }
      else
        buff[cnt] = buff[cnt] + dataIn[i];
    }
    ID = 0;

    if (tableName == "FT") {
      //      Serial.println("Tabel ditemukan");
      //      Serial.println("Jumlah ROW: " + String(cnt));

      do {
        index = 0;
        String temp = buff[ID];
        String tempValue = "";

        for (int i = 0; i < temp.length(); i++) {
          if (temp[i] == ',') {
            index++; //Index counter
            tempValue = "";
            //            Serial.print(" ");
          }
          else {
            tempValue = tempValue + temp[i];
            //            Serial.print(tempValue.toInt());
            table[ID][index] = tempValue.toInt();
          }
        }
        //        Serial.println();
        ID++;
      }
      while (ID < cnt);
      //      Serial.println();
    }
    else
      Serial.println("Tabel tidak ditemukan!");

    //Read table variable
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 15; j++) {
        Serial.print(table[i][j]);
        Serial.print(" ");
      }
      Serial.println();
    }

    inCommingByte = false;
    dataIn = "";
  }
}

void serialEvent() {
  if (Serial.available() > 0) {
    char received = (char)Serial.read();
    dataIn += received;

    if (received == '\n') {
      inCommingByte = true;
      received = NULL;
    }
  }
}
