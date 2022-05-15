# Import package
import paho.mqtt.client as mqtt
import ssl

# Define Variables
MQTT_PORT = 8883
MQTT_KEEPALIVE_INTERVAL = 45
MQTT_TOPIC = "esp32/pub"
MQTT_MSG = "hello MQTT PC"

MQTT_HOST = "a1zidheuopaxeb-ats.iot.us-west-2.amazonaws.com"
CA_ROOT_CERT_FILE ="root-CA.crt"
THING_CERT_FILE = "aa2364537e-certificate.pem.crt"
THING_PRIVATE_KEY = "aa2364537e-private.pem.key"

# Define on connect event function
# We shall subscribe to our Topic in this function
def on_connect(mosq, obj, rc):
    mqttc.subscribe(MQTT_TOPIC, 0)

# Define on_message event function.
# This function will be invoked every time,
# a new message arrives for the subscribed topic
def on_message(mosq, obj, msg):
	print("Topic: " + str(msg.topic))
	print("QoS: " + str(msg.qos))
	print("Payload: " + str(msg.payload))
	mqttc.publish(MQTT_TOPIC, MQTT_MSG, qos=1)

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed to Topic: " +
	MQTT_MSG + " with QoS: " + str(granted_qos))

# Define on_publish event function
def on_publish(client, userdata, mid):
	print("Message Published...")

# Initiate MQTT Client
mqttc = mqtt.Client()

# Assign event callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe

# Register publish callback function
mqttc.on_publish = on_publish


# Configure TLS Set
mqttc.tls_set(CA_ROOT_CERT_FILE, certfile=THING_CERT_FILE, keyfile=THING_PRIVATE_KEY, cert_reqs=ssl.CERT_REQUIRED, tls_version=ssl.PROTOCOL_TLSv1_2, ciphers=None)


# Connect with MQTT Broker
mqttc.connect(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE_INTERVAL)

mqttc.publish(MQTT_TOPIC, MQTT_MSG, qos=1)
mqttc.publish(MQTT_TOPIC, MQTT_MSG, qos=1)
mqttc.publish(MQTT_TOPIC, MQTT_MSG, qos=1)
mqttc.publish(MQTT_TOPIC, MQTT_MSG, qos=1)
#while True:
#	mqttc.publish(MQTT_TOPIC, MQTT_MSG, qos=1)

# Continue monitoring the incoming messages for subscribed topic
mqttc.loop_forever()