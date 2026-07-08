class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> idx;
        vector<int> digit;

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                idx.push_back(i);
                digit.push_back(s[i] - '0');
            }
        }

        int k = digit.size();

        vector<long long> prefNum(k + 1, 0);
        vector<long long> prefSum(k + 1, 0);
        vector<long long> pow10(k + 1, 1);

        for (int i = 1; i <= k; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        for (int i = 0; i < k; i++) {
            prefNum[i + 1] = (prefNum[i] * 10 + digit[i]) % MOD;
            prefSum[i + 1] = prefSum[i] + digit[i];
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int L = lower_bound(idx.begin(), idx.end(), l) - idx.begin();
            int R = upper_bound(idx.begin(), idx.end(), r) - idx.begin() - 1;

            if (L > R) {
                ans.push_back(0);
                continue;
            }

            int len = R - L + 1;

            long long x = (prefNum[R + 1] -
                          (prefNum[L] * pow10[len]) % MOD + MOD) % MOD;

            long long sum = prefSum[R + 1] - prefSum[L];

            ans.push_back((x * (sum % MOD)) % MOD);
        }

        return ans;
    }
};