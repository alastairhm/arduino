require "serialport"

myport = SerialPort.new("/dev/ttyACM0","9600".to_i)
sleep(10)
myport.write(">Hello From Ruby Script<")
myport.close
