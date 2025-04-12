# C++ 西洋棋遊戲

這個專案是我在自主學習過程中，使用 C++ 撰寫的一個西洋棋遊戲程式。透過這個專案，我不只學會如何將棋盤資訊存儲在二維陣列中，還深入探討了棋子走法的實作、座標與 ASCII 編碼的轉換、以及特殊規則的處理（例如王車易位和兵的升后）。

## 專案介紹

在本程式中，每個棋子都被賦予一個對應的數值，如下所示（使用 Unicode 字符來呈現棋子圖示）：

- **白方棋子**：  
  王：1, 后：2, 車：3, 象：4, 馬：5, 兵：6

- **黑方棋子**：  
  王：7, 后：8, 車：9, 象：10, 馬：11, 兵：12

此外，為了方便後續運算與顯示，棋盤的座標利用 ASCII 編碼的特性，將 a ~ h 轉換成相應的數字，讓棋盤資訊能夠全部存放在一個二維陣列中。

## 主要功能

1. **棋盤建立與輸出**  
   - 利用二維整數陣列 `board` 表示棋盤，並將每個位置預先設定為特定棋子（或空位）。
   - 透過 `print_board()` 函式搭配 `num2chess()` 將棋子數值轉換成相對應的 Unicode 字符，使得遊戲介面直觀呈現。

2. **棋子走法檢測**  
   - 為國王、后、車、象、馬和兵分別設計了走法合法性檢測函式，這些函式不僅考慮棋子的移動規則，還會調用 `is_ally()` 函式以確保目的位置不含友軍。
   - 例如，在**國王**的走法檢查中，通過計算行差與列差判斷只移動一格；而**皇后**的走法則是綜合了橫走、直走與斜走的判斷，並進一步檢查路障情形。

3. **特殊規則處理**  
   - **兵的升后**：當白兵到達最上列或黑兵到達最下列時，自動將其升變為后。
   - **王車易位**：透過全域布林變數記錄國王與車是否曾移動過，再結合路障的判斷，使得遊戲能夠正確判斷王車易位的條件並執行易位操作。

4. **使用者互動**  
   - 遊戲透過終端機提示使用者輸入棋子的起始座標與目的座標（例如 `a1`、`b3`），並將這些字串根據 ASCII 編碼轉換為對應的陣列索引，進行後續處理。
   - 若玩家輸入不合法，程式會提示錯誤，並要求重新輸入，確保遊戲狀態正確更新。

# C++ Chess Game

This project is a chess game written in C++ that I developed during my self-learning journey. Through this project, I not only learned how to store the board information in a two-dimensional array, but also explored the implementation of each piece's movement, the conversion between coordinates and ASCII codes, and the handling of special rules (such as castling and pawn promotion).

## Project Overview

In this program, each chess piece is assigned a specific numeric value as shown below (using Unicode characters to display the pieces):

- **White Pieces**:  
  King: 1, Queen: 2, Rook: 3, Bishop: 4, Knight: 5, Pawn: 6

- **Black Pieces**:  
  King: 7, Queen: 8, Rook: 9, Bishop: 10, Knight: 11, Pawn: 12

In addition, to facilitate subsequent calculations and display, the board coordinates are represented by converting letters (a ~ h) into corresponding numbers using ASCII properties, so that all board information can be stored in a single two-dimensional array.

## Main Features

1. **Board Setup and Display**  
   - The board is represented using a two-dimensional integer array called `board`, with each cell pre-assigned a specific piece (or left empty).
   - The `print_board()` function, together with the `num2chess()` function, converts the numeric values of the pieces into corresponding Unicode characters so that the game interface is displayed in an intuitive way.

2. **Piece Movement Validation**  
   - Separate functions are implemented for validating the movement of each piece (King, Queen, Rook, Bishop, Knight, and Pawn). These functions not only consider the movement rules specific to the piece but also call the `is_ally()` function to ensure that the target square does not contain a friendly piece.
   - For example, the King’s move is validated by calculating the differences in rows and columns to confirm it moves only one square; the Queen’s move combines checks for horizontal, vertical, and diagonal movements, with additional obstacles (path) validation.

3. **Special Rule Handling**  
   - **Pawn Promotion**: When a white pawn reaches the top row or a black pawn reaches the bottom row, it is automatically promoted to a queen.
   - **Castling**: The program uses global boolean variables to track whether the King or Rook has moved. Coupled with the path clearance check, this ensures that the conditions for castling are properly evaluated and executed.

4. **User Interaction**  
   - The game prompts the user in the terminal to input the starting and ending coordinates for a move (e.g., `a1`, `b3`), and these strings are converted into corresponding array indices based on ASCII codes for further processing.
   - If the player's input is invalid, the program displays an error message and asks for re-entry, ensuring that the game state is updated correctly.

