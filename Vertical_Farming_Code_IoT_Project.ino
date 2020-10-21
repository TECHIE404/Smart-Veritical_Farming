/*
 ***************** Project: Code For Vertical Green  Farming***************** 
 * Project Details:
 * Sensor List:
 *              1- Soil Moisture Sensor x2 
 * Actuator's: 
 *            1-Water Pump/Motor
 *            2-Led Light
 *            
 * Project Working Details:
 *            We will measure Soil Moisture for every 6hrs time. If the value of the Soil Moisture if below the threshold value 
 *            then the Water pump will start for requried interval of time(In other words until the soil moisture goes above the 
 *            threshold value). 
 *            
 * Project Diagram:
 *                                        
 *                |            Sensor1     |
 *                |___________________-____| <----- Soil Layer 1
 *                |            Sensor2     |
 *                |___________________-____| <----- Soil Layer 2
 *                |                        |  
 *               _|_                      _|_
 *                         
 *   Soil Type/Dangerously Low Soil Moisture
 *   Fine(Clay)       /Below 60(Used For Layer 1)
 *   Medium(Loamy)    /Below70 (Used For Layer 2)
 *   Sandy(Sandy)     /Below80
 *   Default Time Interval  5 Minutes
 *   
 * Project DataBase
 *        1-Strong Data into Computer System:
 *              :By Default the data will store into desktop root_File/Vertical_Farming_log(Can't use becase use have to download external softwate example 'coolitem' )
 *        2-Strong Data into SD Card
 *               :By Default the data will store into SD_Card/Vertical_Farming_log/
 *               Connect:
 *               vcc->5v
 *               GND->GND
 *               MSO->12
 *               SOSI->11
 *               SCk->13
 *               SC->4
 *               
 *               
 */



const int sensor_pin1=A1;// Moisture Sensor For Layer1 Soil
const int sensor_pin2=A2;// Moisture Sensor For Layer2 Soil
const int pump=5;
void setup() {
    
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(pump,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(9600);
  while(!Serial)
  {
    Serial.println("Waiting For the Serial Port to connect!");
    Serial.println();
  }
}

void loop() {
  Serial.println();
  //---------Variable Declaration-----
  float moisture_percent1=0,moisture_percent2=0;
  float sensor_analog1=0,sensor_analog2=0;
  float threshold_value1=60,threshold_value2=75;
  //Threshold value will the percertage value.and it will depends on type of soil

  //---------Taking Analog Input----------
  sensor_analog1=analogRead(sensor_pin1);
  sensor_analog2=analogRead(sensor_pin2);

  //--------Convering analogData into MoisturePercentage--------- 
  moisture_percent1=(100-((sensor_analog1/1023.00)*100));
  moisture_percent2=(100-((sensor_analog2/1023.00)*100));

  //--------Displaying the Data on Serial Monitor
  Serial.print("Moisture Percentage for Sensor 1= ");
  Serial.print(moisture_percent1);
  Serial.print("%\n\n");
  Serial.print("Moisture Percentage for Sensor 2 = ");
  Serial.print(moisture_percent2);
  Serial.print("%\n\n");

  //--------Water Pump Operation-----------------
  if(moisture_percent1<=threshold_value1 || moisture_percent2<=threshold_value2){
    Serial.print("Stand by water pump in going to start in 30 secound for 2 minutes\nTime Left to start pump.");
    int timel=1,pump_time=0;
    while(timel<=30){Serial.print(".");timel++;delay(1000);}Serial.println();
        digitalWrite(pump,HIGH);
        Serial.print("Pump Status: Active\n");
        delay(1000*30);//delay for 2 minutes
        digitalWrite(pump,LOW);
        Serial.print("Pump Status: Inactive\n");
        
  }
  else{
    Serial.println("Every Thing is alright!");
  }
  delay(1000*60);//Time After which the loop will work again
  Serial.println();
  //default 1 min
}
