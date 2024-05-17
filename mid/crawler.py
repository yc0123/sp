import threading
import sqlite3
import requests
from bs4 import BeautifulSoup
import time

def crawler(c):
    global lock
    data=BeautifulSoup(requests.get(f"https://www.astrotw.com/fortune/{c}").text,"html.parser")
    data=data.find("h1",class_="fortune_h1__afL9M").text
    lock.acquire()
    db=sqlite3.connect("crawler.db")
    cursor=db.cursor()
    cursor.execute("INSERT INTO horoscope(constellation,stars,describe)\
                   VALUES(?,?,?)",(data[0:3],int(data[8:9]),data[11:]))
    db.commit()
    db.close()
    lock.release()

constellation=["aries","taurus","gemini","cancer","leo","virgo","libra","scorpio","sagittarius","capricorn","aquarius","pisces"]
threads=[]
for c in constellation:
    threads.append(threading.Thread(target=crawler,args=(c,)))

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

lock=threading.Lock()
start=time.time()
for t in threads:
    t.start()

for t in threads:
    t.join()
end=time.time()

print("今日星座運勢:")
db=sqlite3.connect("crawler.db")
cursor=db.cursor()
cursor.execute("SELECT * FROM horoscope")
for r in cursor:    
    print(f"{r[0]} {r[1]}★  {r[2]}")
db.close()
print(end-start)