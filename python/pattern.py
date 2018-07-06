'''
A pattern can be represented as a string containing lowercase English letters and special characters: question marks and asterisks. Each question mark should be replaced by exactly one letter, and each asterisk should be replaced by zero or more letters (possibly different).

A string of letters matches a pattern if question marks and asterisks in the latter can be replaced by letters in such a way that pattern will become equal to a given string.

Does a given string match a given pattern?

Example

For input = "abacaba" and pattern = "?*b?", the output should be
patternMatching(input, pattern) = true;
For input = "abacaba" and pattern = "?*ca?", the output should be
patternMatching(input, pattern) = false.
Input/Output

[execution time limit] 4 seconds (py)

[input] string input

A string of lowercase Latin letters.

Guaranteed constraints:
1 ≤ input.length ≤ 10.

[input] string pattern

A string of lowercase Latin letters, question marks and asterisks.

Guaranteed constraints:
4 ≤ pattern.length ≤ 10.

[output] boolean

true if input string matches pattern, false otherwise.
'''
# there is one bug in the following code.
def patternMatching(inputStr, pattern):

    dp = []
    for i in range(len(inputStr) + 1):
        line = []
        for j in range(len(pattern) + 1):
            line.append(False)
        dp.append(line)

    dp[0][0] = True
    for i in range(len(inputStr) + 1):
        for j in range(len(pattern)):
            if not dp[i][j]:
                continue
            if (i < len(inputStr)
            and (inputStr[i] == pattern[j] or inputStr[j] == '?')):
                dp[i + 1][j + 1] = True
            if pattern[j] == '*':
                for k in range(len(inputStr) - i + 1):
                    dp[i + k][j + 1] = True

    return dp[len(inputStr)][len(pattern)]

