#!/usr/bin/python3

with open('day08.txt', 'r') as f:
    # Parse each line into operation and argument, with array to store whether each command has been executed
    lines = f.readlines()
    ops = [line[:3] for line in lines]
    args = [int(line[4:]) for line in lines]
    executed = [False for line in lines]

    # Keep track of a program counter and accumulator
    pc = 0
    acc = 0

    # Keep executing commands, stopping before any instruction is repeated
    while not executed[pc]:
        executed[pc] = True
        command = ops[pc]
        if command == 'nop':
            pc += 1
        elif command == 'acc':
            acc += args[pc]
            pc += 1
        elif command == 'jmp':
            pc += args[pc]

    print(acc)
