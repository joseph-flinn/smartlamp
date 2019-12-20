### DIY Smart Lamp
Because of my background in cyber security, I am very hesitant to jump head
first into the world of IoT and bringing them into my house. As a side note, the
FBI has warned all consumers to keep their IoT devices on a separate network 
than the rest of their devices (pretty sure modern routers are capable of doing
this). This background has led me to create my own wifi enabled lamps. 

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

### What's Next
+ Creating some sort of user interface to interact with the api
+ Adding simple authentication?