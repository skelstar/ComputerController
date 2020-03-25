#ifndef UNIT_TEST

#ifdef DEBUG_SERIAL
#define DEBUG_OUT Serial
#endif
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <i2cEncoderLibV2.h>

//------------------------------------------------------------------

#define ENCODER_BRAKE_COUNTS 20
#define ENCODER_ACCEL_COUNTS 20

i2cEncoderLibV2 encoder(0x01);

//---------------------------------------------------------------

#include <Button2.h>

#define BUTTON_35 35
Button2 button35(BUTTON_35);
Button2 button0(0);

void onEncoderChange(i2cEncoderLibV2 *enc)
{
  Serial.printf("Encoder changed: %d\n", enc->readCounterByte());
}

//---------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.printf("Ready");

  Wire.begin();

  encoder.reset();
  encoder.begin(i2cEncoderLibV2::INT_DATA |
                i2cEncoderLibV2::WRAP_DISABLE |
                i2cEncoderLibV2::DIRE_RIGHT |
                i2cEncoderLibV2::IPUP_ENABLE |
                i2cEncoderLibV2::RMOD_X1 |
                i2cEncoderLibV2::STD_ENCODER);

  encoder.writeCounter((int32_t)0);    /* Reset the counter value */
  encoder.writeMax(100);               /* Set the maximum threshold*/
  encoder.writeMin(0);                 /* Set the minimum threshold */
  encoder.writeStep((int32_t)1);       /* Set the step to 1*/
  encoder.writeAntibouncingPeriod(20); /* Set an anti-bouncing of 200ms */
  encoder.writeDoublePushPeriod(50);   /*Set a period for the double push of 500ms */

  encoder.writeCounter(0);
  encoder.updateStatus();

  encoder.onDecrement = onEncoderChange;
  encoder.onIncrement = onEncoderChange;
  // encoder.onButtonPush = _encoderButtonPushedCb;
  // encoder.onButtonDoublePush = _encoderButtonDoubleClickCb;
}
//---------------------------------------------------------------

void loop()
{
  encoder.updateStatus();
}
//------------------------------------------------------------------

#endif