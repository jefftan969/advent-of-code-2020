from collections import deque

with open('day22.txt', 'r') as f:
    players = f.read().strip().split('\n\n')
    player1_list = players[0].split('\n')[1:]
    player1 = deque([int(card) for card in player1_list])
    player2_list = players[1].split('\n')[1:]
    player2 = deque([int(card) for card in player2_list])

    # Keep playing rounds until a player runs out of cards
    while len(player1) > 0 and len(player2) > 0:
        # Draw cards
        card1 = player1.popleft()
        card2 = player2.popleft()

        if card1 > card2:
            # Player 1 wins
            player1.append(card1)
            player2.append(card2)
        else:
            # Player 2 wins
            player2.append(card2)
            player2.append(card1)

    # Determine winner score
    winner_deck = list(player1) + list(player2)
    winner_score = sum((len(winner_deck) - i) * winner_deck[i] for i in range(len(winner_deck)))
    print(winner_score)
