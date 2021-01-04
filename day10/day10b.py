with open('day10.txt', 'r') as f:
    lines = f.readlines()
    nums = [int(line) for line in lines]
    nums.sort()
    # Include charging outlet and device's built-in adapter
    nums = [0] + nums + [max(nums) + 3]

    ways_to_reach = {num:0 for num in nums}
    ways_to_reach[0] = 1

    # Partition the number of ways to reach a number, by what the most recent move is
    for num in nums:
        if (num-1) in nums:
            ways_to_reach[num] += ways_to_reach[num-1]
        if (num-2) in nums:
            ways_to_reach[num] += ways_to_reach[num-2]
        if (num-3) in nums:
            ways_to_reach[num] += ways_to_reach[num-3]

    print(ways_to_reach[max(nums)])
