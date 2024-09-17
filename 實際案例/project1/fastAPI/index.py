from fastapi import FastAPI
from pydantic import BaseModel
import redis
from dotenv import load_dotenv


class Item(BaseModel):
    distance:float
    light:float

import os

load_dotenv() #載入.env的環境變數
app = FastAPI()
renderRedis = redis.Redis.from_url(os.environ.get('redis'))

@app.post("/items/")
async def update_item(item:Item):
    print(item)
    return {'status':'ok'}

@app.get("/items/{date}/{distance}/{light}")
async def update_item1(date:str,distance:float,light:float):
    #lpush是放在redis list的最前方
    renderRedis.lpush('pico_distance',distance)
    renderRedis.lpush('pico_light',light)
    
    return {"status":"ok"}

@app.post("/items/{lastNum}")
async def get_items(lastNum:int):
    #redis取出最前方資料(因為更新在最前方)
    distances = renderRedis.lrange('pico_distance',0,lastNum)
    light = renderRedis.lrange('pico_light',0,lastNum)
    
    #傳出的資料的索引是[9,8,7,6,5,4,3,2,1,0],所以要反轉資料
    #0是每次更新的最新資料,
    #list.reverse(),傳出None
    
    distances.reverse()
    light.reverse()


    #將byte string 轉換為 str
    distances_list = [item.decode('utf-8') for item in distances]
    light_list = [item.decode('utf-8') for item in light]

    #建立list_time:list[Item]
    list_item:list[Item] = []  
    for i in range(len(distances_list)):
        d = distances_list[i]
        l = light_list[i]
        #建立Pydantic實體
        item = Item(distance=float(d), light=float(l))        
        list_item.append(item)
    
    return list_item


