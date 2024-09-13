# Linux_MQTT￼安裝(Mosquitto)

1 **更新系統:**

```bash
sudo apt update
sudo apt upgrade
```

2. **Install Mosquitto:**
使用下列命令，￼安裝Mosquitto和Mosquitto clients
   
```bash
sudo apt install mosquitto mosquitto-clients
```

3. **開機時自動啟動Mosquitto￼:**
   
```bash
sudo systemctl enable mosquitto
```

4. **立即啟動 Mosquitto Service:**

```bash
sudo systemctl start mosquitto
```

5. **檢查Mosquitto Service狀態:**
   驗證現在Mosquitto service是否在執行￼:
```bash
sudo systemctl status mosquitto
```

6. **修改Mosquitto配置設定:**

## 1-1 使用編輯器修改`/etc/mosquitto/mosquitto.conf`的設定.
    
- #### [修改說明]￼(/usr/share/doc/mosquitto/examples/mosquitto.conf.example)

**以下為不需要密碼的操作方式**

```bash
#原本的設定
pid_file /run/mosquitto/mosquitto.pid

persistence true
persistence_location /var/lib/mosquitto/

log_dest file /var/log/mosquitto/mosquitto.log

include_dir /etc/mosquitto/conf.d

#新增的設定
#監聽1883port
#允許匿名發佈
￼listener 1883 
allow_anonymous true

```

**以下為需要密碼的操作方式**

- 先使用command加入密碼,再改變mosquitto.conf的內容,順序不要錯

**1. 使用command 加入密碼**
- username:pi
- password:raspberry
- 程式加入密碼要在publish內

```
sudo mosquitto_passwd -c /etc/mosquitto/pwfile TYPE_YOUR_USERNAME
```



```bash


#原本的設定
pid_file /run/mosquitto/mosquitto.pid

persistence true
persistence_location /var/lib/mosquitto/

log_dest file /var/log/mosquitto/mosquitto.log

include_dir /etc/mosquitto/conf.d

#新增的設定
#監聽1883port
#允許匿名發佈
￼listener 1883 
allow_anonymous false

password_file /etc/mosquitto/pwfile
```




￼
## 1-2 使用command line操作測試(無密碼)
￼建立兩個終端機，一個終端機當作訂閱另一個終端機當作發佈。

**1. 訂閱主題終端機如下：**

```bash
mosquitto_sub -d -h localhost -t test/topic
```

**2. 發佈訂閱主題如下：**

```bash
mosquitto_pub -d -h localhost -t test/topic -m "Hello, Mosquitto!"
```

**3. 將在訂閱主題的終端機看到以下幾個字：**

```
Hello,Mosquitto!
```

## 1-3 使用command line操作測試(有密碼)

￼建立兩個終端機，一個終端機當作訂閱另一個終端機當作發佈。

**1. 訂閱主題終端機如下：**

```bash
mosquitto_sub -d -h localhost -t test/topic
```

**2. 發佈訂閱主題如下：**

```base
# -u username
# -P password
```

```bash
mosquitto_pub -d -h localhost -t test/topic -u USERNAME -P PASSWORD -m "Hello, Mosquitto!"
```

**3. 將在訂閱主題的終端機看到以下幾個字：**

```
Hello,Mosquitto!
```
