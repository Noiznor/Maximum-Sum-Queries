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
Time complexity:
1. Sorting the indices of nums1 takes O(n * log(n)), where n is the length of nums1.
2. Sorting the indices of queries takes O(n_queries * log(n_queries)), where n_queries is the length of queries.
3. Iterating through the queries and processing each query requires a loop that runs for n_queries iterations. Within each iteration, we perform operations like removing elements from the stack and performing binary search. These operations take O(log(n)) time complexity.
Overall: O(n * log(n) + n_queries * log(n_queries) + n_queries * log(n)).

Space complexity:
1. The additional arrays indices1 and indices_q have sizes of n and n_queries, respectively. Therefore, they contribute O(n + n_queries) space complexity.
2. The stack st stores pairs of values and can have at most n elements if all elements of nums1 satisfy the conditions. Hence, it contributes O(n) space complexity.
3. The resulting vector ret has n_queries elements. Therefore, it contributes O(n_queries) space complexity.
Overall: the space complexity is O(n + n_queries).
