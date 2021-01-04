# Algorithm for two-sum, using two pointers into sorted list (one starting on left, the other on right)
# If sum too small, increment left pointer to increase the sum
# If sum too large, increment right pointer to decrease the sum
# Eventually, if two numbers exist that add up to 2020, will converge on it
def findpair(nums, desired_sum):
    start_index = 0
    end_index = len(nums) - 1
    while(start_index < end_index):
        x = nums[start_index]
        y = nums[end_index]
        current_sum = x + y
        if current_sum < desired_sum:
            start_index += 1
        elif current_sum > desired_sum:
            end_index -= 1
        else:
            return (x,y)
    return None

with open('day01.txt', 'r') as f:
    # Read input from file, and sort
    nums = [int(line) for line in f]
    nums.sort()

    # Scan through input for three numbers that add to 2020
    # For each number in list, subtract that number from desired_sum, and
    # run two-sum algorithm on remainder of the list
    desired_sum = 2020
    for i in range(len(nums)):
        pair = findpair(nums[(i+1):], desired_sum - nums[i])
        if pair is not None:
            x = nums[i]
            y = pair[0]
            z = pair[1]
            print(x*y*z)
            break


