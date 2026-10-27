import random

# Define the suits and ranks of a standard deck of cards
suits = ["Hearts", "Diamonds", "Clubs", "Spades"]
ranks = ["2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"]

# Assign values to each rank for comparison
rank_values = {rank: index for index, rank in enumerate(ranks, start=2)}

# Create a deck of cards
def create_deck():
    deck = [f"{rank} of {suit}" for suit in suits for rank in ranks]
    random.shuffle(deck)
    return deck

# Draw a card from the deck
def draw_card(deck):
    return deck.pop() if deck else None

# Get the rank of a card
def get_rank(card):
    return card.split(" ")[0]

# Main game logic
def play_card_game():
    # Initialize the deck and players' scores
    deck = create_deck()
    player1_score = 0
    player2_score = 0

    print("Starting the card game!\n")

    # Play until the deck is empty
    while deck:
        # Each player draws a card
        player1_card = draw_card(deck)
        player2_card = draw_card(deck)

        if not player1_card or not player2_card:
            break

        print(f"Player 1 draws: {player1_card}")
        print(f"Player 2 draws: {player2_card}")

        # Compare the ranks of the cards
        player1_rank = get_rank(player1_card)
        player2_rank = get_rank(player2_card)

        if rank_values[player1_rank] > rank_values[player2_rank]:
            print("Player 1 wins this round!\n")
            player1_score += 1
        elif rank_values[player1_rank] < rank_values[player2_rank]:
            print("Player 2 wins this round!\n")
            player2_score += 1
        else:
            print("It's a tie!\n")

    # Display the final scores
    print("Game Over!")
    print(f"Player 1 Score: {player1_score}")
    print(f"Player 2 Score: {player2_score}")

    # Determine the winner
    if player1_score > player2_score:
        print("Player 1 wins the game!")
    elif player1_score < player2_score:
        print("Player 2 wins the game!")
    else:
        print("The game is a tie!")

# Run the game
if __name__ == "__main__":
    play_card_game()