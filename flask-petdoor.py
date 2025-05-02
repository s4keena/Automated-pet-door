from flask import Flask, render_template, request
import paho.mqtt.publish as publish

app = Flask(__name__)

MQTT_BROKER = "mqtt.thingsboard.io"
MQTT_PORT = 1883
MQTT_TOPIC = "v1/devices/me/rpc/request/1"
MQTT_USERNAME = "kQJNR8EBoRBvaSbzd0lK"

@app.route('/')
def index():
	return render_template('index.html')

@app.route('/open')
def open_door():
	publish.single(MQTT_TOPIC, payload='{"command": "open"}', hostname= MQTT_BROKER, port=MQTT_PORT, auth={'username': MQTT_USERNAME})
	return "Door Opened"

@app.route('/close')
def close_door():
	publish.single(MQTT_TOPIC, payload='{"command": "close"}', hostname= MQTT_BROKER, port=MQTT_PORT, auth={'username': MQTT_USERNAME})
	return "Door Closed"

if __name__ == '__main__':
	app.run(debug=True, host='0.0.0.0', port=8080)
