/**
 * Time Complexity: O(n * log(n) + n_queries * log(n_queries) + n_queries * log(n))
 * Space Complexity: O(n + n_queries)
 * where `n` is the length of the vector `nums1`
 *       `n_queries` is the length of the vector `queries`
 */
/**
 * Time Complexity: O(n * log(n) + n_queries * log(n_queries) + n_queries * log(n))
 * Space Complexity: O(n + n_queries)
 * where `n` is the length of the vector `nums1`
 *       `n_queries` is the length of the vector `queries`
 */
class Solution {
private:
  using st_node_t = pair<int, int>;
  
  static constexpr int cant_find = -1;
  
public:
  vector<int> maximumSumQueries(const vector<int> &nums1,
                                const vector<int> &nums2,
                                const vector<vector<int>> &queries) {
    const int n = static_cast<int>(nums1.size());
    int indices1[n];
    iota(indices1, indices1 + n, 0);
    sort(indices1, indices1 + n, [&nums1](const int lhs, const int rhs) -> bool {
      return nums1[lhs] > nums1[rhs];
    });
    
    const int n_queries = static_cast<int>(queries.size());
    int indices_q[n_queries];
    iota(indices_q, indices_q + n_queries, 0);
    sort(indices_q, indices_q + n_queries, [&queries](const int lhs, const int rhs) -> bool {
      return queries[lhs].front() > queries[rhs].front();
    });
    
    vector<int> ret(n_queries, cant_find);
    vector<st_node_t> st;
    for (int j = 0, i = 0; i < n_queries; ++i) {
      const int i_query = indices_q[i];
      const int q_num1 = queries[i_query].front();
      const int q_num2 = queries[i_query].back();
      for (; j < n && nums1[indices1[j]] >= q_num1; ++j) {
        const int num1 = nums1[indices1[j]];
        const int num2 = nums2[indices1[j]];
        while (!st.empty() && st.back().second <= num1 + num2) {
          st.pop_back();
        }
        if (st.empty() || st.back().first < num2) {
          st.emplace_back(num2, num1 + num2);
        }
      }
      auto lb = lower_bound(st.begin(), st.end(), make_pair(q_num2, 0));
      ret[i_query] = lb == st.end() ? cant_find : lb->second;
    }
    return ret;
  }
};
