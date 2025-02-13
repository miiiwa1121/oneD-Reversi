#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20000  // 余裕を持った盤面サイズ

int main() {
    char S[MAX_SIZE];  // 入力の棋譜
    char board[MAX_SIZE];  // 1次元リバーシの盤面
    int left, right;  // 盤面の両端
    int turn = 0;  // 0: 黒(b)、1: 白(w)

    // 入力を取得
    scanf("%s", S);

    int len = strlen(S);
    
    // 盤面の中央付近に初期配置
    int mid = MAX_SIZE / 2;
    left = mid;
    right = mid + 1;
    board[left] = 'b';  // 初期黒石
    board[right] = 'w'; // 初期白石

    // 棋譜の処理
    for (int i = 0; i < len; i++) {
        turn = i % 2; // 交互に黒白を置く
        char stone = (turn == 0) ? 'b' : 'w';

        if (S[i] == 'L') {
            left--; // 左に移動
            board[left] = stone;
        } else {
            right++; // 右に移動
            board[right] = stone;
        }

        // 挟んだ石をひっくり返す
        int flip_start = (S[i] == 'L') ? left + 1 : right - 1;
        int flip_end = (S[i] == 'L') ? right : left;

        while (flip_start < flip_end && board[flip_start] != stone) {
            board[flip_start] = stone;
            flip_start++;
        }
    }

    // 石の数をカウント
    int black_count = 0, white_count = 0;
    for (int i = left; i <= right; i++) {
        if (board[i] == 'b') black_count++;
        if (board[i] == 'w') white_count++;
    }

    // 結果を出力
    printf("%d %d\n", black_count, white_count);

    return 0;
}