// --------------------------------------------------------------------------
//               Radiohead example code - RF22 MESH CLIENT/SERVER
// --------------------------------------------------------------------------


// // ---------------------------- Client -------------------------------------

// rf22_mesh_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, routed reliable messaging client
// with the RHMesh class.
// It is designed to work with the other examples rf22_mesh_server*
// Hint: you can simulate other network topologies by setting the 
// RH_TEST_NETWORK define in RHRouter.h

// Mesh has much greater memory requirements, and you may need to limit the
// max message length to prevent wierd crashes
// #define RH_MESH_MAX_MESSAGE_LEN 50
#define RH_MESH_MAX_MESSAGE_LEN 200

//#define RH_TEST_NETWORK 5

#include <Arduino.h> // DEBUGGING
#include <RHMesh.h>
#include <RH_RF95.h> // CHANGED
#include <SPI.h>

// In this small artifical network of 4 nodes,
#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3
#define SERVER3_ADDRESS 4

// Singleton instance of the radio driver
RH_RF95 driver(12, 6); // CHANGED



// Class to manage message delivery and receipt, using the driver declared above
RHMesh manager(driver, CLIENT_ADDRESS);

// manager.init(); // SATCH ADDITION

// driver.setModemConfig(2);

void setup() 
{
  SerialUSB.begin(9600);
  if (!manager.init())
    SerialUSB.println("init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36

    // DEBUGGING
  // pinMode(LED_BUILTIN, OUTPUT);
  // for (int n = 0; n < 5; n++) {
  //   SerialUSB.print("check number" + String(n + 1));
  //   digitalWrite(LED_BUILTIN, HIGH);
  // }
  driver.setModemConfig(RH_RF95::Bw31_25Cr48Sf512);
  driver.setTxPower(20);
}

uint8_t data[] = "Hello World!";
//uint8_t data[] = "hi"; // SATCH SHORT MESSAGE TEST
// Dont put this on the stack:
uint8_t buf[RH_MESH_MAX_MESSAGE_LEN];

void loop()
{
  SerialUSB.println("Sending to manager_mesh_server3"); // UPDATE to the highest number server in the sequence?
  //SerialUSB.println("sending");  // SATCH SHORT MESSAGE TEST

  // Send a message to a rf22_mesh_server
  // A route to the destination will be automatically discovered.

  // // ---------------------- SERVER1 -------------------

  // if (manager.sendtoWait(data, sizeof(data), SERVER1_ADDRESS) == RH_ROUTER_ERROR_NONE) // UPDATE?
  // {
  //   // It has been reliably delivered to the next node.
  //   // Now wait for a reply from the ultimate server
  //   uint8_t len = sizeof(buf);
  //   uint8_t from;    
  //   if (manager.recvfromAckTimeout(buf, &len, 3000, &from))
  //   {
  //     SerialUSB.print("got reply from : 0x");
  //     SerialUSB.print(from, HEX);
  //     SerialUSB.print(": ");
  //     SerialUSB.println((char*)buf);
  //   }
  //   else
  //   {
  //     SerialUSB.println("No reply, is rf22_mesh_server1, rf22_mesh_server2 and rf22_mesh_server3 running?");
  //   }
  // }
  // else
  //    SerialUSB.println("sendtoWait failed. Are the intermediate mesh servers running?");

  // // ---------------------- SERVER2 -------------------

  // if (manager.sendtoWait(data, sizeof(data), SERVER2_ADDRESS) == RH_ROUTER_ERROR_NONE) // UPDATE?
  // {
  //   // It has been reliably delivered to the next node.
  //   // Now wait for a reply from the ultimate server
  //   uint8_t len = sizeof(buf);
  //   uint8_t from;    
  //   if (manager.recvfromAckTimeout(buf, &len, 3000, &from))
  //   {
  //     SerialUSB.print("got reply from : 0x");
  //     SerialUSB.print(from, HEX);
  //     SerialUSB.print(": ");
  //     SerialUSB.println((char*)buf);
  //   }
  //   else
  //   {
  //     SerialUSB.println("No reply, is rf22_mesh_server1, rf22_mesh_server2 and rf22_mesh_server3 running?");
  //   }
  // }
  // else
  //    SerialUSB.println("sendtoWait failed. Are the intermediate mesh servers running?");

  // // ------------------------------------------------

  // implementation with for loop to access multiple servers

  int max_server;
  max_server = 4;

  for (int i = 2; i < max_server + 1; i++) {
    if (manager.sendtoWait(data, sizeof(data), i) == RH_ROUTER_ERROR_NONE) { 
    // It has been reliably delivered to the next node.
    // Now wait for a reply from the ultimate server
    uint8_t len = sizeof(buf);
    uint8_t from;    
    if (manager.recvfromAckTimeout(buf, &len, 3000, &from)) {
      SerialUSB.print("got reply from : 0x"); // COMMENT OUT FOR SATCH SHORT MESSAGE TEST
      SerialUSB.print(from, HEX); // COMMENT OUT FOR SATCH SHORT MESSAGE TEST
      SerialUSB.print(": "); // COMMENT OUT FOR SATCH SHORT MESSAGE TEST
      SerialUSB.println((char*)buf);
    }
    else {
      SerialUSB.println("No reply, is rf22_mesh_server1, rf22_mesh_server2 and rf22_mesh_server3 running?");
      // SerialUSB.println("no reply"); // SATCH SHORT MESSAGE TEST
    }
  }
  else
    SerialUSB.println("sendtoWait failed. Are the intermediate mesh servers running?"); 
    // SerialUSB.println("sendtoWait failed"); // SATCH SHORT MESSAGE TEST
  }

  
}


//---------------------------- Server -------------------------------------


// rf22_mesh_server1.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, routed reliable messaging server
// with the RHMesh class.
// It is designed to work with the other examples rf22_mesh_*
// Hint: you can simulate other network topologies by setting the 
// RH_TEST_NETWORK define in RHRouter.h

// Mesh has much greater memory requirements, and you may need to limit the
// max message length to prevent wierd crashes
//#define RH_MESH_MAX_MESSAGE_LEN 50
#define RH_MESH_MAX_MESSAGE_LEN 200 // increase message length test

#include <RHMesh.h>
#include <RH_RF95.h> // CHANGED
#include <SPI.h>

// In this small artifical network of 4 nodes,
#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3
#define SERVER3_ADDRESS 4

// Singleton instance of the radio driver
RH_RF95 driver(12, 6); // CHANGED

// Class to manage message delivery and receipt, using the driver declared above
RHMesh manager(driver, SERVER1_ADDRESS); // UPDATE

void setup() 
{
  SerialUSB.begin(9600);
  //SerialUSB.print("server check");
  if (!manager.init())
    SerialUSB.println("RF22 init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
  driver.setModemConfig(RH_RF95::Bw31_25Cr48Sf512);
  driver.setTxPower(20);
}

uint8_t data[] = "And hello back to you from server1"; // UPDATE
//uint8_t data[] = "3";
// Dont put this on the stack:
uint8_t buf[RH_MESH_MAX_MESSAGE_LEN];
void loop()
{
  uint8_t len = sizeof(buf);
  uint8_t from;
  if (manager.recvfromAck(buf, &len, &from))
  {
    SerialUSB.print("got request from : 0x");
    SerialUSB.print(from, HEX);
    SerialUSB.print(": ");
    SerialUSB.println((char*)buf);

    // Send a reply back to the originator client
    if (manager.sendtoWait(data, sizeof(data), from) != RH_ROUTER_ERROR_NONE)
      SerialUSB.println("sendtoWait failed");
  }
  //delay(1000); // satch addition -- makes it easier to read
}
