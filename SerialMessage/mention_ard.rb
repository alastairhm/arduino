#!/usr/bin/env ruby
# Find your Twitter Mentions and send them to Arduino on Serial Port

require "rubygems"
require "twitter" #https://github.com/sferik/twitter for config details
require "serialport" #http://rubygems.org/gems/serialport
require "pp"

prevID = 0
puts "Setting Up Serial Port"
myport = SerialPort.new("/dev/ttyACM0","9600".to_i)
sleep(10)
while true
	puts "Checking for mentions"
	latestMention = Twitter.mentions(:count => 1)[0]
	if prevID != latestMention.id
		#msg = latestMention.user.screen_name + " " + latestMention.text 
		#msg = msg = latestMention.user.screen_name
		msg = latestMention.text
		#puts msg.size
		puts "-" + msg
		bytes = myport.write(msg)
		puts "-" + bytes.to_s
		prevID = latestMention.id
	else
		puts "-No new updates"
	end
	sleep 60
end
myport.close
