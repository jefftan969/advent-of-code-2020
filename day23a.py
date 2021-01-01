from collections import deque

with open('day23.txt', 'r') as f:
    nums = list(f.read().strip())
    circle_size = len(nums)
    # Circle represented as a deque with current cup in index 0
    circle = deque([int(char) for char in nums], maxlen = circle_size)

    for i in range(100):
        curr_num = circle.popleft()

        # Remove three cups immediately clockwise from current cup
        removed_num1 = circle.popleft()
        removed_num2 = circle.popleft()
        removed_num3 = circle.popleft()

        # Decrement current number to find destination number, until finding a cup not picked up
        dest_num = curr_num
        while dest_num not in circle:
            dest_num -= 1
            if dest_num == 0:
                dest_num = circle_size

        # Find destination cup
        dest_index = None
        for i in range(len(circle)):
            if circle[i] == dest_num:
                dest_index = i
                break

        # Place picked-up cups immediately clockwise of destination cup
        circle.insert(dest_index+1, removed_num3)
        circle.insert(dest_index+1, removed_num2)
        circle.insert(dest_index+1, removed_num1)

        # Place current cup at end, so the current cup in the next iteration is one step clockwise to the right
        circle.append(curr_num)

    # Rotate circular buffer around until cup 1 is the current cup
    while circle[0] != 1:
        left_num = circle.popleft()
        circle.append(left_num)

    print(''.join([str(char) for char in list(circle)[1:]]))
