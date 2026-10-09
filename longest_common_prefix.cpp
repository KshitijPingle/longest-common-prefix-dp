/* Longest Common Prefix problem

    Write a function that finds the longest starting substring (prefix) shared by every string in a given array.
    If no common prefix exists, the function returns an empty string ("")

Author Info:
Kshitij Pingle
pinglekshitij15@gmail.com

8 October, 2026
Thursday


Sample Test cases
Example 1:
Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
*/

#include <iostream>
#include <vector>
#include <string>
#include <limits>


/*
Recursive Solution to LCS

def LCS(n): Returns an int for the longest common subsequence between two strings

Tautology:
Should I use the S[n] element?
Yes -> 1 + LCS(n - 1)
No -> LCS(n - 1)

Base Case:
if 0 == n: return 0
*/

std::string longest_common_prefix_recursive(int n, int m, std::string s1, std::string s2) {
    // Base Cases: If we run out of characters in either string
    if ((n == -1) || (m == -1)) {
        return "";
    }

    // Tautology: If the characters match at the current positions
    if (s1[n] == s2[m]) { // Fix: use 'm' for s2 to track its independent index
        // Build the string forward by appending the matching character to the previous results
        return longest_common_prefix_recursive(n - 1, m - 1, s1, s2) + s1[n];
    }
    else {
        // Not matching: evaluate both paths and return the string with the longest length
        std::string left_path = longest_common_prefix_recursive(n - 1, m, s1, s2);
        std::string right_path = longest_common_prefix_recursive(n, m - 1, s1, s2);
        
        return (left_path.size() > right_path.size()) ? left_path : right_path;
    }
}

std::string longest_common_prefix(std::string s1, std::string s2) {
    size_t n = s1.size();
    size_t m = s2.size();

    // Allocate the 2D grid with size (n+1) x (m+1) pre-filled with 0
    std::vector<std::vector<unsigned int>> table(n + 1, std::vector<unsigned int>(m + 1, 0));

    // Table filling loop
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                // Match
                table[i][j] = 1 + table[i - 1][ j - 1];
            }
            else {
                table[i][j] = table[i - 1][j - 1];
            }
        }
    }

    unsigned int max = 0;

    // Limit 't' to the smaller dimension so table[t][t] never goes out of bounds
    size_t limit = std::min(n, m);

    // Loop to check increasing matches
    for (size_t t = 1; t <= limit; ++t) {
        // Keep checking the diagonals from the start
        if (table[t][t] == max + 1) {
            // If they increase, then they match
            ++max;
        }
        else {
            // Not increasing any more, no matches
            break;
        }
    }

    return s1.substr(0, max);
}

int main() {
    // A collection of different test cases
    std::vector<std::vector<std::string>> test_cases = {
    //                                                                             Expected
    {"apple", "approve", "app"},           // Standard Case                         "app"
    {"flower", "flow", "flight"},          // Standard Case 2                       "fl"
    {"dog", "racecar", "car"},             // No Match Midway                       ""
    {"referee", "refresh"},                // Subsequence Trap                      "ref"
    {"interspecies", "interstellar"},      // Long Subsequence Trap                 "inters"
    {"throne", "throne"},                  // Exact Match Case                      "throne"
    {},                                    // Edge Case 1: Empty Array              ""
    {"", "flow", "flight"},                // Edge Case 2: Contains Empty String    ""
    {"solitude"},                          // Edge Case 3: Only One Word            "solitude"
    {"apple", "banana", "cherry"}          // Edge Case 4: Zero Match From Start    ""
    };

    // Loop through each test case
    for (size_t t = 0; t < test_cases.size(); ++t) {
        const auto& words = test_cases[t];
        
        std::cout << "\nTest Case " << t + 1 << ": ";
        if (words.empty()) {
            std::cout << "\"\"\n\n";
            continue;
        }

        // Initialize our common prefix to the first entire word
        std::string common_prefix = words[0];

        // Run comparison loop sequentially through the words array
        for (size_t i = 0; i < words.size() - 1; ++i) {
            int s1_last_idx = static_cast<int>(common_prefix.size()) - 1;
            int s2_last_idx = static_cast<int>(words[i + 1].size()) - 1;
            
            // Compare our accumulated prefix against the next word in the list
            // std::string result = longest_common_prefix_recursive(s1_last_idx, s2_last_idx, common_prefix, words[i + 1]);
            std::string result = longest_common_prefix(common_prefix, words[i + 1]);
            
            // The new running common prefix becomes whatever matched
            common_prefix = result;
        }

        // Print final string directly!
        std::cout << "Result = \"" << common_prefix << "\"\n";
    }

    return 0;
}