#include <Servo.h>
#include <XBee.h>

Servo servo;
XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse();

const int SERVO_MOTOR_PIN = 3;

void setup() {
  xbee.begin(9600);
  servo.attach(SERVO_MOTOR_PIN);
}

void loop() {
  char command[2] = {0};
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
      xbee.getResponse().getZBRxResponse(zbRx);
      strncpy(command, (char *)zbRx.getData(), sizeof(command));
      
      if (String(command) == "1") {
        servo.write(135);
        delay(1000);
        servo.write(90);
      } else if(String(command) == "2") {
        servo.write(45);
        delay(1000);
        servo.write(90);
      }
    }
  }
  delay(1000);
}
