import parse

mem = {}

# Recursively writes the given value to the memory address(es) specified by addrlist
def write_to_memory(value, addrlist, scan_index):
    if scan_index == len(addrlist):
        # If entire memory address has been scanned for X's, write directly to memory
        addr = int("".join(addrlist), 2)
        mem[addr] = value
    elif addrlist[scan_index] == 'X':
        # If current bit of memory address is 'X', recursively spawn two instances of write_to_memory,
        # one interpreting the 'X' as 0 and the other interpreting the 'X' as 1
        addrlist_0 = list(addrlist)
        addrlist_1 = list(addrlist)
        addrlist_0[scan_index] = '0'
        addrlist_1[scan_index] = '1'
        write_to_memory(value, addrlist_0, scan_index + 1)
        write_to_memory(value, addrlist_1, scan_index + 1)
    else:
        # If current bit of memory address is not 'X', continue scanning the next memory address bit for 'X'
        write_to_memory(value, addrlist, scan_index + 1)

def apply_mask(value, mask):
    value_str = format(int(value), "036b")
    result_list = list(value_str)
    for i in range(len(mask)):
        if mask[i] != '0':
            result_list[i] = mask[i]
    return result_list

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
            addrlist = apply_mask(addr, mask)
            write_to_memory(value, addrlist, 0)
        else:
            # Otherwise, replace the current bitmask
            mask = mask_cmd[0]

    # Find sum of all values currently stored in memory
    print(sum(int(value_str) for value_str in mem.values()))
