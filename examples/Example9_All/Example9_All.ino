/*
  Reading lat and long via UBX binary commands - no more NMEA parsing!
  By: Nathan Seidle
  SparkFun Electronics
  Date: January 3rd, 2019
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example shows how to query a Ublox module for its lat/long/altitude. Leave NMEA
  parsing behind. Now you can simply ask the module for the datums you want!

  Feel like supporting open source hardware?
  Buy a board from SparkFun!
  ZED-F9P RTK2: https://www.sparkfun.com/products/15136
  NEO-M8P RTK: https://www.sparkfun.com/products/15005
  SAM-M8Q: https://www.sparkfun.com/products/15106

  Hardware Connections:
  Plug a Qwiic cable into the GPS and a BlackBoard
  If you don't have a platform with a Qwiic connection use the SparkFun Qwiic Breadboard Jumper (https://www.sparkfun.com/products/14425)
  Open the serial monitor at 115200 baud to see the output
*/

#include <Wire.h> //Needed for I2C to GPS

#include "SparkFun_Ublox_Arduino_Library.h" //http://librarymanager/All#SparkFun_Ublox_GPS
SFE_UBLOX_GPS myGPS;

long lastTime = 0; //Simple local timer. Limits amount if I2C traffic to Ublox module.

void setup()
{
  Serial.begin(115200);
  while (!Serial); //Wait for user to open terminal
  Serial.println("Reading Lat/Long Example");

  Wire.begin();

  myGPS.begin(); //Connect to the Ublox module using Wire port
  if (myGPS.isConnected() == false)
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  //Wire.setClock(400000); //Increase I2C clock speed to 400kHz

  /*byte response;
    response = myGPS.getVal(VAL_GROUP_I2C, VAL_ID_I2C_ADDRESS, VAL_GROUP_I2C_SIZE, VAL_LAYER_RAM);
    Serial.print("res: 0x");
    Serial.println(response, HEX);

    delay(100);

    response = myGPS.getVal(VAL_GROUP_I2COUTPROT, VAL_ID_I2COUTPROT_NMEA, VAL_GROUP_I2COUTPROT_SIZE, VAL_LAYER_RAM);
    Serial.print("res: 0x");
    Serial.print(response, HEX);
    while(1);*/


  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGPS.setNavigationFrequency(4); //Set output to 4 times a second

  byte rate = myGPS.getNavigationFrequency(); //Get the update rate of this module
  Serial.print("Update rate:");
  Serial.println(rate);

  while (1);

  /*long pos = myGPS.getPositionAccuracy();
    Serial.print("pos: ");
    Serial.println(pos);

    byte version = myGPS.getProtocolVersionHigh();
    Serial.print("version: ");
    Serial.println(version);*/

  long latitude = myGPS.getLatitude();
  Serial.print(F("Lat: "));
  Serial.print(latitude);

  long longitude = myGPS.getLongitude();
  Serial.print(F(" Long: "));
  Serial.print(longitude);

  long altitude = myGPS.getAltitude();
  Serial.print(" Alt (above mean sea level): ");
  Serial.print(altitude);
  Serial.print(" (mm)");

  byte SIV = myGPS.getSIV();
  Serial.print(" SIV: ");
  Serial.print(SIV);

  byte fixType = myGPS.getFixType();
  Serial.print(" Fix: ");
  Serial.print(fixType);

  byte RTK = myGPS.getCarrierSolutionType();
  Serial.print(" RTK: ");
  Serial.print(RTK);
  if (RTK == 1) Serial.println("High precision float fix!");
  if (RTK == 2) Serial.println("High precision fix!");

  long speed = myGPS.getGroundSpeed();
  Serial.print(" Speed: ");
  Serial.print(speed);
  Serial.print(" (mm/s)");

  long heading = myGPS.getHeading();
  Serial.print(" Heading: ");
  Serial.print(heading);
  Serial.print(" (degrees * 10^-5)");

  int pDOP = myGPS.getPDOP();
  Serial.print(" pDOP: ");
  Serial.print(pDOP / 100.0, 2);

  while (1);
}

void loop()
{
  /*  myGPS.checkUblox(); //See if new data is available. Process bytes as they come in.

    delay(250); //Don't pound too hard on the I2C bus

    //Every other second print the current 3D position accuracy
    if (millis() - lastTime > 1000)
    {
      long latitude = myGPS.getLatitude();
      Serial.print("Lat: ");
      Serial.print(latitude);

      while (1);

      long longitude = myGPS.getLongitude();
      Serial.print(" Long: ");
      Serial.print(longitude);
      Serial.print(" (degrees * 10^-7)");

      long altitude = myGPS.getAltitude();
      Serial.print(" Alt (above mean sea level): ");
      Serial.print(altitude);
      Serial.print(" (mm)");

      long altitudeEllipsoid = myGPS.getAltitudeEllipsoid();
      Serial.print(" AltMSL (above Ellipsoid model surface of earth): ");
      Serial.print(altitudeEllipsoid);
      Serial.println(" (mm)");
    }*/

}
