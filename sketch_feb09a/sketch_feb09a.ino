#include <Wire.h>
#include <WireData.h>

const int myAddress = 0x08;
char myData;


void setup()
{
  Wire.begin(myAddress);
  Wire.onReceive(i2cReceive);
  Wire.onRequest(i2cRequest);
}

void loop()
{
  // Nothing to do - all the work is done in the Wire data handlers (onReceive, onRequest).
}

void i2cReceive(int byteCount)
{
  // Get and store the data.
  wireReadData(myData);
}

void i2cRequest()
{
  // FYI: The Atmel AVR 8 bit microcontroller provides for clock stretching while using
  // the ISR for the data request.  This is, by extension, happening here, since this
  // callback is called from the ISR.

  // Send the data.
  if (myData == 'a')
    wireWriteData("hello");
  else if (myData == 'b')
    wireWriteData("cats beat dogs");
  else
    wireWriteData(myData);
}
