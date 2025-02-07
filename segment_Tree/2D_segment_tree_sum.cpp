#include <bits/stdc++.h>
using namespace std;

const int Max_row = 1000;
const int Max_cols = 1000;

vector<vector<int>> tree, seg;
int n, m;

// Build segment tree along Y-dimension
void buildY(int lowx, int highx, int posx, int lowy, int highy, int posy) {
    if (lowy == highy) {
        if (lowx == highx) {
            seg[posx][posy] = tree[lowx][lowy];
        } else {
            seg[posx][posy] = seg[posx * 2 + 1][posy] + seg[posx * 2 + 2][posy];
        }
    } else {
        int mid = (lowy + highy) / 2;
        buildY(lowx, highx, posx, lowy, mid, posy * 2 + 1);
        buildY(lowx, highx, posx, mid + 1, highy, posy * 2 + 2);
        seg[posx][posy] = seg[posx][posy * 2 + 1] + seg[posx][posy * 2 + 2];
    }
}

// Build segment tree along X-dimension
void buildX(int low, int high, int posx) {
    if (low == high) {
        buildY(low, high, posx, 0, m - 1, 0);
    } else {
        int mid = (low + high) / 2;
        buildX(low, mid, posx * 2 + 1);
        buildX(mid + 1, high, posx * 2 + 2);
        buildY(low, high, posx, 0, m - 1, 0);
    }
}

// Update along Y-dimension
void updateY(int lowx, int highx, int posx, int lowy, int highy, int posy, int indx, int indy, int val) {
    if (lowy == highy) {
        if (lowx == highx) {
            seg[posx][posy] = val;
        } else {
            seg[posx][posy] = seg[posx * 2 + 1][posy] + seg[posx * 2 + 2][posy];
        }
    } else {
        int mid = (lowy + highy) / 2;
        if (indy <= mid)
            updateY(lowx, highx, posx, lowy, mid, posy * 2 + 1, indx, indy, val);
        else
            updateY(lowx, highx, posx, mid + 1, highy, posy * 2 + 2, indx, indy, val);

        seg[posx][posy] = seg[posx][posy * 2 + 1] + seg[posx][posy * 2 + 2];
    }
}

// Update along X-dimension
void updateX(int lowx, int highx, int posx, int indx, int indy, int val) {
    if (lowx == highx) {
        updateY(lowx, highx, posx, 0, m - 1, 0, indx, indy, val);
    } else {
        int mid = (lowx + highx) / 2;
        if (indx <= mid)
            updateX(lowx, mid, posx * 2 + 1, indx, indy, val);
        else
            updateX(mid + 1, highx, posx * 2 + 2, indx, indy, val);

        updateY(lowx, highx, posx, 0, m - 1, 0, indx, indy, val);
    }
}

// Query along Y-dimension
int queryY(int qlowy, int qhighy, int lowy, int highy, int posy, int posx) {
    if (qlowy > highy || qhighy < lowy) return 0; // Out of range
    if (qlowy <= lowy && qhighy >= highy) return seg[posx][posy]; // Full overlap

    int mid = (lowy + highy) / 2;
    return queryY(qlowy, qhighy, lowy, mid, posy * 2 + 1, posx) +
           queryY(qlowy, qhighy, mid + 1, highy, posy * 2 + 2, posx);
}

// Query along X-dimension
int queryX(int qlowx, int qhighx, int qlowy, int qhighy, int lowx, int highx, int posx) {
    if (qlowx > highx || qhighx < lowx) return 0; // Out of range
    if (qlowx <= lowx && qhighx >= highx) return queryY(qlowy, qhighy, 0, m - 1, 0, posx); // Full overlap

    int mid = (lowx + highx) / 2;
    return queryX(qlowx, qhighx, qlowy, qhighy, lowx, mid, posx * 2 + 1) +
           queryX(qlowx, qhighx, qlowy, qhighy, mid + 1, highx, posx * 2 + 2);
}

int main() {
    cin >> n >> m;

    tree.resize(n, vector<int>(m, 0));
    seg.resize(4 * n, vector<int>(4 * m, 0));

    // Read input matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> tree[i][j];

    // Build the segment tree
    buildX(0, n - 1, 0);

    // Example update: Set (2,3) to 10
    int row = 2, col = 3, newVal = 10;
    updateX(0, n - 1, 0, row, col, newVal);

    // Example range sum query: Sum from (1,1) to (3,3)
    int x1 = 1, y1 = 1, x2 = 3, y2 = 3;
    int result = queryX(x1, x2, y1, y2, 0, n - 1, 0);
    cout << "Sum in range (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ") = " << result << endl;

    return 0;
}
