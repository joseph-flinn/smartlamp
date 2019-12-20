### DIY Smart Lamp
Because of my background in cyber security, I am very hesitant to jump head
first into the world of IoT and bringing them into my house. As a side note, the
FBI has warned all consumers to keep their IoT devices on a separate network 
than the rest of their devices (pretty sure modern routers are capable of doing
this). This background has led me to create my own wifi enabled lamps. 

Built on top of a wireless enabled arduino type device for a very small
footprint.

### REST API:

--GET-- 
+ / - Welcome to Web Server
+ /leds - returns json if an led exists
+ `curl -i http://ip-address`
+ `curl -i http://ip-address/leds`

--POST--
+ /leds - creates an led
+ `curl -X POST -H "Content-Type: application/json" -d '{"id":1, "gpio":13, "status": 1}' -i http://ip-address/leds`

--PUT--
+ /leds - updates an led
+ `curl -X PUT -H "Content-Type: application/json" -d '{"id":1, "gpio":13, "status": 0}' -i http://ip-address/leds`


Note: "status" == 1 means led on

PWM RGB: 1024 is off, 0 is on

### Parts List
+ [RGB Amplifiers](https://www.amazon.com/SUPERNIGHT-Lights-Channels-Amplifier-Repeater/dp/B01LZAVJJL/ref=pd_sbs_60_3/136-3110762-0813959?_encoding=UTF8&pd_rd_i=B01LZAVJJL&pd_rd_r=0d5828e4-324e-11e9-acf9-71fc83dc301e&pd_rd_w=3lBCV&pd_rd_wg=OhYFF&pf_rd_p=588939de-d3f8-42f1-a3d8-d556eae5797d&pf_rd_r=AWDWRBXG9J1T1NWEY6K0&psc=1&refRID=AWDWRBXG9J1T1NWEY6K0) - $14.99/2pc
+ [LED Strips](https://www.amazon.com/SUPERNIGHT-Waterproof-300LEDs-Changing-Flexible/dp/B00DTOAWZ2/ref=pd_bxgy_267_2/136-3110762-0813959?_encoding=UTF8&pd_rd_i=B00DTOAWZ2&pd_rd_r=5f88618f-324b-11e9-a6c1-83a6775f2fe5&pd_rd_w=zXYES&pd_rd_wg=AFCyE&pf_rd_p=6725dbd6-9917-451d-beba-16af7874e407&pf_rd_r=97XMBT53S2PTWARD158J&psc=1&refRID=97XMBT53S2PTWARD158J) {5A/strip} - $11.98/pc
+ [ESP8266 NodeMCU](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010N1SPRK/ref=asc_df_B010O1G1ES/?tag=hyprod-20&linkCode=df0&hvadid=309818716690&hvpos=1o1&hvnetw=g&hvrand=4638120028514079272&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9033789&hvtargid=pla-361876718784&th=1) - $6.00/pc
+ [12V/5A Power Supply](https://www.amazon.com/dp/B008FKDK2M/ref=emc_b_5_t) - $9.98
+ [Extension Cable](https://www.amazon.com/C-able-Extension-Lights-Extend-Connectors/dp/B07FDW4M89/ref=pd_sim_86_2/136-3110762-0813959?_encoding=UTF8&pd_rd_i=B07FDW4M89&pd_rd_r=19a08995-324e-11e9-be6e-798520fb1ea5&pd_rd_w=HAKyi&pd_rd_wg=X4JN2&pf_rd_p=90485860-83e9-4fd9-b838-b28a9b7fda30&pf_rd_r=6Q32Z8FXHNCM3JEEYBZK&psc=1&refRID=6Q32Z8FXHNCM3JEEYBZK) - $19.90
+ [Voltage Step Down module](https://www.amazon.com/Converter-Module-LM2596S-ADJ-3-2V-40V-1-25V-35V/dp/B07DMGPB9R/ref=pd_day0_hl_263_6/136-3110762-0813959?_encoding=UTF8&pd_rd_i=B07DMGPB9R&pd_rd_r=18262d94-37c9-11e9-9879-bb7f1328ddae&pd_rd_w=Cprew&pd_rd_wg=pIEv1&pf_rd_p=ad07871c-e646-4161-82c7-5ed0d4c85b07&pf_rd_r=XJVMR014A7FEGBVSE93X&psc=1&refRID=XJVMR014A7FEGBVSE93X) - $6.99

### What's Next
+ Creating some sort of user interface to interact with the api
  + Artificial Intelligence presence detector
  + Thermal instead of motion because I work on a computer without moving a lot
  + Maybe a [PIR sensor](https://makezine.com/projects/presence-lights/) or sensor array
+ Adding simple authentication?