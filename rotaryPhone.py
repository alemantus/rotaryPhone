
# External module imports
import RPi.GPIO as GPIO
import time
import paho.mqtt.client as mqtt

pulse_count = 0
hangUp = 17
dial = 18
startTime = 0
phoneNumber = [0,0,0,0,0,0,0,0]
index = 0
control = 0

GPIO.setmode(GPIO.BCM)
#GPIO.setup(hangUp, GPIO.IN)
GPIO.setup(dial, GPIO.IN, pull_up_down=GPIO.PUD_UP)
#GPIO.setup(dial, GPIO.IN)
GPIO.setup(hangUp, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def toInt(list):
	listToInt = int(''.join(list))
	return listToInt


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("$SYS/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.


def pulse(channel):
    global pulse_count
    global startTime
	global control
    startTime = time.time()
    pulse_count += 1
    #print(pulse_count)
	control = 0

def nulle():
    global pulse_count
    pulse_count = 0
	control = 1
	
GPIO.add_event_detect(dial, GPIO.FALLING, callback=pulse, bouncetime=50)

client.publish("test",toInt(phoneNumber))

while 1:
	#enter if not dialing
    if ((time.time()-startTime) > 0.5 and control = 0):
		if pulse_count != 0:
			if pulse_count == 10:
				pulse_count = 0
			print(pulse_count)
			phoneNumber[index] = pulse_count
			index += 1
			nulle()
			client.publish("test",toInt(phoneNumber))
			#print(index)
			
			#we have 8 digits
			if index >= 8:
				client.publish("test",toInt(phoneNumber))
		#		print("test2")
				time.sleep(2)
				phoneNumber = [0,0,0,0,0,0,0,0]
				client.publish("test",toInt(phoneNumber))
				index = 0
	    
    if GPIO.input(hangUp):
		print("test1")
		phoneNumber = [0,0,0,0,0,0,0,0]

		client.publish("test",toInt(phoneNumber))
		client.publish("hangUp",1)
		index = 0
    else:
		client.publish("hangUp", 0)


    time.sleep(0.1)

	client.loop_start()
