# 使用python實作一個簡易爬蟲，爬取當日各個星座的運勢，具有sqlite3資料庫

## crawler_single.py
### 沒有使用multithread的版本，用for迴圈爬取每個分頁的資料
執行結果:
```py
今日星座運勢:
牡羊座 3★  保持活躍與興致
金牛座 4★  結合實際情況行動
雙子座 3★  做好應變的準備
巨蟹座 2★  忽略重要的事情
獅子座 3★  考慮多出門走走
處女座 4★  很多知識的收穫
天秤座 4★  穩住自己的重心
天蠍座 3★  精神太過於緊繃
射手座 3★  過於歸咎自己責任
摩羯座 4★  迎來努力後的收穫
水瓶座 4★  不被外界因素左右
雙魚座 4★  越努力就越幸運
6.22951865196228 #這一行為迴圈爬取每個網頁並寫入資料庫所花費的時間(s)
```

## crawler.py
### 使用multithread的版本，創建爬取各個分頁的Thread，再一起執行
執行結果:
```py
今日星座運勢:
摩羯座 4★  迎來努力後的收穫
巨蟹座 2★  忽略重要的事情
金牛座 4★  結合實際情況行動
雙魚座 4★  越努力就越幸運
水瓶座 4★  不被外界因素左右
雙子座 3★  做好應變的準備
天蠍座 3★  精神太過於緊繃
獅子座 3★  考慮多出門走走
射手座 3★  過於歸咎自己責任
處女座 4★  很多知識的收穫
牡羊座 3★  保持活躍與興致
天秤座 4★  穩住自己的重心
0.8059995174407959 #這一行為所有Thread爬取網頁並寫入資料庫所花費的時間(s)
```

#### 全部原創，僅上網查詢各個函式的功能及用法