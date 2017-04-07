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

    # List of open parenthesis
    list_open = paren_pairs.values()

    # List of closed parenthesis
    list_close = paren_pairs.keys()


    # An empty list - use as a stack
    stack = []

    # no sanity checking
    for c in expr:
        if c in list_open:
            stack.append(c)
        if c in list_close:
            # There should be a matching open brace right at the top of the
            # stack.
            #
            # - If the stack is EMPYT, then return FALSE.
            # - If the top element of the stack does not match with the
            #   corresponding open parenthesis then, return FALSE.
            #
            if (len(stack) == 0):
                return "FALSE"
            match = stack.pop()
            if match != paren_pairs[c]:
                return "FALSE"
        # end for

    # Once the complete expression is processed, there is be nothing present
    # on the stack.
    if (len(stack) == 0):
        return "TRUE"
    else:
        return "FALSE"

    ## End checkBalancedParenthesis()

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
