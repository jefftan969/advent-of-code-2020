with open('day25.txt', 'r') as f:
    [card_pk, door_pk] = [int(line) for line in f.read().strip().split('\n')]
    
    # Find card's secret loop size
    card_loop_size = 0
    card_value = 1
    card_subj = 7
    lcg_base = 20201227

    while card_value != card_pk:
        card_loop_size += 1
        card_value = (card_value * card_subj) % lcg_base

    # Transform door's public key according to card's loop size
    enc_key = 1
    for i in range(card_loop_size):
        enc_key = (enc_key * door_pk) % lcg_base

    print(enc_key)
