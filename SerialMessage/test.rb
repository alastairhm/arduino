#!/usr/bin/env ruby
require "serialport"
require "optparse"

opts = OptionParser.new
opts.on("-m Message","--message Message", String, "Message to Send") {|v| @message = v}
begin
	opts.parse!(ARGV)
rescue OptionParser::ParseError => e
	puts e
end
raise OptionParser::MissingArgument, "Message [-m]" if @message.nil?

puts "Initializing Serial Port"
myport = SerialPort.new("/dev/ttyACM0","9600".to_i)
sleep(2)
puts "Sending message = #{@message}"
myport.write(@message)
myport.close
