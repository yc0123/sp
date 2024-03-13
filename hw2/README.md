```
...

DOWHILE = do STMT while (E)
void DOWHILE() { // 定義 DOWHILE 函數，用於解析 do-while 循環
  int dowhileBegin = nextLabel(); // 獲取下一個標籤索引並賦值給 dowhileBegin
  skip("do"); // 跳過 'do' 關鍵字
  emit("(L%d)\n", dowhileBegin); // 輸出標籤
  STMT(); // 呼叫 STMT 函數解析語句
  skip("while"); // 跳過 'while' 關鍵字
  skip("("); // 跳過 '('
  int e = E(); // 呼叫 E 函數解析表達式
  emit("if T%d goto L%d\n", e, dowhileBegin); // 輸出條件判斷指令
  skip(")"); // 跳過 ')'
  skip(";"); // 跳過 ';'
}
...
```
```
============ parse =============
t0 = 1
i = t0
(L0)
t1 = i
t2 = 1
t3 = t1 + t2
i = t3
t4 = i
t5 = 10
t6 = t4 <= t5
if T6 goto L0
```