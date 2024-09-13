### 9. 使用python操作￼￼￼￼

#### 9-1. 安裝套件

```
pip install paho-mqtt
```

#### 9-2. ￼￼程式碼

- [mqtt範例網站](https://github.com/roppert/mosquitto-python-example)

#### 9-2-1 發佈的程式碼￼

```

""" 
Publish some messages to queue
"""
import paho.mqtt.publish as publish


msgs = [{'topic': "kids/yolo", 'payload': "jump"},
        {'topic': "adult/pics", 'payload': "some photo"},
        {'topic': "adult/news", 'payload': "extra extra"},
        {'topic': "adult/news", 'payload': "super extra"}]

host = "localhost"


if __name__ == '__main__':
    # publish a single message
    publish.single(topic="kids/yolo", payload="just do it", hostname=host,qos=2)

    # publish multiple messages
    publish.multiple(msgs, hostname=host)
```

#### 9-2-2 ￼訂閱的程式碼

```
"""
A small example subscriber
"""
import paho.mqtt.client as mqtt

def on_message(mosq, obj, msg):
    print("topic:{0},payload:{1},qos:{2}".format(msg.topic,msg.payload.decode('utf-8'),msg.qos)) #msg.payload是binary string
    



if __name__ == '__main__':
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.on_message = on_message


    #client.tls_set('root.ca', certfile='c1.crt', keyfile='c1.key')
    client.connect("127.0.0.1", 1883, 60)

    client.subscribe("kids/yolo", qos=2)
    client.subscribe("adult/#", qos=2)

    client.loop_forever()
```