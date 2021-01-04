def evaluate(expr):
    expr = expr.strip()
    try:
        # First, try to parse expression as an int
        val = int(expr)
        return val
    except ValueError:
        # Then, look for first operator from right to left, treating parenthesized values as atomic
        # Scan right to left, because operator precedence is left-to-right, and need to do action with the least
        # operator precedence first due to recursion
        # Similarly, need to do multiplication before addition, because addition has higher precedence
        # Track location of first addition operator, in case multiplication is not initially found
        paren_level = 0
        first_add = None
        for i in range(len(expr)-1, -1, -1):
            if expr[i] == '(':
                paren_level += 1
            elif expr[i] == ')':
                paren_level -= 1
            elif paren_level == 0:
                if expr[i] == '+':
                    if first_add is None:
                        first_add = i
                elif expr[i] == '*':
                    left_expr = expr[:(i-1)]
                    right_expr = expr[(i+2):]
                    return evaluate(left_expr) * evaluate(right_expr)

        # If no multiplication operator found, try to perform addition
        if first_add is not None:
            left_expr = expr[:(first_add-1)]
            right_expr = expr[(first_add+2):]
            return evaluate(left_expr) + evaluate(right_expr)

        # If no operator found, assuming that the entire given expression is parenthesized
        if expr[0] == '(' and expr[-1] == ')':
            return evaluate(expr[1:-1])

        print("Error: Expression {} invalid!".format(expr))
        exit()

with open('day18.txt', 'r') as f:
    print(sum(evaluate(line) for line in f))
