#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_S_LEN 1000001
#define MAX_T_LEN 1000001
#define DEQUE_SIZE (MAX_S_LEN + MAX_T_LEN + 5)
#define START_IDX (MAX_T_LEN + 2)

typedef struct {
    char color;
    long long count;
} Block;

static char S[MAX_S_LEN];
static char T[MAX_T_LEN];
static Block deque[DEQUE_SIZE];

int main() {
    if (scanf("%s", S) != 1) return 1;
    if (scanf("%s", T) != 1) return 1;

    int s_len = strlen(S);
    int t_len = strlen(T);

    int head = START_IDX;
    int tail = START_IDX - 1;

    if (s_len > 0) {
        tail++;
        deque[tail].color = S[0];
        deque[tail].count = 1;
        for (int i = 1; i < s_len; ++i) {
            if (S[i] == deque[tail].color) {
                deque[tail].count++;
            } else {
                tail++;
                deque[tail].color = S[i];
                deque[tail].count = 1;
            }
        }
    }
    
    int is_empty = head > tail;

    for (int i = 0; i < t_len; ++i) {
        char current_color = (i % 2 == 0) ? 'b' : 'w';
        char move_dir = T[i];

        if (is_empty) {
            head = START_IDX;
            tail = START_IDX;
            deque[head].color = current_color;
            deque[head].count = 1;
            is_empty = 0;
            continue;
        }

        if (move_dir == 'L') {
            if (deque[head].color == current_color) {
                deque[head].count++;
            } else { 
                if (head == tail) {
                    head--;
                    deque[head].color = current_color;
                    deque[head].count = 1;
                } else {
                    long long flip_count = deque[head].count;
                    head++;
                    
                    deque[head].count += flip_count + 1;
                }
            }
        } else {
            if (deque[tail].color == current_color) {
                deque[tail].count++;
            } else {
                if (head == tail) {
                    tail++;
                    deque[tail].color = current_color;
                    deque[tail].count = 1;
                } else {
                    long long flip_count = deque[tail].count;
                    tail--;
                    deque[tail].count += flip_count + 1;
                }
            }
        }
    }

    long long black_count = 0;
    long long white_count = 0;
    for (int i = head; i <= tail; ++i) {
        if (deque[i].color == 'b') {
            black_count += deque[i].count;
        } else {
            white_count += deque[i].count;
        }
    }

    printf("%lld %lld\n", black_count, white_count);

    return 0;
}
