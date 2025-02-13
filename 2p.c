#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20000  // 余裕を持った盤面サイズ

void print_board(char *board, int left, int right) {// 盤面を表示する関数
    printf("Board: ");
    for (int i = left; i <= right; i++) {
        printf("%c", board[i]);
    }
    printf("\n");
}

int main() {
    char board[MAX_SIZE];  // 1次元リバーシの盤面
    int left, right;  // 盤面の両端
    int turn = 0;  // 0: 黒(b)、1: 白(w)
    int num;
    char itte;

    // 盤面を初期化
    memset(board, '.', sizeof(board)); // '.' で初期化（空のマス）

    // ターン数を入力
    printf("ターン数：");
    scanf("%d", &num);

    // 盤面の中央付近に初期配置
    int mid = MAX_SIZE / 2;
    left = mid;
    right = mid + 1;
    board[left] = 'b';  // 初期黒石
    board[right] = 'w'; // 初期白石

    // 初期配置を表示
    printf("最初の盤面：bw\n");

    // 棋譜の処理
    for (int i = 0; i < num; i++) {
        turn = i % 2; // 交互に黒白を置く
        char stone = (turn == 0) ? 'b' : 'w'; // 偶数ターンは黒、奇数ターンは白

        if(turn == 0) 
            printf("黒の手番\n");
        else 
            printf("白の手番\n");
        
        printf("一手（L/R）：");
        
        scanf(" %c", &itte); // 余分な空白を追加して改行文字を無視

        if (itte == 'L') {
            left--; // 左に移動
            board[left] = stone;
        } else if (itte == 'R') {
            right++; // 右に移動
            board[right] = stone;
        } else {
            printf("無効な入力です。'L' または 'R' を入力してください。\n");
            i--; // 無効入力の場合、ターンを戻す
            continue;
        }

        // 挟んだ石をひっくり返す
        int flip_pos = (itte == 'L') ? left + 1 : right - 1;// 挟む石の位置
        while (flip_pos < right && flip_pos > left && board[flip_pos] != '.' && board[flip_pos] != stone) {// 挟む石が空白でない間
            board[flip_pos] = stone;// 石をひっくり返す
            flip_pos += (itte == 'L') ? 1 : -1;// 次の位置
        }

        // 盤面を表示
        print_board(board, left, right);
    }

    // 石の数をカウント
    int black_count = 0, white_count = 0;
    for (int i = left; i <= right; i++) {
        if (board[i] == 'b') black_count++;
        if (board[i] == 'w') white_count++;
    }

    // 結果を出力
    printf("黒: %d 白: %d\n", black_count, white_count);

    if(black_count > white_count) {
        printf("黒の勝ち\n");
    } else if(black_count < white_count) {
        printf("白の勝ち\n");
    } else {
        printf("引き分け\n");
    }

    return 0;
}
