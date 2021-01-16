#!/usr/bin/python3

with open('day10.txt', 'r') as f:
    lines = f.readlines()
    nums = [int(line) for line in lines]
    nums.sort()
    # Include charging outlet and device's built-in adapter
    nums = [0] + nums + [max(nums) + 3]

    # Find pairwise differences to determine number of 1-diffs and 3-diffs
    diffs = [(nums[i] - nums[i-1]) for i in range(1, len(nums))]
    num_1diffs = sum(1 for diff in diffs if diff == 1)
    num_3diffs = sum(1 for diff in diffs if diff == 3)
    print(num_1diffs * num_3diffs)
