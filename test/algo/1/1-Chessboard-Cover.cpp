//
// Created by LOKKA on 2020/5/17.
//

#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;
int tile = 0;
int bd[mxN][mxN];

void chessBoard(int tr, int tc, int dr, int dc, int size) {
    if (size == 1) return;
    int t = tile++;
    int s = size / 2;
    if (dr < tr + s && dc < tc + s) {
        chessBoard(tr, tc, dr, dc, s);
    } else {
        bd[tr + s - 1][tc + s - 1] = t;
        chessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
    }
    if (dr < tr + s && dc >= tc + s) {
        chessBoard(tr, tc + s, dr, dc, s);
    } else {
        bd[tr + s - 1][tc + s] = t;
        chessBoard(tr, tc + s, tr + s - 1, tc + s, s);
    }
    if (dr >= tr + s && dc < tc + s) {
        chessBoard(tr + s, tc, dr, dc, s);
    } else {
        bd[tr + s][tc + s - 1] = t;
        chessBoard(tr + s, tc, tr + s, tc + s - 1, s);
    }
    if (dr >= tr + s && dc >= tc + s) {
        chessBoard(tr + s, tc + s, dr, dc, s);
    } else {
        bd[tr + s][tc + s] = t;
        chessBoard(tr + s, tc + s, tr + s, tc + s, s);
    }
}

int main() {
    int n, x, y;
    printf("��������������:");
    cin >> n;
    printf("��������%d*%d�����ϲ��ɸ��ǵ������:", n, n);
    cin >> x >> y;
    bd[x][y] = -1;
    chessBoard(0, 0, x, y, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", bd[i][j]);
        }
        printf("\n");
    }
}