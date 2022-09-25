#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_RFM95
#define MY_DEBUG_VERBOSE_RFM95
#define MY_RFM95_RST_PIN 14
#define MY_RFM95_CS_PIN 18
#define MY_RFM95_IRQ_PIN 26
#define MY_RFM95_IRQ_NUM MY_RFM95_IRQ_PIN
#define MY_SOFT_SPI_MOSI_PIN 27
#define MY_SOFT_SPI_SCK_PIN 5
#define MY_RFM95_FREQUENCY (RFM95_868MHZ)
#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128


#define MY_NODE_ID 44


#include <SPI.h>
#include <MySensors.h>  
#include <NewPing.h>

#define SENSOR_NAME "Distance Sensor"
#define SENSOR_VERSION "1.1"

#define CHILD_ID 1  // Each radio node can report data for up to 254 different child sensors. You are free to choose the child id yourself. 
                    // You should avoid using child-id 255 because it is used for things like sending in battery level and other (protocol internal) node specific information.
#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
unsigned long SLEEP_TIME = 21600000; // Sleep time between reads (in milliseconds)   900000 = 15min, 21600000 = 6h


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
MyMessage msg(CHILD_ID, V_DISTANCE);
int lastDist;
bool metric = true;

void setup()  
{ 
  metric = getControllerConfig().isMetric;
}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo(SENSOR_NAME, SENSOR_VERSION);

  // Register all sensors to gw (they will be created as child devices) by their ID and S_TYPE
  present(CHILD_ID, S_DISTANCE);
}

void loop()      
{ 
  // use the build-in digital filter to discard out of range pings
  int echoTime = sonar.ping_median(10);
  int dist = metric?sonar.convert_cm(echoTime):sonar.convert_in(echoTime);
  Serial.print("Ping: ");
  Serial.print(dist);
  Serial.println(metric?" cm":" in");

  if (dist != lastDist) {
      send(msg.set(dist));
      lastDist = dist;
  }

  wait(SLEEP_TIME);
}




void setup()  
{ 

}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo(SENSOR_NAME, SENSOR_VERSION);

}

void loop()      
{ 

  }
