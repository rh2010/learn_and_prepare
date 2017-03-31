#! /usr/bin/env python
#
# Check for balanced parenthesis
#
import os
import sys
import time
import re


def checkBalancedParenthesis(expr):
    paren_pairs = {']':'[',
                   '}':'{',
                   ')':'(',
                   }
    list_open = paren_pairs.values()
    list_close = paren_pairs.keys()


    stack = []

    # no sanity checking
    for c in expr:
        if c in list_open:
            stack.append(c)
        if c in list_close:
            if (len(stack) == 0):
                return "FALSE"
            match = stack.pop()
            if match != paren_pairs[c]:
                return "FALSE"
        # end for

    if (len(stack) == 0):
        return "TRUE"
    else:
        return "FALSE"

    ## End twoSum

if __name__ == "__main__":
    expr = "[()]{}{[()()]()}"

    expr1 = "[{()(]}"
    expr2 = "[(])"
    expr3 = "[{("
    expr4 = "]})"

    print("Expression %s is balanced: %s\n" % (expr, checkBalancedParenthesis(expr)))
    print("Expression %s is balanced %s\n" % (expr1, checkBalancedParenthesis(expr1)))
    print("Expression %s is balanced %s\n" % (expr2, checkBalancedParenthesis(expr2)))
    print("Expression %s is balanced %s\n" % (expr3, checkBalancedParenthesis(expr3)))
    print("Expression %s is balanced %s\n" % (expr4, checkBalancedParenthesis(expr4)))

    ## End main
