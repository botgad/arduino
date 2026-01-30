import serial

ser = serial.Serial('/dev/serial0', 9600, timeout=1)

while True:
    line = ser.readline().decode('utf-8').strip()
    if not line:
        continue

    try:
        parts = line.split('|')
        humidity = float(parts[0].split('=')[1])
        temperature = float(parts[1].split('=')[1])
        light = int(parts[2].split('=')[1])

        print(f"Humidité : {humidity} %")
        print(f"Température : {temperature} °C")
        print(f"Luminosité : {light}")
        print("-" * 30)

    except Exception as e:
        print("Erreur de parsing :", e)