def parse_rule_string(s):
    [rule, matches] = s.strip().split(': ')
    if matches[0] == '"' and matches[2] == '"':
        return (rule, matches[1])
    match_list = [sequence_str.split(' ') for sequence_str in matches.split(' | ')]
    return (rule, match_list)

# If a match is found, returns a list of indices at which matching possibly stops
# Otherwise, returns the empty list
def match_helper(rules, message, rule, index):
    match_list = rules[rule]

    # Matching fails if trying to match beyond the end of the string
    if index >= len(message):
        return []

    # Matching a single character
    if isinstance(match_list, str):
        if message[index] == match_list:
            return [index+1]
        else:
            return []
    # Otherwise, proceed through definition of the rule, recursively calling match
    else:
        matches_found = []
        for rule_seq in match_list:
            # Apply rules in sequence, where matched_indices keeps track of the list of indices at which
            # matching should continue after matching successfully up to the current rule
            matched_indices = match_helper(rules, message, rule_seq[0], index)
            for rule_id in range(1, len(rule_seq)):
                new_matched_indices = []
                for matched_index in matched_indices:
                    new_matched_indices += match_helper(rules, message, rule_seq[rule_id], matched_index)
                matched_indices = list(set(new_matched_indices))
            matches_found += matched_indices
        return list(set(matches_found))

# Returns true if the message matches the given rule
def match(rules, message, rule):
    return (len(message) in match_helper(rules, message, rule, 0))

with open('day19.txt', 'r') as f:
    [rule_strings, messages] = f.read().strip().split('\n\n')
    rule_strings = rule_strings.split('\n')
    messages = messages.split('\n')

    rules = {rule: match_list for (rule, match_list) in [parse_rule_string(s) for s in rule_strings]}

    valid_count = sum(1 for message in messages if match(rules, message, '0'))
    print(valid_count)
