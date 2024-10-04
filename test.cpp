#include <bits/stdc++.h>
 
using namespace std;
using Graph = vector<vector<int>>;

// Complexity of CalcMatchingSize (Kuhn algorithm): O(nm), but in reality it's faster
class KuhnMatching {
private:
    const Graph& g;
    vector<int> matched;
    vector<char> used;
 
    bool TryKuhn(int v) {
        if (used[v])  return false;
        used[v] = true;
        for (int to : g[v]) {
			// If matched[to] == -1, then we can use it
			// Otherwise we try to find matching for vertex it's currently matched to
            if (matched[to] == -1 || TryKuhn(matched[to])) {
                matched[to] = v;
                return true;
            }
        }
        return false;
    }
 
public:
    // g must contain only first part
    KuhnMatching(const Graph& g_, int secondPartSize)
    : g(g_)
    , matched(vector<int>(secondPartSize, -1))
    , used(vector<char>(g.size(), false))
    {}
 
	// If zeroIfNotPerfect is set, answer is 0 or perfect matching size, but it also speeds up code 
    int CalcMatchingSize(bool zeroIfNotPerfect = false) {
        int ans = 0;
 
        // Approximate matching to speed up Kuhn
        vector<char> usedFirstPart(g.size(), false);
        for (size_t v = 0; v < g.size(); ++v) {
            for (int to : g[v]) {
                if (matched[to] == -1) {
                    ++ans;
                    matched[to] = v;
                    usedFirstPart[v] = true;
                    break;
                }
            }
        }
 
        for (size_t i = 0; i < g.size(); ++i) {
            if (usedFirstPart[i]) {
                continue;
            }
            if (TryKuhn(i)) {
                ++ans;
                used.assign(used.size(), false);
            } else {
                if (zeroIfNotPerfect) {
                    return 0;
                }
            }
        }
        return ans;
    }
 
	// If noneIfNotPerfect is set, answer is {} or perfect matching, but it also speeds up code
    vector<pair<int, int>> CalcMatching(bool noneIfNotPerfect = false) {
        vector<pair<int, int>> matching;
        matching.reserve(CalcMatchingSize(noneIfNotPerfect));
        if (matching.capacity() == 0) {
            return matching;
        }
 
        for (size_t i = 0; i < matched.size(); ++i) {
            if (matched[i] != -1) {
                matching.emplace_back(matched[i], i);
            }
        }
        return matching;
    }
};


struct Performance {
    uint64_t perf1 = 0, perf2 = 0;

    void set_high(size_t i) {
        if (i >= 64) {
            perf2 |= 1ull << (i - 64);
        } else {
            perf1 |= 1ull << i;
        }
    }

    void set_low(size_t i) {
        if (i >= 64) {
            perf2 ^= 1ull << (i - 64);
        } else {
            perf1 ^= 1ull << i;
        }
    }

    bool inverted(const Performance& p) {
        return perf1 == ~p.perf1 && perf2 == ~p.perf2;
    }
};

void run() {
    int n, m;
    cin >> n >> m;

    vector<Performance> performance(n * 2), inv_performance(n * 2, Performance{UINT64_MAX, UINT64_MAX});

    map<int, int> part_high, part_low;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            int score;
            cin >> score;
            if (score > n) {
                performance[j].set_high(i);
            } else {
                inv_performance[j].set_low(i);
            }
            if (i == 0) {
                if (score > n) {
                    part_high[j] = part_high.size();
                } else {
                    part_low[j] = part_low.size();
                }
            }
        }
    }

    Graph g(n);
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = i + 1; j < 2 * n; ++j) {
            if (performance[i].inverted(inv_performance[j])) {
                if (part_high.count(i)) {
                    g[part_high[i]].push_back(part_low[j]);
                } else {
                    g[part_high[j]].push_back(part_low[i]);
                }
            }
        }
    }

    if (KuhnMatching(g, n).CalcMatchingSize(true)) {
        cout << "success" << endl;
    } else {
        cout << "fail" << endl;
    }
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie();
    int t = 1;
    // cin >> t;
    for (int test = 1; test <= t; ++test) {
        run();
    }
}