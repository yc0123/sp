import sqlite3
import requests
from bs4 import BeautifulSoup
import time

db=sqlite3.connect("crawler.db")
cursor=db.cursor()
try:
    cursor.execute("CREATE TABLE horoscope\
                   (constellation TEXT PRIMARY KEY NOT NULL,\
                   stars INT NOT NULL,\
                   describe TEXT NOT NULL)")
    db.commit()
except:
    db.rollback()
cursor.execute("DELETE FROM horoscope")
db.commit()
db.close()

constellation=["aries","taurus","gemini","cancer","leo","virgo","libra","scorpio","sagittarius","capricorn","aquarius","pisces"]
start=time.time()
for c in constellation:
    data=BeautifulSoup(requests.get(f"https://www.astrotw.com/fortune/{c}").text,"html.parser")
    data=data.find("h1",class_="fortune_h1__afL9M").text
    db=sqlite3.connect("crawler.db")
    cursor=db.cursor()
    cursor.execute("INSERT INTO horoscope(constellation,stars,describe)\
                   VALUES(?,?,?)",(data[0:3],int(data[8:9]),data[11:]))
    db.commit()
    db.close()
end=time.time()

print("今日星座運勢:")
db=sqlite3.connect("crawler.db")
cursor=db.cursor()
cursor.execute("SELECT * FROM horoscope")
for r in cursor:    
    print(f"{r[0]} {r[1]}★  {r[2]}")
db.close()
print(end-start)