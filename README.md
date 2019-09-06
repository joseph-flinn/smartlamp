REST API:

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
