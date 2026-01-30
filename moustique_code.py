import serial
import paho.mqtt.client as mqtt


ser = serial.Serial('/dev/serial0', 9600, timeout=1)


client = mqtt.Client()
client.connect("10.124.52.41", 1883, 60)

while True:
    line = ser.readline().decode('utf-8').strip()
    if not line:
        continue

    try:
        parts = line.split('|')
        humidity = parts[0].split('=')[1]
        temperature = parts[1].split('=')[1]
        light = parts[2].split('=')[1]

        
        client.publish("humidite", humidity)
        client.publish("emperature", temperature)
        client.publish("luminosite", light)

        print("Données envoyées au téléphone ")

    except:
        print("Erreur de lecture")