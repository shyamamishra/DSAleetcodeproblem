class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {

        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1, 0);

        for (int x : nums)
            freq[x]++;

        vector<long long> cnt(mx + 1, 0);

        // cnt[d] = numbers divisible by d
        for (int d = 1; d <= mx; d++) {
            for (int m = d; m <= mx; m += d)
                cnt[d] += freq[m];
        }

        vector<long long> gcdCount(mx + 1, 0);

        // Inclusion-Exclusion
        for (int d = mx; d >= 1; d--) {

            long long pairs = cnt[d] * (cnt[d] - 1) / 2;

            for (int m = d + d; m <= mx; m += d)
                pairs -= gcdCount[m];

            gcdCount[d] = pairs;
        }

        // Prefix sums
        vector<long long> prefix(mx + 1, 0);

        for (int i = 1; i <= mx; i++)
            prefix[i] = prefix[i - 1] + gcdCount[i];

        vector<int> ans;

        for (long long q : queries) {

            int l = 1, r = mx;

            while (l < r) {

                int mid = (l + r) / 2;

                if (prefix[mid] > q)
                    r = mid;
                else
                    l = mid + 1;
            }

            ans.push_back(l);
        }

        return ans;
    }
};