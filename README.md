# longest-common-prefix-dp
Longest Common Prefix solved with Dyanmic Programming

An unconventional, unique solution to the classic **Longest Common Prefix (LCP)** problem written in C++. 

Instead of traditional horizontal scanning or vertical matching, this implementation customizes the **Longest Common Subsequence (LCS)** Dynamic Programming matrix structure. It isolates strict prefixes by mathematically validating progressive character matches exclusively along the matrix's prime diagonal.

## The Why
I wanted more practice with dp for my graduate algorithms class where we learned about Longest Common Subsequence (LCS). In another entirely different class, I was assigned the LCP problem as a quiz assignment and I realized that I could probably write a cool solution which would be very similar to the dp solution of LCS.

## 🚀 The Approach

Standard LCS algorithms evaluate non-contiguous sequences across a 2D grid using a maximization fallback rule (`std::max(top, left)`). This codebase adapts that 2D space for prefixes:
1. It maps out string matches iteratively across a structured `(N+1) x (M+1)` matrix space.
2. It breaks the traditional subsequence trap by implementing a sequential fallback constraint.
3. A validation pass traces down the true matrix diagonal `table[t][t]`. If a cell value increments continuously (`max + 1`), the prefix chain remains unbroken. The moment the sequence stalls, the lookup terminates instantly to guarantee contiguous slicing.

## 📋 Sample Run & Test Harness

The main workflow natively evaluates standard edge cases, single-element vectors, completely disconnected string pairs, and hidden duplicate subsequences:
```

Test Case 1: Result = "app"

Test Case 2: Result = "fl"

Test Case 3: Result = ""

Test Case 4: Result = "ref"

Test Case 5: Result = "inters"

Test Case 6: Result = "throne"

Test Case 7: ""


Test Case 8: Result = ""

Test Case 9: Result = "solitude"

Test Case 10: Result = ""
```

## 📊 Complexity Analysis

Because this solution translates the prefix matching problem into a 2D matrix coordinate space, its performance matches the bounds of typical grid-based dynamic programming:

### 1. Time Complexity: \(\mathcal{O}(N \times M)\)
* **Table Generation:** The main engine relies on a nested loop structure where the outer loop iterates over the rows (\(N = \text{s1.size()}\)) and the inner loop iterates over the columns (\(M = \text{s2.size()}\)). This creates an underlying execution bottleneck of exactly \(\mathcal{O}(N \times M)\).
* **Diagonal Validation:** Tracing the true prime diagonal to extract the string slice requires a single pass bounded by \(\mathcal{O}(\min(N, M))\), which is computationally negligible compared to the matrix population phase.
* **Global Test Runner:** Across a sequence of W words within the `main` loop, the absolute time scaling behaves as \(\mathcal{O}(W \times N \times M)\).

### 2. Space Complexity: \(\mathcal{O}(N \times M)\)
* **Memory Allocation:** The dynamic grid tracking state allocates a grid structure of size (N + 1) × (M + 1) elements. Drop-off constants yield a clean spatial complexity notation of \(\mathcal{O}(N \times M)\).