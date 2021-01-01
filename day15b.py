with open('day15.txt', 'r') as f:
    nums = [int(s) for s in f.read().strip().split(',')]
    # Track when each number was last spoken, to avoid linear search
    last_spoken = {}
    for i in range(len(nums)-1):
        last_spoken[nums[i]] = i
    while len(nums) < 30000000:
        num = nums[-1]
        # If most recent number has not been spoken before, say 0
        next_num = 0
        if num in last_spoken:
            # Otherwise, specify how many turns apart the previous occurrence was
            next_num = len(nums) - 1 - last_spoken[num]
        last_spoken[num] = len(nums)-1
        nums.append(next_num)
    print(nums[-1])
