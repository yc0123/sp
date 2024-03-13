#include <assert.h>
#include "compiler.h"

int E(); // 宣告 E 函數
void STMT(); // 宣告 STMT 函數
void IF(); // 宣告 IF 函數
void BLOCK(); // 宣告 BLOCK 函數

int tempIdx = 0, labelIdx = 0; // 宣告全域變數 tempIdx 和 labelIdx，用於產生暫存變數索引和標籤索引

#define nextTemp() (tempIdx++) // 定義 nextTemp() 宏，用於產生下一個暫存變數索引
#define nextLabel() (labelIdx++) // 定義 nextLabel() 宏，用於產生下一個標籤索引
#define emit printf // 定義 emit 宏為 printf 函數

int isNext(char *set) { // 定義 isNext 函數，用於檢查下一個 token 是否在指定集合中
  char eset[SMAX], etoken[SMAX]; // 宣告字串變數 eset 和 etoken
  sprintf(eset, " %s ", set); // 將集合 set 格式化為字串 eset
  sprintf(etoken, " %s ", tokens[tokenIdx]); // 將下一個 token 格式化為字串 etoken
  return (tokenIdx < tokenTop && strstr(eset, etoken) != NULL); // 檢查下一個 token 是否在集合中
}

int isEnd() { // 定義 isEnd 函數，用於檢查是否已到達 token 流的結尾
  return tokenIdx >= tokenTop; // 回傳是否已到達 token 流的結尾
}

char *next() { // 定義 next 函數，用於獲取下一個 token
  // printf("token[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
  return tokens[tokenIdx++]; // 回傳下一個 token 並增加 token 索引
}

char *skip(char *set) { // 定義 skip 函數，用於跳過下一個符合指定集合的 token
  if (isNext(set)) { // 如果下一個 token 在指定集合中
    return next(); // 回傳下一個 token
  } else { // 否則
    printf("skip(%s) got %s fail!\n", set, next()); // 輸出錯誤訊息並終止程式
    assert(0);
  }
}

// F = (E) | Number | Id
int F() { // 定義 F 函數，用於解析表達式
  int f; // 宣告 f 變數，用於存儲結果
  if (isNext("(")) { // 如果下一個 token 是左括號 '('
    next(); // 獲取下一個 token
    f = E(); // 呼叫 E 函數並將結果賦值給 f
    next(); // 獲取下一個 token
  } else { // 否則（即為數字或識別符）
    f = nextTemp(); // 獲取下一個暫存變數索引並賦值給 f
    char *item = next(); // 獲取下一個 token 並賦值給 item
    if (isdigit(*item)) { // 如果 token 是數字
      emit("t%d = %s\n", f, item); // 輸出指令
    } else { // 否則（即為識別符）
      if (isNext("++")) { // 如果下一個 token 是 '++'
        next(); // 獲取下一個 token
        emit("%s = %s + 1\n", item, item); // 輸出指令
      }
      emit("t%d = %s\n", f, item); // 輸出指令
    }
  }
  return f; // 回傳結果
}

// E = F (op E)*
int E() { // 定義 E 函數，用於解析表達式
  int i1 = F(); // 呼叫 F 函數並將結果賦值給 i1
  while (isNext("+ - * / & | ! < > = <= >= == !=")) { // 當下一個 token 是運算符時
    char *op = next(); // 獲取運算符
    int i2 = E(); // 呼叫 E 函數並將結果賦值給 i2
    int i = nextTemp(); // 獲取下一個暫存變數索引
    emit("t%d = t%d %s t%d\n", i, i1, op, i2); // 輸出指令
    i1 = i; // 更新 i1
  }
  return i1; // 回傳結果
}

// FOR =  for (ASSIGN EXP; EXP) STMT

// ASSIGN = id '=' E;
void ASSIGN() { // 定義 ASSIGN 函數，用於解析賦值語句
  char *id = next(); // 獲取識別符
  skip("="); // 跳過 '='
  int e = E(); // 呼叫 E 函數並將結果賦值給 e
  skip(";"); // 跳過 ';'
  emit("%s = t%d\n", id, e); // 輸出指令
}

// WHILE = while (E) STMT
void WHILE() { // 定義 WHILE 函數，用於解析 while 循環
  int whileBegin = nextLabel(); // 獲取下一個標籤索引並賦值給 whileBegin
  int whileEnd = nextLabel(); // 獲取下一個標籤索引
  emit("(L%d)\n", whileBegin); // 輸出標籤
  skip("while"); // 跳過 'while' 關鍵字
  skip("("); // 跳過 '('
  int e = E(); // 呼叫 E 函數並將結果賦值給 e
  emit("if not T%d goto L%d\n", e, whileEnd); // 輸出條件判斷指令
  skip(")"); // 跳過 ')'
  STMT(); // 呼叫 STMT 函數解析語句
  emit("goto L%d\n", whileBegin); // 輸出無條件跳轉指令
  emit("(L%d)\n", whileEnd); // 輸出標籤
}

// if (EXP) STMT (else STMT)?
void IF() { // 定義 IF 函數，用於解析 if 條件語句
  skip("if"); // 跳過 'if' 關鍵字
  skip("("); // 跳過 '('
  E(); // 呼叫 E 函數解析表達式
  skip(")"); // 跳過 ')'
  STMT(); // 呼叫 STMT 函數解析語句
  if (isNext("else")) { // 如果下一個 token 是 'else'
    skip("else"); // 跳過 'else' 關鍵字
    STMT(); // 呼叫 STMT 函數解析語句
  }
}

// DOWHILE = do STMT while (E)
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

// STMT = WHILE | BLOCK | ASSIGN
void STMT() { // 定義 STMT 函數，用於解析語句
  if (isNext("while")) // 如果下一個 token 是 'while'
    return WHILE(); // 呼叫 WHILE 函數解析循環
  else if(isNext("do")) // 如果下一個 token 是 'do'
    return DOWHILE(); // 呼叫 DOWHILE 函數解析循環
  else if (isNext("if")) // 如果下一個 token 是 'if'
    IF(); // 呼叫 IF 函數解析條件語句
  else if (isNext("{")) // 如果下一個 token 是 '{'
    BLOCK(); // 呼叫 BLOCK 函數解析區塊
  else
    ASSIGN(); // 否則呼叫 ASSIGN 函數解析賦值語句
}

// STMTS = STMT*
void STMTS() { // 定義 STMTS 函數，用於解析一系列語句
  while (!isEnd() && !isNext("}")) { // 當未到達 token 流的結尾且下一個 token 不是 '}'
    STMT(); // 呼叫 STMT 函數解析語句
  }
}

// BLOCK = { STMTS }
void BLOCK() { // 定義 BLOCK 函數，用於解析區塊
  skip("{"); // 跳過 '{'
  STMTS(); // 呼叫 STMTS 函數解析一系列語句
  skip("}"); // 跳過 '}'
}

// PROG = STMTS
void PROG() { // 定義 PROG 函數，用於解析整個程式
  STMTS(); // 呼叫 STMTS 函數解析一系列語句
}

void parse() { // 定義 parse 函數，用於解析程式
  printf("============ parse =============\n"); // 輸出提示訊息
  tokenIdx = 0; // 初始化 token 索引
  PROG(); // 呼叫 PROG 函數解析整個程式
}
