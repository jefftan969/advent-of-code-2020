#!/usr/bin/python3

with open('day15.txt', 'r') as f:
    nums = [int(s) for s in f.read().strip().split(',')]
    while len(nums) < 2020:
        num = nums[-1]
        # If the most recent number has not been spoken before, say 0
        next_num = 0
        for i in range(1, len(nums)):
            # Search backwards to see whether the most recent number has been spoken before
            j = len(nums) - 1 - i
            if nums[j] == num:
                # Specify how many turns apart the previous occurrence was
                next_num = i
                break
        nums.append(next_num)
    print(nums[-1])
