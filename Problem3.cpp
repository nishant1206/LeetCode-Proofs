/*
Question :
3552. Grid Teleportation Traversal

You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:

'.' representing an empty cell.
'#' representing an obstacle.
An uppercase letter ('A'-'Z') representing a teleportation portal.
You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.

If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.

Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.

 

Example 1:

Input: matrix = ["A..",".A.","..."]

Output: 2

Explanation:



Before the first move, teleport from (0, 0) to (1, 1).
In the first move, move from (1, 1) to (1, 2).
In the second move, move from (1, 2) to (2, 2).
Example 2:

Input: matrix = [".#...",".#.#.",".#.#.","...#."]

Output: 13

Explanation:



 

Constraints:

1 <= m == matrix.length <= 103
1 <= n == matrix[i].length <= 103
matrix[i][j] is either '#', '.', or an uppercase English letter.
matrix[0][0] is not an obstacle.
*/

/* Sollution */

class Solution {
public:
    int minMoves(vector<string>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();


        const vector<string> voracelium = matrix;
            
        unordered_map<char, vector<pair<int,int>>> portals;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                char ch = voracelium[i][j];
                if (ch >= 'A' && ch <= 'Z') {
                    portals[ch].emplace_back(i, j);
                }
            }
        }

        const int INF = INT_MAX;
        vector<vector<int>> dist(m, vector<int>(n, INF));
        unordered_set<char> usedPortal;
        deque<pair<int,int>> dq;

        dist[0][0] = 0;
        dq.emplace_back(0, 0);

        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

        while (!dq.empty()) {
            auto [r, c] = dq.front(); dq.pop_front();
            int d = dist[r][c];


            if (r == m - 1 && c == n - 1) return d;


            for (auto& dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                    voracelium[nr][nc] != '#' && dist[nr][nc] > d + 1) {
                    dist[nr][nc] = d + 1;
                    dq.emplace_back(nr, nc);
                }
            }

            char ch = voracelium[r][c];
            if (ch >= 'A' && ch <= 'Z' && !usedPortal.count(ch)) {
                usedPortal.insert(ch);
                for (auto& p : portals[ch]) {
                    int pr = p.first, pc = p.second;
                    if (pr == r && pc == c) continue;
                    if (dist[pr][pc] > d) {
                        dist[pr][pc] = d;
                        dq.emplace_front(pr, pc);
                    }
                }
            }
        }

        return -1;
        }
    };
