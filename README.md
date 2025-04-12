Chess_Game
這是一個使用 C++ 實作的簡易西洋棋遊戲。項目主要目標是演練各種棋子移動規則的實作，並探索如何進行座標轉換、處理特殊走法（例如王車易位、兵的升變）以及基礎的程式設計概念。

功能說明
棋盤初始化與顯示
使用二維陣列 board 來表示棋盤狀態，並搭配 print_board() 函式將目前棋子狀態以符號顯示在終端機上。

棋子走法判斷
為每個棋子（國王、后、車、象、馬、兵）分別撰寫了合法性檢查函式（如 king()、queen()、rook() 等），以確保每一步都符合正確的移動規範。

座標轉換機制
支援使用者輸入象徵西洋棋坐標（例如 a1、b3），透過字串解析將其轉換成對應的陣列索引，讓玩家能以直覺方式控制棋子。

特殊規則

王車易位：檢查國王與車是否有移動過，以及路徑是否淨空。

兵的升后：白兵抵達最上列或黑兵抵達最下列時自動升為后。

終局檢查
當任一方的王被吃掉時，遊戲即宣告結束並顯示勝負結果。

使用方式
編譯程式
確保系統已安裝 C++ 編譯器（例如 g++），然後在終端機輸入：

bash
複製
g++ chess.cpp -o chess
生成的執行檔名稱可自行指定（此處為 chess）。

執行程式

bash
複製
./chess
進入遊戲後，程式會列印初始棋盤，並要求玩家依座標輸入想移動的棋子與目的位置。

操作說明

在終端機中，透過如 a1、b2 等方式輸入起始座標與目的座標。

若移動不合法，程式會提示錯誤並重新要求輸入。

程式架構
board 陣列
以 2D 整數陣列儲存棋盤狀態；

走法檢查函式
king(), queen(), rook(), bishop(), knight(), pawn() 用於判斷移動的合規性；

座標轉換
例如透過 in_coor[0] - 'a' + 1 與 8 - (in_coor[1] - '0') 將字串座標轉成陣列索引；

特殊規則
國王易位由 castle() 函式檢查；兵升后由 pawn2queen() 處理。
