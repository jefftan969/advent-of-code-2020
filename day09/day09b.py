#!/usr/bin/python3

# Use two-pointer method through sorted list to find a pair of numbers that add to desired sum
def exists_pair_with_sum(nums, desired_sum):
    nums.sort()
    left_ptr = 0
    right_ptr = len(nums) - 1
    while left_ptr < right_ptr:
        curr_sum = nums[left_ptr] + nums[right_ptr]
        if curr_sum < desired_sum:
            left_ptr += 1
        elif curr_sum > desired_sum:
            right_ptr -= 1
        else:
            return True
    return False

with open('day09.txt', 'r') as f:
    lines = f.readlines()
    nums = [int(line) for line in lines]

    # Find invalid number that's not the sum of two numbers in the immediately preceding 25
    invalid_num = None
    for i in range(25, len(nums)):
        prev_nums = nums[(i-25):i]
        if not exists_pair_with_sum(prev_nums, nums[i]):
            invalid_num = nums[i]
            break

    # Find sums of every possible contiguous set of numbers, by accumulating onto the list contiguous_sums
    # Each iteration of outer loop finds all possible contiguous sums of a given length
    # Each iteration of inner loop considers the contiguous sum that starts at a different index
    contiguous_sums = list(nums)
    for offset in range(1, len(nums)-1):
        for i in range(len(nums) - offset):
            contiguous_sums[i] += nums[i+offset];
            if contiguous_sums[i] == invalid_num:
                # Successfully found a contiguous sum that adds to the invalid number
                contiguous_range = nums[i:(i+offset+1)]
                enc_weakness = min(contiguous_range) + max(contiguous_range)
                print(enc_weakness)
                exit()
