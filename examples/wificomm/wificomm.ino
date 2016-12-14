#include <RelayRace.h>
#include <BRCClient.h>

/* If you are using UNO, uncomment the next line. */
 #define UNO
/* If you are using MEGA and want to use HardwareSerial,
 * umcomment the next 2 lines. */
// #define USE_HARDWARE_SERIAL
// #define HW_SERIAL Serial2

#ifdef UNO
 #define UART_RX 3
 #define UART_TX 2
#else
 #define UART_RX 10
 #define UART_TX 2
#endif

#if !defined(UNO) && defined(USE_HARDWARE_SERIAL)
 BRCClient brcClient(&HW_SERIAL);
#else
 BRCClient brcClient(UART_RX, UART_TX);
#endif

// You have to modify the corresponding parameter
#define AP_SSID    "HMKRL"
#define AP_PASSWD  "hatsune39"
#define TCP_IP     "192.168.43.1"
#define TCP_PORT   5000
#define MY_COMM_ID 0x36

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  brcClient.begin(9600);
  brcClient.beginBRCClient(AP_SSID, AP_PASSWD, TCP_IP, TCP_PORT);

  RelayRace race(&brcClient, MY_COMM_ID);
  race.registerID();
  race.waitLaunchSignal();
  Serial.print("LIFT OFF!!!");

  //Put your car operation code here

  race.sendReachSignal();
}

void loop()
{

}
