#!/usr/bin/python3

def evaluate(expr):
    expr = expr.strip()
    try:
        # First, try to parse expression as an int
        val = int(expr)
        return val
    except ValueError:
        # Then, look for first operator from right to left, treating parenthesized values as a single entity
        # Scan right to left, because operator precedence is left-to-right, and need to do action with the least
        # operator precedence first due to recursion
        paren_level = 0
        for i in range(len(expr)-1, -1, -1):
            if expr[i] == '(':
                paren_level += 1
            elif expr[i] == ')':
                paren_level -= 1
            elif paren_level == 0:
                if expr[i] == '+':
                    left_expr = expr[:(i-1)]
                    right_expr = expr[(i+2):]
                    return evaluate(left_expr) + evaluate(right_expr)
                elif expr[i] == '*':
                    left_expr = expr[:(i-1)]
                    right_expr = expr[(i+2):]
                    return evaluate(left_expr) * evaluate(right_expr)

        # If no operator found, assuming that the entire given expression is parenthesized
        if expr[0] == '(' and expr[-1] == ')':
            return evaluate(expr[1:-1])

        print("Error: Expression {} invalid!".format(expr))
        exit()

with open('day18.txt', 'r') as f:
    print(sum(evaluate(line) for line in f))
