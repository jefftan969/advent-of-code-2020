def modify_program(ops, index):
    modified = list(ops)
    if modified[index] == 'nop':
        modified[index] = 'jmp'
    elif modified[index] == 'jmp':
        modified[index] = 'nop'
    return modified


def eval_program(ops, args):
    executed = [False for op in ops]
    pc = 0
    acc = 0
    # Keep executing commands, stopping before any instruction is repeated, or on program termination
    while (pc < len(ops)) and (not executed[pc]):
        executed[pc] = True
        command = ops[pc]
        if command == 'nop':
            pc += 1
        elif command == 'acc':
            acc += args[pc]
            pc += 1
        elif command == 'jmp':
            pc += args[pc]

    # Return accumulator if program terminated normally
    if pc == len(ops):
        return acc
    return None

with open('day08.txt', 'r') as f:
    # Parse each line into operation and argument
    lines = f.readlines()
    ops = [line[:3] for line in lines]
    args = [int(line[4:]) for line in lines]

    # For every line, modify that line and see if program terminates normally on evaluation
    for index in range(len(lines)):
        result = eval_program(modify_program(ops, index), args)
        if result is not None:
            print(result)
            break
