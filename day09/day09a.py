#!/usr/bin/python3

# Use two-pointer method through sorted list to find a pair of numbers that add to desired sum
# To make more efficient, instead of re-sorting the entire list every time, can use a doubly linked list to
# track the 25 immediately preceding numbers, and continually remove the oldest element and insert a new
# element into the correct sorted location
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
    # Find invalid number that's not a sum of two numbers in the 25 immediately preceding numbers
    for i in range(25, len(nums)):
        prev_nums = nums[(i-25):i]
        if not exists_pair_with_sum(prev_nums, nums[i]):
            print(nums[i])
            break
