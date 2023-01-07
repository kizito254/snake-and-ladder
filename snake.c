using System;
using System.Collections.Generic;

namespace SnakeAndLadder
{
    class Game
    {
        // The board size
        private const int BOARD_SIZE = 100;

        // The starting position for each player
        private const int START_POSITION = 0;

        // The players
        private Player[] players;

        // The current player
        private int currentPlayer;

        // The positions of the ladders on the board
        private Dictionary<int, int> ladders;

        // The positions of the snakes on the board
        private Dictionary<int, int> snakes;

        public Game(int numPlayers)
        {
            // Initialize the players array
            players = new Player[numPlayers];

            // Create a new player for each player
            for (int i = 0; i < numPlayers; i++)
            {
                players[i] = new Player(START_POSITION);
            }

            // Set the current player to the first player
            currentPlayer = 0;

            // Initialize the ladders dictionary
            ladders = new Dictionary<int, int>
            {
                { 3, 50 },
                { 6, 25 },
                { 20, 70 },
                { 36, 55 },
                { 63, 95 }
            };

            // Initialize the snakes dictionary
            snakes = new Dictionary<int, int>
            {
                { 54, 19 },
                { 62, 18 },
                { 81, 14 },
                { 92, 31 },
                { 95, 72 }
            };
        }

        public void Play()
        {
            // Roll the dice and move the current player
            int roll = RollDice();
            players[currentPlayer].Move(roll);

            // Check if the player landed on a ladder
            if (ladders.ContainsKey(players[currentPlayer].Position))
            {
                players[currentPlayer].Move(ladders[players[currentPlayer].Position] - players[currentPlayer].Position);
                Console.WriteLine("You climbed a ladder to square " + players[currentPlayer].Position);
            }

            // Check if the player landed on a snake
            if (snakes.ContainsKey(players[currentPlayer].Position))
            {
                players[currentPlayer].Move(snakes[players[currentPlayer].Position] - players[currentPlayer].Position);
                Console.WriteLine("You were bitten by a snake and moved down to square " + players[currentPlayer].Position);
            }

            // Check if the player has won
            if (players[currentPlayer].Position == BOARD_SIZE - 1)
            {
                Console.WriteLine("Player " + (currentPlayer + 1) + " wins!");
                return;
            }

            // Switch to the next player
            currentPlayer = (currentPlayer + 1) % players.Length;
        }

        // Roll a dice and return the result
        private int RollDice()
        {
            Random random = new Random();
            return random.Next(1, 7);
        }
    }

    class Player
    {
        private int position;

        public int Position
        {
            get { return position; }
        }

        public Player(
