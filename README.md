# Maximum-Sum-Queries

# Intuition
- To find the maximum sum for each query, we can iterate through the elements of nums1 in descending order and maintain a monotonically decreasing stack. The stack will store pairs of values where the first element is from nums2 and the second element is the sum of corresponding elements from nums1 and nums2. By doing so, we can efficiently find the maximum sum for each query using binary search.
# Approach
1. Sort the indices of nums1 in descending order based on their corresponding values. This will allow us to iterate through nums1 in descending order efficiently.
2. Sort the indices of queries in descending order based on the first element of each query. This will allow us to process queries in descending order of the required condition.
3. Initialize an empty stack (st) to maintain the monotonically decreasing values.
4. Iterate through the queries and perform the following steps:
- Retrieve the current query queries[i_query].
- Iterate through the remaining elements of nums1 starting from the current index j and perform the following steps:
- Retrieve the current element values num1 and num2 from nums1 and nums2 using the sorted indices.
- Remove elements from the stack (st) that are not useful for the current query by checking if their sum (second value of the pair) is less than or equal to num1 + num2.
- If the stack (st) is empty or the top element's first value (nums2 value) is less than num2, then push the current pair (num2, num1 + num2) to the stack.
- Use binary search (lower_bound) on the stack (st) to find the first element with a first value greater than or equal to the second element (q_num2) of the current query.
- If a valid pair is found, assign its second value as the result for the current query. Otherwise, assign -1 to indicate that no valid pair was found.
5. Return the resulting vector ret containing the maximum sums for each query.
# Complexity
- Time complexity:
O(n * log(n) + n_queries * log(n_queries) + n_queries * log(n))
- Space complexity:
 O(n + n_queries)
# Code
```
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
