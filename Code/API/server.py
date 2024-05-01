from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from datetime import datetime as dt
import json

app = FastAPI()

origins = [
    "http://localhost:1234",
    "http://192.168.77.174:80"
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

song_data = json.load(open('song_data.json'))

@app.get("/song_data")
def getSongData(name: str):
    return song_data[name]

@app.get("/add_data")
def addData(litres: int):
    with open("drinking_info.json",'r+') as f:
        f_data = json.load(f)
        
        date_now = dt.now().strftime(r"%d/%m/%y")
        time_now = dt.now().strftime("%H:%M")
        
        if date_now in f_data:
            if time_now in f_data[date_now]:
                f_data[date_now][time_now] += litres
            else:
                f_data[date_now].update({time_now: litres})
        else:
            f_data.update({date_now: {time_now: litres}})
        
        f.seek(0)
        json.dump(f_data, f, indent = 4)

@app.get("/get_data")
def getData():
    with open("drinking_info.json",'r') as f:
        return json.load(f)