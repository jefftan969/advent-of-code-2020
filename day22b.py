from collections import deque

def stringify_decks(player1, player2):
    return str(player1) + str(player2)

# Returns 1 if Player 1 wins the game, 2 if Player 2 wins the game
def recursive_combat(player1, player2):
    card_history = set()

    # Keep playing rounds until someone runs out of cards
    while len(player1) > 0 and len(player2) > 0:
        # If some previous round had exact same cards in same order, Player 1 wins the game
        deck_str = stringify_decks(player1, player2)
        if deck_str in card_history:
            return (1, player1)
        card_history.add(deck_str)

        # Draw cards
        card1 = player1.popleft()
        card2 = player2.popleft()

        if len(player1) >= card1 and len(player2) >= card2:
            # If both players have enough cards, then recurse to determine round winner
            player1_slice = deque(list(player1)[:card1])
            player2_slice = deque(list(player2)[:card2])
            (winner, _) = recursive_combat(player1_slice, player2_slice)
        else:
            # Otherwise, see who has the biggest card
            winner = 1 if card1 > card2 else 2

        if winner == 1:
            # Player 1 wins the round
            player1.append(card1)
            player1.append(card2)
        else:
            # Player 2 wins the round
            player2.append(card2)
            player2.append(card1)

    # Determine winner of game
    if len(player2) == 0:
        # Player 1 wins
        return (1, player1)
    else:
        # Player 2 wins
        return (2, player2)

with open('day22.txt', 'r') as f:
    players = f.read().strip().split('\n\n')
    player1_list = players[0].split('\n')[1:]
    player1 = deque([int(card) for card in player1_list])
    player2_list = players[1].split('\n')[1:]
    player2 = deque([int(card) for card in player2_list])

    # Play the game
    (winner, winner_deck) = recursive_combat(player1, player2)
    winner_deck = list(winner_deck)
    winner_score = sum((len(winner_deck) - i) * winner_deck[i] for i in range(len(winner_deck)))
    print(winner_score)
