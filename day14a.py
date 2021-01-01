import parse

def apply_mask(value, mask):
    value_str = format(int(value), "036b")
    result = list(value_str)
    for i in range(len(mask)):
        if mask[i] != 'X':
            # If mask specifies 0 or 1, overwrite that result bit
            result[i] = mask[i]
    return "".join(result)

with open('day14.txt', 'r') as f:
    lines = f.readlines()
    mask = ""
    mem = {}
    for line in lines:
        mask_cmd = parse.parse("mask = {}\n", line)
        if mask_cmd is None:
            # If current command does not set the bitmask, interpret as a write to memory
            mem_cmd = parse.parse("mem[{}] = {}\n", line)
            addr = int(mem_cmd[0])
            value = mem_cmd[1]
            mem[addr] = apply_mask(value, mask)
        else:
            # Otherwise, replace the current bitmask
            mask = mask_cmd[0]

    # Find sum of all values currently stored in memory
    print(sum(int(value_str, 2) for value_str in mem.values()))
