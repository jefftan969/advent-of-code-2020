with open('day06.txt', 'r') as f:
    all_lines = f.read()
    group_strings = all_lines.split('\n\n')
    groups = [group_str.replace('\n', '') for group_str in group_strings]
    group_counts = [len(set(group)) for group in groups]
    print(sum(group_counts))

# One line solution:
# print(sum([len(set(group_str.replace('\n', ''))) for group_str in open('day06.txt', 'r').read().split('\n\n')]))
