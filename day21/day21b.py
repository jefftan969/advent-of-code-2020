import parse

def parse_line(line):
    result = parse.parse("{} (contains {})", line)
    ingredients = set(result[0].split(' '))
    allergens = result[1].split(', ')
    return (ingredients, allergens)

with open('day21.txt', 'r') as f:
    food_table = [parse_line(line) for line in f.readlines()]

    # Create mapping from allergens to the possible ingredients that could contain that allergen
    allergen_table = {}
    for i in range(len(food_table)):
        (ingredient_row, allergen_row) = food_table[i]
        for allergen in allergen_row:
            if allergen in allergen_table.keys():
                allergen_table[allergen].append(ingredient_row)
            else:
                allergen_table[allergen] = [ingredient_row]
    allergen_table = {key:set.intersection(*value) for (key, value) in allergen_table.items()}

    # Determine what ingredient each allergen corresponds to
    allergen_matches = {}
    while True:
        allergen_match_found = False
        for allergen in allergen_table.keys():
            ingredients = allergen_table[allergen]
            if len(ingredients) == 1:
                # If a match is found, save the match and remove that allergen-ingredient pairing from the table
                ingredient_match = list(ingredients)[0]
                allergen_matches[allergen] = ingredient_match
                for allergen in allergen_table.keys():
                    if ingredient_match in allergen_table[allergen]:
                        allergen_table[allergen].remove(ingredient_match)
                allergen_match_found = True
                break
        if not allergen_match_found:
            break

    # Determine canonical dangerous ingredient list
    dangerous_list = []
    for key in sorted(allergen_matches):
        dangerous_list.append(allergen_matches[key])
    print(','.join(dangerous_list))
