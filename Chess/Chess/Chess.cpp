#include <iostream>
using namespace std;
//	    王	后	車	象	馬	兵
//白方	♔1	♕2	♖3	♗4	♘5	♙6
//黑方	♚7	♛8	♜9	♝10	♞11	♟12
//空位   ○ 0
//座標   a為97(ASCII編碼) b為98依此類推 空白則為96

//初始化棋盤(全域)
int board[9][9] =
{
    {8 ,9 ,11,10,8 ,7 ,10,11,9 },
    {7 ,12,12,12,12,12,12,12,12},
    {6 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {5 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {4 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {3 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
    {2 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 },
    {1 ,3 ,5 ,4 ,2 ,1 ,4 ,5 ,3 },
    {0 ,97,98,99,100,101,102,103,104}
};

//數字轉棋子符號
string num2chess(int n)
{
    //棋子
    if (n == 0)  return "　";
    if (n == 1)  return "♔";
    if (n == 2)  return "♕";
    if (n == 3)  return "♖";
    if (n == 4)  return "♗";
    if (n == 5)  return "♘";
    if (n == 6)  return "♙";
    if (n == 7)  return "♚";
    if (n == 8)  return "♛";
    if (n == 9)  return "♜";
    if (n == 10)  return "♝";
    if (n == 11)  return "♞";
    if (n == 12)  return "♟";
    //字母座標
    if (n >= 97 && n <= 104)
    {
        cout << char(n);
    }
}

void print_board(void)
{
    for (int i = 0; i < 9; i++)
    {
        if (i < 8)  cout << board[i][0] << " ";
        if (i == 8) cout << "  ";
        for (int j = 1; j < 9; j++)
        {
            cout << num2chess(board[i][j]);
            cout << " ";
        }
        cout << endl;
    }
}

//目的地檢查(確保不會吃掉友軍)
bool is_ally(int src_piece, int dst_piece)
{
    if (dst_piece == 0) return false;
    else
    {
        // 白棋為 1~6，黑棋為 7~12
        if ((src_piece >= 1 && src_piece <= 6 && dst_piece >= 1 && dst_piece <= 6) ||
            (src_piece >= 7 && src_piece <= 12 && dst_piece >= 7 && dst_piece <= 12))
            return true;
    }
    return false;
}

//王的走法是否合法
bool king(int src_row, int src_col, int dst_row, int dst_col)
{
    int src_piece = board[src_row][src_col];
    int dst_piece = board[dst_row][dst_col];
    if (src_piece == 0)// 若起始格無棋子，直接返回 false
        return false;

    // 國王只能移動一格，計算列與行的差值
    int dRow = abs(src_row - dst_row);//橫列
    int dCol = abs(src_col - dst_col);//直行
    if (dRow > 1 || dCol > 1)
        return false;
    //判斷目的地是否為友軍

    if (is_ally(src_piece, dst_piece))//若為友軍則表示目的地錯誤
        return false;
    return true;
}

//后的走法是否合法
bool queen(int src_row, int src_col, int dst_row, int dst_col)
{
    int src_piece = board[src_row][src_col];
    int dst_piece = board[dst_row][dst_col];
    if (src_piece == 0)// 若起始格無棋子，直接返回 false
        return false;

    //分3部分 1.移動方向 2.目的地是否為友軍 3.路障

    //移動方向
    int dRow = abs(src_row - dst_row);
    int dCol = abs(src_col - dst_col);
    if (!(src_row == dst_row || src_col == dst_col || dRow == dCol))//橫走 直走 斜走
        return false;

    //目的地檢查
    if (is_ally(src_piece, dst_piece))
        return false;

    //路障檢查 分3個小部分 水平 垂直 斜線 三方向
    //基本邏輯:先算出兩點座標 再用迴圈一個一個檢查有無棋子
    if (src_row == dst_row)//水平方向(仍在同一橫列)
    {
        int init = min(src_col, dst_col) + 1;//找最小值=>獲得起點
        int end = max(src_col, dst_col);//找最大值=>獲得終點
        for (int i = init; i < end; i++)
        {
            if (board[src_row][i] != 0)
                return false;
        }
    }

    else if (src_col == dst_col)//垂直方向(仍在同一直行)
    {
        int init = min(src_row, dst_row) + 1;
        int end = max(src_row, dst_row);
        for (int i = init; i < end; i++)
        {
            if (board[i][src_col] != 0)
                return false;
        }
    }

    else//只剩對角線移動這個可能性
    {
        // 對角線移動檢查：確保起點與目的地之間的所有格子均為空（不含目的地）

        int row_step, col_step;
        // 決定橫列的步進：如果目的列大於起始列，步進為1，否則為-1
        if (dst_row > src_row)
        {
            row_step = 1;
        }
        else
        {
            row_step = -1;
        }

        // 決定直行的步進：如果目的行大於起始行，步進為1，否則為-1
        if (dst_col > src_col)
        {
            col_step = 1;
        }
        else
        {
            col_step = -1;
        }

        int r = src_row + row_step;
        int c = src_col + col_step;
        // 從起點開始沿對角線移動，直到到達目的地之前的那一格
        while (r != dst_row && c != dst_col)
        {
            if (board[r][c] != 0)
            {
                return false;  // 如果中間有棋子阻擋，則移動不合法
            }
            r = r + row_step;
            c = c + col_step;
        }

        return true;
    }
}

//車(城堡)的走法是否合法
bool rook(int src_row, int src_col, int dst_row, int dst_col)
{
    int src_piece = board[src_row][src_col];
    int dst_piece = board[dst_row][dst_col];
    if (src_piece == 0)// 若起始格無棋子，直接返回 false
        return false;
    //移動方向
    int dRow = abs(src_row - dst_row);
    int dCol = abs(src_col - dst_col);
    if (!(src_row == dst_row || src_col == dst_col))//橫走 直走
        return false;

    //目的地檢查
    if (is_ally(src_piece, dst_piece))
        return false;

    //路障檢查
    if (src_row == dst_row)//水平方向(仍在同一橫列)
    {
        int init = min(src_col, dst_col) + 1;//找最小值=>獲得起點
        int end = max(src_col, dst_col);//找最大值=>獲得終點
        for (int i = init; i < end; i++)//目的地不是空的就是敵軍(目的地檢查就檢查過有無敵軍了)
        {
            if (board[src_row][i] != 0)
                return false;
        }
    }

    if (src_col == dst_col)//垂直方向(仍在同一直行)
    {
        int init = min(src_row, dst_row) + 1;
        int end = max(src_row, dst_row);
        for (int i = init; i < end; i++)
        {
            if (board[i][src_col] != 0)
                return false;
        }
    }
    return true;
}

//象(主教)的走法是否合法
bool bishop(int src_row, int src_col, int dst_row, int dst_col)
{
    int src_piece = board[src_row][src_col];
    int dst_piece = board[dst_row][dst_col];
    if (src_piece == 0)
        return false;

    // 檢查移動方向：必須為對角線 (斜走)
    int dRow = abs(src_row - dst_row);
    int dCol = abs(src_col - dst_col);
    if (dRow != dCol)
        return false;

    // 檢查目的地是否為友軍
    if (is_ally(src_piece, dst_piece))
        return false;

    // 決定步進方向
    int row_step, col_step;
    // 決定橫列的步進：如果目的列大於起始列，步進為1，否則為-1
    if (dst_row > src_row)
    {
        row_step = 1;
    }
    else
    {
        row_step = -1;
    }

    // 決定直行的步進：如果目的行大於起始行，步進為1，否則為-1
    if (dst_col > src_col)
    {
        col_step = 1;
    }
    else
    {
        col_step = -1;
    }

    // 檢查路障：從起點下一格開始，直到目的格前一格
    int r = src_row + row_step;
    int c = src_col + col_step;
    // 從起點開始沿對角線移動，直到到達目的地之前的那一格
    while (r != dst_row && c != dst_col)
    {
        if (board[r][c] != 0)
        {
            return false;  // 如果中間有棋子阻擋，則移動不合法
        }
        r = r + row_step;
        c = c + col_step;
    }

    return true;
}


//馬(騎士)的走法是否合法
bool knight(int src_row, int src_col, int dst_row, int dst_col)
{
    int src_piece = board[src_row][src_col];
    int dst_piece = board[dst_row][dst_col];
    if (src_piece == 0)// 若起始格無棋子，直接返回 false
        return false;
    //移動方向
    int dRow = abs(src_row - dst_row);//橫列
    int dCol = abs(src_col - dst_col);//直行
    if (!((dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2)))
        return false;

    //目的地檢查
    if (is_ally(src_piece, dst_piece))
        return false;

    return true;
    //沒有路障問題 馬可以跳著走
}

//兵的走法是否合法 *第一步可以走兩格
bool pawn(int src_row, int src_col, int dst_row, int dst_col)
{
    int src_piece = board[src_row][src_col];
    int dst_piece = board[dst_row][dst_col];
    //若起始格無棋子，直接返回 false
    if (src_piece == 0)
        return false;

    //白兵（6）：向上移動 (行數減少)
    if (src_piece == 6)
    {
        //直走
        if (src_col == dst_col)
        {
            //一步直走
            if (dst_row == src_row - 1 && dst_piece == 0)
                return true;
            //第一步可直走兩步
            //是白兵 && 走兩步 && 中間那一格空白 && 目的地空白
            if (src_row == 6 && dst_row == src_row - 2 &&
                board[src_row - 1][src_col] == 0 && dst_piece == 0)
                return true;
        }
        //捕捉：對角線移動一步，且目的格有敵方棋子
        //列差一格 && 行差一格 && 目標格不為空白 && 目標格不為友軍
        if (abs(dst_col - src_col) == 1 && dst_row == src_row - 1 &&
            dst_piece != 0 && !is_ally(src_piece, dst_piece))
            return true;
    }
    // 黑兵（12）：向下移動 (行數增加)
    else if (src_piece == 12)
    {
        //直走
        if (src_col == dst_col)
        {
            //一步直走
            if (dst_row == src_row + 1 && dst_piece == 0)
                return true;
            //是黑兵 && 走兩步 && 中間那一格空白 && 目的地空白
            if (src_row == 1 && dst_row == src_row + 2 &&
                board[src_row + 1][src_col] == 0 && dst_piece == 0)
                return true;
        }
        //捕捉：對角線移動一步，且目的格有敵方棋子
        //列差一格 && 行差一格 && 目標格不為空白 && 目標格不為友軍
        if (abs(dst_col - src_col) == 1 && dst_row == src_row + 1 &&
            dst_piece != 0 && !is_ally(src_piece, dst_piece))
            return true;
    }

    return false;
}

//兵晉升為后
int pawn2queen(int src_row, int src_col, int dst_row, int dst_col)
{
    //白兵升后
    for (int i = 1; i < 9; i++)
    {
        if (board[0][i] == 6)
        {
            return board[0][i] = 2;
        }
    }
    //黑兵升后
    for (int i = 1; i < 9; i++)
    {
        if (board[7][i] == 12)
        {
            return board[7][i] = 8;
        }
    }
}

//判斷王車易位 
bool castle(int king_src_row, int king_src_col, int king_dst_row, int king_dst_col, bool isWhite)
{
    if (isWhite)
    {
        //條件：白方國王和任一白車均未移動過，且國王必須在 (7,5)
        extern bool white_king_moved, white_rook_moved;
        if (white_king_moved || white_rook_moved)
            return false;
        if (king_src_row != 7 || king_src_col != 5)
            return false;

        //短易位：國王從 e1 (7,5) 移至 g1 (7,7)
        if (king_dst_row == 7 && king_dst_col == 7)
        {
            //檢查路徑：f1 (7,6) 和 g1 (7,7) 必須為空
            if (board[7][6] != 0 || board[7][7] != 0)
                return false;
            //檢查對應的車必須在 h1 (7,8) 且為白車 (3)
            if (board[7][8] != 3)
                return false;
            //執行易位：移動國王與車
            board[7][7] = board[7][5];   // 國王移至 g1
            board[7][5] = 0;
            board[7][6] = board[7][8];   // 車移至 f1
            board[7][8] = 0;
            white_king_moved = true;
            white_rook_moved = true;
            return true;
        }
        //長易位：國王從 e1 (7,5) 移至 c1 (7,3)
        else if (king_dst_row == 7 && king_dst_col == 3)
        {
            //檢查路徑：b1 (7,2)、c1 (7,3) 與 d1 (7,4) 必須為空
            if (board[7][2] != 0 || board[7][3] != 0 || board[7][4] != 0) return false;
            //檢查對應的車必須在 a1 (7,1) 且為白車 (3)
            if (board[7][1] != 3) return false;
            //執行易位：移動國王與車
            board[7][3] = board[7][5];   // 國王移至 c1
            board[7][5] = 0;
            board[7][4] = board[7][1];   // 車移至 d1
            board[7][1] = 0;
            white_king_moved = true;
            white_rook_moved = true;
            return true;
        }
        else
            return false;
    }
    else // 黑方
    {
        extern bool black_king_moved, black_rook_moved;
        if (black_king_moved || black_rook_moved) return false;
        if (king_src_row != 0 || king_src_col != 5) return false;

        //王側易位：國王從 e8 (0,5) 移至 g8 (0,7)
        if (king_dst_row == 0 && king_dst_col == 7)
        {
            if (board[0][6] != 0 || board[0][7] != 0) return false;
            //檢查黑車在 h8 (0,8)，黑車代號為 9
            if (board[0][8] != 9) return false;
            board[0][7] = board[0][5];   // 國王移至 g8
            board[0][5] = 0;
            board[0][6] = board[0][8];   // 車移至 f8
            board[0][8] = 0;
            black_king_moved = true;
            black_rook_moved = true;
            return true;
        }
        //后側易位：國王從 e8 (0,5) 移至 c8 (0,3)
        else if (king_dst_row == 0 && king_dst_col == 3)
        {
            if (board[0][2] != 0 || board[0][3] != 0 || board[0][4] != 0) return false;
            //檢查黑車在 a8 (0,1)
            if (board[0][1] != 9) return false;
            board[0][3] = board[0][5];   // 國王移至 c8
            board[0][5] = 0;
            board[0][4] = board[0][1];   // 車移至 d8
            board[0][1] = 0;
            black_king_moved = true;
            black_rook_moved = true;
            return true;
        }
        else
            return false;
    }
}

bool white_king_moved = false, black_king_moved = false; //檢測王有沒有移動過 用於判斷王車易位
bool white_rook_moved = false, black_rook_moved = false; //檢測車有沒有移動過

int main()
{
    //輸出初始棋盤
    print_board();

    string in_coor, end_coor, player;
    int count = 0; //當count為偶數則為白方 反之為黑方
    int src_row, src_col, dst_row, dst_col;
    bool white_king_life = true, black_king_life = true;


    while (white_king_life == true && black_king_life == true) //當王的生命沒被檢測到則結束迴圈(遊戲) 代表被其他棋子吃掉
    {
        if (count % 2 == 0) player = "白方";
        else player = "黑方";
        bool valid = true;
        do
        {
            valid = true;
            cout << "\n" << player << "要移動哪顆棋子(輸入座標，例如 a1): ";
            cin >> in_coor;
            src_row = 8 - (in_coor[1] - '0'); // 例如 '1' => 8-1 = 7
            src_col = in_coor[0] - 'a' + 1;   // 例如 'a' => 0+1 = 1
            if (board[src_row][src_col] == 0)
            {
                cout << "錯誤：該位置沒有棋子，請重新輸入座標。" << endl;
                valid = false;
            }

            if (board[src_row][src_col] > 0 && board[src_row][src_col] < 7 && count % 2 != 0)//黑方動白方的棋子
            {
                cout << "錯誤：你是黑方不可移動白方的棋子。" << endl;
                valid = false;
            }

            if (board[src_row][src_col] > 6 && board[src_row][src_col] < 13 && count % 2 == 0)//白方動黑方的棋子
            {
                cout << "錯誤：你是白方不可移動黑方的棋子。" << endl;
                valid = false;
            }

        } while (board[src_row][src_col] == 0 || valid == false);

        cout << "\n" << player << "要移動這顆棋子到哪裡(輸入座標，例如 b3): ";
        cin >> end_coor;
        dst_row = 8 - (end_coor[1] - '0');
        dst_col = end_coor[0] - 'a' + 1;

        //判別是哪一兵種
        int src_piece = board[src_row][src_col];
        int dst_piece = board[dst_row][dst_col];

        // 是否為王移動（包括正常走法與王車易位）
        if (src_piece == 1 || src_piece == 7)
        {
            bool validMove = false;
            do
            {
                int temp1;
                // 正常國王走法：移動一格
                if (king(src_row, src_col, dst_row, dst_col))
                {
                    validMove = true;
                    temp1 = board[src_row][src_col];
                    board[dst_row][dst_col] = temp1;
                    board[src_row][src_col] = 0;
                    if (src_piece == 1)
                        white_king_moved = true;
                    else
                        black_king_moved = true;
                }
                // 判斷是否為王車易位
                else if ((src_piece == 1 && castle(src_row, src_col, dst_row, dst_col, true)) ||
                    (src_piece == 7 && castle(src_row, src_col, dst_row, dst_col, false)))
                {
                    validMove = true;
                }
                else
                {
                    cout << "錯誤：該走法違規，請重新輸入起始和目的座標：" << endl;
                    cout << "要移動哪顆棋子(輸入座標，例如 a1): ";
                    cin >> in_coor;
                    cout << "要移動這顆棋子到哪裡(輸入座標，例如 b3): ";
                    cin >> end_coor;
                    src_row = 8 - (in_coor[1] - '0');
                    src_col = in_coor[0] - 'a' + 1;
                    dst_row = 8 - (end_coor[1] - '0');
                    dst_col = end_coor[0] - 'a' + 1;
                    // 若重新輸入 重置國王移動狀態以避免產生 bug
                    if (src_piece == 1)
                        white_king_moved = false;
                    else
                        black_king_moved = false;
                }
            } while (!validMove);
        }
        //是否為后
        else if (src_piece == 2 || src_piece == 8)
        {
            string in_coor, end_coor;
            bool validMove = false;
            do
            {
                int temp1;

                if (queen(src_row, src_col, dst_row, dst_col))
                {
                    validMove = true;
                    // 移動棋子：保存原位置棋子並更新目標及原位置
                    temp1 = board[src_row][src_col];
                    board[dst_row][dst_col] = temp1;
                    board[src_row][src_col] = 0;
                }
                else
                {
                    cout << "錯誤：該走法違規，請重新輸入起始和目的座標：" << endl;
                    cout << "要移動哪顆棋子(輸入座標，例如 a1):";
                    cin >> in_coor;
                    cout << "要移動這顆棋子到哪裡(輸入座標，例如 b3):";
                    cin >> end_coor;
                    src_row = 8 - (in_coor[1] - '0');
                    src_col = in_coor[0] - 'a' + 1;
                    dst_row = 8 - (end_coor[1] - '0');
                    dst_col = end_coor[0] - 'a' + 1;
                }
            } while (!validMove);

        }
        //是否為車(城堡)
        else if (src_piece == 3 || src_piece == 9)
        {
            int temp1;
            bool validMove = false;
            do
            {
                if (rook(src_row, src_col, dst_row, dst_col))
                {
                    validMove = true;
                    // 移動棋子：保存原位置棋子並更新目標及原位置
                    temp1 = board[src_row][src_col];
                    board[dst_row][dst_col] = temp1;
                    board[src_row][src_col] = 0;
                    if (src_piece == 3)//白車移動過了
                        white_rook_moved = true;
                    else
                        black_rook_moved = true;
                }
                else
                {
                    cout << "錯誤：該走法違規，請重新輸入起始和目的座標：" << endl;
                    cout << "要移動哪顆棋子(輸入座標，例如 a1):";
                    cin >> in_coor;
                    cout << "要移動這顆棋子到哪裡(輸入座標，例如 b3):";
                    cin >> end_coor;
                    src_row = 8 - (in_coor[1] - '0');
                    src_col = in_coor[0] - 'a' + 1;
                    dst_row = 8 - (end_coor[1] - '0');
                    dst_col = end_coor[0] - 'a' + 1;
                    if (src_piece == 3)
                        white_rook_moved = false;
                    else
                        black_rook_moved = false;
                }
            } while (!validMove);
        }
        //是否為象(主教)
        else if (src_piece == 4 || src_piece == 10)
        {
            string in_coor, end_coor;
            bool validMove = false;
            do
            {
                int temp1;

                if (bishop(src_row, src_col, dst_row, dst_col))
                {
                    validMove = true;
                    // 移動棋子：保存原位置棋子並更新目標及原位置
                    temp1 = board[src_row][src_col];
                    board[dst_row][dst_col] = temp1;
                    board[src_row][src_col] = 0;
                }
                else
                {
                    cout << "錯誤：該走法違規，請重新輸入起始和目的座標：" << endl;
                    cout << "要移動哪顆棋子(輸入座標，例如 a1):";
                    cin >> in_coor;
                    cout << "要移動這顆棋子到哪裡(輸入座標，例如 b3):";
                    cin >> end_coor;
                    src_row = 8 - (in_coor[1] - '0');
                    src_col = in_coor[0] - 'a' + 1;
                    dst_row = 8 - (end_coor[1] - '0');
                    dst_col = end_coor[0] - 'a' + 1;
                }
            } while (!validMove);
        }
        //是否為馬(騎士)
        else if (src_piece == 5 || src_piece == 11)
        {
            string in_coor, end_coor;
            bool validMove = false;
            do
            {
                int temp1;

                if (knight(src_row, src_col, dst_row, dst_col))
                {
                    validMove = true;
                    // 移動棋子：保存原位置棋子並更新目標及原位置
                    temp1 = board[src_row][src_col];
                    board[dst_row][dst_col] = temp1;
                    board[src_row][src_col] = 0;
                }
                else
                {
                    cout << "錯誤：該走法違規，請重新輸入起始和目的座標：" << endl;
                    cout << "要移動哪顆棋子(輸入座標，例如 a1):";
                    cin >> in_coor;
                    cout << "要移動這顆棋子到哪裡(輸入座標，例如 b3):";
                    cin >> end_coor;
                    src_row = 8 - (in_coor[1] - '0');
                    src_col = in_coor[0] - 'a' + 1;
                    dst_row = 8 - (end_coor[1] - '0');
                    dst_col = end_coor[0] - 'a' + 1;
                }
            } while (!validMove);
        }
        //是否為兵
        else if (src_piece == 6 || src_piece == 12)
        {
            string in_coor, end_coor;
            bool validMove = false;
            do
            {
                int temp1;

                if (pawn(src_row, src_col, dst_row, dst_col))
                {
                    validMove = true;
                    // 移動棋子：保存原位置棋子並更新目標及原位置
                    temp1 = board[src_row][src_col];
                    board[dst_row][dst_col] = temp1;
                    board[src_row][src_col] = 0;
                }
                else
                {
                    cout << "錯誤：該走法違規，請重新輸入起始和目的座標：" << endl;
                    cout << "要移動哪顆棋子(輸入座標，例如 a1):";
                    cin >> in_coor;
                    cout << "要移動這顆棋子到哪裡(輸入座標，例如 b3):";
                    cin >> end_coor;
                    src_row = 8 - (in_coor[1] - '0');
                    src_col = in_coor[0] - 'a' + 1;
                    dst_row = 8 - (end_coor[1] - '0');
                    dst_col = end_coor[0] - 'a' + 1;
                }
            } while (!validMove);

            pawn2queen(src_row, src_col, dst_row, dst_col);
        }
        count++;
        print_board();

        //檢測王被吃掉了沒
        for (int i = 0; i < 8; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (board[i][j] == 1)//檢測到白王
                {
                    white_king_life = true;
                    break;
                }
                else
                {
                    white_king_life = false;
                }
            }
            if (white_king_life)//外層for迴圈也要break
            {
                break;
            }
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 1; j < 9; j++)
            {
                if (board[i][j] == 7)//檢測到黑王
                {
                    black_king_life = true;
                    break;
                }
                else
                {
                    black_king_life = false;
                }
            }
            if (black_king_life)//外層for迴圈也要break
            {
                break;
            }
        }
    }

    if (white_king_life == false)
    {
        cout << "遊戲結束，黑方獲勝。\n";
    }
    else if (black_king_life == false)
    {
        cout << "遊戲結束，白方獲勝。\n";
    }
}