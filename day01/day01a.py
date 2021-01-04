with open('day01.txt', 'r') as f:
    # Read input from file, and sort
    nums = [int(line) for line in f]
    nums.sort()

    # Scan through input for two numbers that add to 2020
    # Use two pointers into sorted list, one starting on the left and the other starting on the right
    # If sum too small, increment left pointer to increase the sum
    # If sum too large, decrement right pointer to decrease the sum
    # Eventually, if two numbers exist adding to 2020, they will be found
    desired_sum = 2020
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
            print(x*y)
            break

