# Bilgisayarda çalışan bu python kodu ile
# raspberry pi brokerına baglanip temperature konusuna 
# abone olan program
import paho.mqtt.client as mqtt
# baglanma fonksiyonu
def on_connect(client, userdata, flags, rc):
    print("Connected")
    client.subscribe("temperature")

#mesaj gelince calısan fonk
def on_message(client, userdata, msg):
    print(str(msg.payload))

client = mqtt.Client()
client.username_pw_set("mosq_hoca", "12345678")
client.on_connect = on_connect
client.on_message = on_message

client.connect("88.242.114.139", 1883, 60)
client.loop_forever()