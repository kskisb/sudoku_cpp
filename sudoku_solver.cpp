#include <bits/stdc++.h>
using namespace std;

int N = 9;
vector<vector<vector<int>>> ans;

bool check(vector<vector<int>> &field, int si, int sj) {
    // 行ごとに同じ文字がないかチェック
    vector<int> num1(10, 0);
    for(int j=0; j<N; j++) {
        if(field[si][j] == -1) {
            continue;
        }
        if(num1[field[si][j]] == 1) {
            return false;
        } else {
            num1[field[si][j]]++;
        }
    }
    // 列ごとに同じ文字がないかチェック
    vector<int> num2(10, 0);
    for(int i=0; i<N; i++) {
        if(field[i][sj] == -1) {
            continue;
        }
        if(num2[field[i][sj]] == 1) {
            return false;
        } else {
            num2[field[i][sj]]++;
        }
    }
    // ブロックごとに同じ文字がないかチェック
    if(si <= 2) si = 0;
    else if(si <= 5) si = 3;
    else si = 6;

    if(sj <= 2) sj = 0;
    else if(sj <= 5) sj = 3;
    else sj = 6;
    
    vector<int> num3(10, 0);
    for(int k=0; k<3; k++) {
        for(int l=0; l<3; l++) {
            if(field[si+k][sj+l] == -1) {
                continue;
            }
            if(num3[field[si+k][sj+l]] == 1) {
                return false;
            } else {
                num3[field[si+k][sj+l]]++;
            }
        }
    }

    return true;
}

// 再帰で探索
void rec(vector<vector<int>> &field) {
    if(ans.size() > 10000) return;
    bool flag = true;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(field[i][j] == -1) {
                flag = false;
            }
        }
    }
    if(flag) {
        ans.push_back(field);
        return;
    }

    int si = -1, sj = -1;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(field[i][j] == -1) {
                si = i;
                sj = j;
            }
        }
    }

    for(int k=1; k<10; k++) {
        field[si][sj] = k;
        if(!check(field, si, sj)) continue;
        rec(field);
    }
    field[si][sj] = -1;
}

int main() {
    srand((unsigned)time(NULL));
    int Time = clock();
    vector<vector<int>> field(N, vector<int>(N, -1));

    cout << "9×9の盤面を入力してください。" << endl;
    cout << "ただし、数字が埋まっていない場所は * としてください。" << endl;
    cout << "- 入力欄 -" << endl;
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        for(int j=0; j<N; j++) {
            if(s[j] == '*') {
                continue;
            } else {
                field[i][j] = s[j] - '0';
            }
        }
    }
    cout << "- 入力欄 -" << endl;

    // 探索開始
    rec(field);

    cout << endl;
    if(ans.size() == 0) {
        cout << "答えは存在しません。" << endl;
        return 0;
    } else if(ans.size() > 1) {
        cout << "答えが複数あります。" << endl << "そのうちの１つの";
    }
    int n = ans.size();
    int r = rand() % n;
    cout << "答えは以下の通りです。（解答時間: ";
    printf("%.2lf 秒）\n", 1.0*(clock()-Time)/CLOCKS_PER_SEC);
    for(int i=0; i<N; i++) {
        if(i%3 == 0) cout << "-------------------------------" << endl;
        for(int j=0; j<N; j++) {
            if(j%3 == 0) printf("|%2d ", ans[r][i][j]);
            else printf("%2d ", ans[r][i][j]);
        }
        cout << "| " << endl;
    }
    cout << "-------------------------------" << endl;
}