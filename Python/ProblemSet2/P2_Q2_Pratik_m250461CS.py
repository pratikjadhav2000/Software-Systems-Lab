def wildcard_match(s: str, p: str) -> bool:
    """
    Returns True if pattern p matches entire string s.
    p may contain:
      ? -> matches any single character
      * -> matches any sequence of characters (including empty)
    """
    n, m = len(s), len(p)
    # dp[i][j] = does p[:j] match s[:i] ?
    dp = [[False] * (m + 1) for _ in range(n + 1)]
    dp[0][0] = True

    # Empty string with pattern having leading '*' characters
    for j in range(1, m + 1):
        if p[j - 1] == "*":
            dp[0][j] = dp[0][j - 1]
        else:
            break

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if p[j - 1] == s[i - 1] or p[j - 1] == "?":
                dp[i][j] = dp[i - 1][j - 1]
            elif p[j - 1] == "*":
                # '*' can match:
                #   - empty sequence  -> dp[i][j-1]
                #   - one more char   -> dp[i-1][j]
                dp[i][j] = dp[i][j - 1] or dp[i - 1][j]
            else:
                dp[i][j] = False

    return dp[n][m]


def run_wildcard_problem():
    s = input("Enter the source string: ")
    p = input("Enter the pattern string: ")
    match = wildcard_match(s, p)
    print("Pattern matches string:", match)
