with open('day23.txt', 'r') as f:
    nums = [int(char) for char in list(f.read().strip())]
    circle_max = len(nums)
    circle_size = 1000000

    # Circle is an array, where the entry at index i is the cup that comes after Cup i
    circle = [None] * (circle_size+1)

    # Fill circle
    for i in range(len(nums)-1):
        circle[nums[i]] = nums[i+1]
    circle[nums[-1]] = circle_max + 1
    for i in range(circle_max+1, circle_size):
        circle[i] = i+1
    circle[-1] = nums[0]

    curr_num = nums[0]

    for i in range(10000000):
        # Find three cups immediately clockwise from current cup
        removed_num1 = circle[curr_num]
        removed_num2 = circle[removed_num1]
        removed_num3 = circle[removed_num2]

        # Decrement current number to find destination number, until finding a cup not picked up
        dest_num = curr_num
        while dest_num in [curr_num, removed_num1, removed_num2, removed_num3]:
            dest_num -= 1
            if dest_num == 0:
                dest_num = circle_size

        # Place picked-up cups immediately clockwise of destination cup
        circle[curr_num] = circle[removed_num3]
        dest_num_next = circle[dest_num]
        circle[dest_num] = removed_num1
        circle[removed_num3] = dest_num_next

        # Advance current cup one step clockwise to the right
        curr_num = circle[curr_num]

    # Find the two numbers after cup 1
    print(circle[1] * circle[circle[1]])
