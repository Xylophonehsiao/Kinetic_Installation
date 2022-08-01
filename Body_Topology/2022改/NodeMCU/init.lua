-- write by Hsiao YL 2022.07.27
-- set mcu to ap mode, and connect to the computer successfully~
-- 2020.08.01
-- successful to control LED through TCP/IP
-- 
local LEDpin = 4 --onbroad LED pgio4
local status = gpio.HIGH
local duration = 1000
local tObj = tmr.create()

gpio.mode(LEDpin, gpio.OUTPUT)
gpio.write(LEDpin, status)

wifi.setmode(wifi.SOFTAP)

wifi.ap.config({
    ssid = "Body_Topology",
    pwd = "m10862017"
})

wifi.ap.setip({
    ip = "192.168.4.1",
    netmask = "255.255.255.0",
    --gateway = "192.168.4.1"
})

--[[for mac,ip in pairs(wifi.ap.getclient()) do
    print(mac,ip)
end]]--

server = net.createServer(net.TCP, 120)

function receiver(sck, data)
    if string.find(data, "on") then
        sck:send("LED ON\r\n")
        gpio.write(LEDpin, gpio.LOW)
    elseif string.find(data, "off") then
        sck:send("LED OFF\r\n") 
        gpio.write(LEDpin, gpio.HIGH)
    elseif string.find(data, "exit") then
        sck:close()
    else 
        sck:send("Command Not Found...\r\n")
    end
end

if server then
    server:listen(80, function(conn)
        conn:on("receive", receiver)
        conn:send("Hello from Body Topology   by Hsiao YL\r\n")
        conn:send("'on' 'off' and 'exit'\r\n")
    end)
end

