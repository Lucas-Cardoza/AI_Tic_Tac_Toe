//********************************************************************
//
// Student: Lucas Cardoza
// Course: CSC 540 - Introduction to Artificial Intelligence
// Assignment 2: Tic Tac Toe Using Minimax Algorithm
// Due Date: Saturday, February 20, 2021, 11:59 PM
// Instructor: Dr. Siming Liu
//
//********************************************************************

#include <iostream>
#include <algorithm>
#include <limits>
#include <ctime>

const int BOARDSIZE = 3;	// Size of each side of the playing board
char player = 'P', computer = 'C';	// Player tokens

// Function prototypes 
void showInstructions();
void showBoard(char board[][BOARDSIZE]);
bool movesLeft(char board[][BOARDSIZE]);
int checkForWin(char board[][BOARDSIZE]);
int minimax(char board[][BOARDSIZE], bool ai);
void playTTT(char board[][BOARDSIZE]);


// Move structure that will contain the best move for the AI
struct Move
{
	int row = 0, col = 0;
};


// Main function to game
int main()
{
	std::string go;		// Variable for user input to start or quit program
	bool quit = false;	// While loop controller variable

	//loop for program menu
	while (!quit)
	{
		std::cout << "\nPress \n'p' to play Tic Tac Toe with an AI"
			<< "\n'i' to show instructions on how to play" 
			<< "\n'q' to quit. " << std::endl;;
		std::cin >> go;

		if (go.length() > 1)
		{
			// set user input to an invalid input to trigger an invalid input response
			go = '0'; 
		}

		switch (go[0])
		{
		case 'p':
		{
			// Create the playing board
			char board[BOARDSIZE][BOARDSIZE];

			// Initialize the board to all empty spaces
			for (int i = 0; i < BOARDSIZE; i++)
			{
				for (int j = 0; j < BOARDSIZE; j++)
				{
					board[i][j] = ' ';
				}
			}

			// Call to play game function
			playTTT(board);
			break;
		}
		case 'q':
		{
			quit = true;
			break;
		}
		case 'i':
		{
			// Call to show instructions
			showInstructions();
			break;
		}
		default:
		{
			std::cout << "\nInput is not a valid option." << std::endl;
		}
		}
	}

	return 0;
}


// Function to display game play instructions
void showInstructions()
{
	std::cout << "\nUse row number and column number to choose where you"
		<< " would like to place your token.\n" << std::endl;

	// Create the demonstration board
	std::string board[BOARDSIZE][BOARDSIZE] = { "Row 1 Col 1", "Row 1 Col 2", "Row 1 Col 3",
												"Row 2 Col 1", "Row 2 Col 2", "Row 2 Col 3",
												"Row 3 Col 1", "Row 3 Col 2", "Row 3 Col 3" };

	// Display board
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			std::cout << " " << board[i][j];
			if (j < 2)
			{
				std::cout << " |";
			}
		}

		if (i < 2)
		{
			std::cout << "\n----------------------------------------" << std::endl;
		}
	}

	std::cout << "\n" << std::endl;
}


// Minimax algorithm 
int minimax(char board[][BOARDSIZE], bool aiMax)
{
	// Get winner if there is one
	int winner = checkForWin(board);

	if (winner == 1 || winner == -1)
	{
		// -1 = human win, 1 = AI win
		return winner;
	}

	// If there are no moves left to make (game was a tie)
	if (movesLeft(board) == false)
	{
		return 0;
	}
	
	// This portion is for when it is maximizer's turn 
	if (aiMax)
	{
		// Set maxValue to -infinity (not really, but as large as ints can go)
		int maxValue = -1 * (std::numeric_limits<int>::max());

		// Traverse through the board to look for possible moves
		for (int i = 0; i < BOARDSIZE; i++)
		{
			for (int j = 0; j < BOARDSIZE; j++)
			{
				// If an empty place on the board is found 
				if (board[i][j] == ' ')
				{
					// Place AI's token in empty cell
					board[i][j] = computer;
					
					// Get the largest (maximum) value by recursively calling minimax function
					// until either a winner (AI in this case) is found or the game is a tie.
					maxValue = std::max(maxValue, minimax(board, false));
					
					// Clear move to empty cell from move made above
					board[i][j] = ' ';
				}
			}
		}

		return maxValue;
	}
	
	// This portion is for when it is minimizer's turn 
	if (!aiMax)
	{
		// Set minValue to +infinity (not really, but as large as ints can go)
		int minValue = (std::numeric_limits<int>::max());

		// Traverse through the board to look for possible moves
		for (int i = 0; i < BOARDSIZE; i++)
		{
			for (int j = 0; j < BOARDSIZE; j++)
			{
				// If an empty place on the board is found 
				if (board[i][j] == ' ')
				{
					// Place human's token in empty cell
					board[i][j] = player;

					// Get the smallest (minimum) value by recursively calling minimax function
					// until either a winner (human in this case) is found or the game is a tie.
					minValue = std::min(minValue, minimax(board, true));
					
					// Clear move to empty cell from move made above
					board[i][j] = ' ';
				}
			}
		}

		return minValue;
	}
}


// Function to select the best move the AI can make
Move findAIMove(char board[][BOARDSIZE])
{
	// Create a structure to hold best move
	Move aiMove;

	// Set bestMoveScore to -infinity (not really, but as large as ints can go)
	int bestMoveScore = -1 * (std::numeric_limits<int>::max());

	// Traverse through the board to look for possible moves
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			// If an empty place on the board is found
			if (board[i][j] == ' ')
			{
				// Place AI's token in empty cell
				board[i][j] = computer;

				// Variable to hold found score value
				int score = minimax(board, false);

				if (bestMoveScore < score)
				{
					// Placing best move into structure
					aiMove.row = i;	
					aiMove.col = j;

					// Saving largest value
					bestMoveScore = score;
				}

				// Clear move to empty cell from move made above
				board[i][j] = ' ';
			}
		}
	}
	return aiMove;
}


void playTTT(char board[][BOARDSIZE])
{
	// Human player row and column choices
	int x{ 0 }, y{ 0 };

	// Create a structure to hold move AI's move
	Move aiMove;

	std::cout << "\nFirst player will be chosen at random *computer tosses coin*" << std::endl;
	
	// Creating random number generator for coin toss.
	// Using 100 instead of 2 seemed to provide a better balance 
	// of random coin tosses.
	std::srand(time(NULL));
	int coin = rand() % 100;

	if (coin < 50)
	{
		std::cout << "\nIts heads. You get to go first.\n" << std::endl;

		// Change player and AI tokens
		player = 'X';
		computer = 'O';

		// Display current playing board
		showBoard(board);
	}
	else
	{
		std::cout << "\nIts tails. AI will go first.\n" << std::endl;

		// Change player and AI tokens
		computer = 'X';
		player = 'O';

		// Find the best move for AI
		aiMove = findAIMove(board);

		// Place AI's token in empty cell
		board[aiMove.row][aiMove.col] = computer;
		std::cout << "Computer made its choice\n" << std::endl;

		// Display current playing board
		showBoard(board);
	}

	// While loop controller
	bool gameOver = false;

	// Game loop
	while (movesLeft(board) && gameOver != true)
	{
		std::cout << "Please enter the row number you would like: ";
		std::cin >> x;
		
		// Input validation
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid position.\n";
			continue;
		}

		std::cout << "Please enter the column number you would like: ";
		std::cin >> y;
		std::cout << std::endl;

		// Input validation
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid position.\n";
			continue;
		}

		// Place human player's row and column choices into x and y
		// Adjust values to match board's array cell values
		x = x - 1;
		y = y - 1;

		// Check to see if cell is valid choice
		if (board[x][y] != ' ')
		{
			std::cout << "Spot is either already taken or is not on the board.\n" << std::endl;
			continue;
		}

		// Check to make sure cell is empty
		if (board[x][y] == ' ')
		{
			// Place human player's token in empty cell
			board[x][y] = player;
			
			// Display current playing board
			showBoard(board);

			// Check for a winner 
			int win = checkForWin(board);

			if (win == -1)
			{
				std::cout << "Human wins!!" << std::endl;
				gameOver = true;
			}
			else if (win == 1)
			{
				std::cout << "Computer wins!!" << std::endl;
				gameOver = true;
			}
			else if (movesLeft(board) == false)
			{
				std::cout << "Its a tie game" << std::endl;
				gameOver = true;
			}
			else // If there are no winners yet, AI's turn to place token
			{
				// Find the best move for AI
				aiMove = findAIMove(board);

				// Place AI's token in empty cell
				board[aiMove.row][aiMove.col] = computer;
				std::cout << "Computer made its choice\n" << std::endl;

				// Display current playing board
				showBoard(board);

				// Check for winners 
				win = checkForWin(board);

				if (win == -1)
				{
					std::cout << "Human wins!!" << std::endl;
					gameOver = true;
				}
				else if (win == 1)
				{
					std::cout << "Computer wins!!" << std::endl;
					gameOver = true;
				}
				else if (movesLeft(board) == false)
				{
					std::cout << "Its a tie game" << std::endl;
					gameOver = true;
				}
			}
		}
	}
}


// Function to check for a winning player
int checkForWin(char board[][BOARDSIZE])
{
	// Check all rows for a winner
	for (int i = 0; i < BOARDSIZE; i++)
	{
		if (board[i][0] == board[i][1] 
			&& board[i][1] == board[i][2]
			&& board[i][0] != ' ')
		{
			if (board[i][0] == computer)
			{
				return +1;
			}
			else if (board[i][0] == player)
			{
				return -1;
			}
		}
	}

	// Check all columns for a winner
	for (int j = 0; j < BOARDSIZE; j++)
	{
		if (board[0][j] == board[1][j]
			&& board[1][j] == board[2][j]
			&& board[0][j] != ' ')
		{
			if (board[0][j] == computer)
			{
				return +1;
			}
			else if (board[0][j] == player)
			{
				return -1;
			}
		}
	}
	
	// Check the backwards leaning diagonal for a winner
	if (board[0][0] == board[1][1]
		&& board[1][1] == board[BOARDSIZE - 1][BOARDSIZE - 1]
		&& board[0][0] != ' ')
	{
		if (board[0][0] == computer)
		{
			return +1;
		}
		else if (board[0][0] == player)
		{
			return -1;
		}
	}

	// Check the forwards leaning diagonal for a winner
	if (board[0][BOARDSIZE - 1] == board[1][1]
		&& board[1][1] == board[BOARDSIZE - 1][0]
		&& board[0][BOARDSIZE - 1] != ' ')
	{
		if (board[0][BOARDSIZE - 1] == computer)
		{
			return +1;
		}
		else if (board[0][BOARDSIZE - 1] == player)
		{
			return -1;
		}
	}

	// If there is no winner
	return 0;
}


// Function to check if there are any empty cells left to move token into
bool movesLeft(char board[][BOARDSIZE])
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			// Check to make sure cell is empty
			if (board[i][j] == ' ')
			{
				return true;
			}
		}
	}

	return false;
}


// Function to display board on screen
void showBoard(char board[][BOARDSIZE])
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			std::cout << " " << board[i][j];
			if (j < 2)
			{
				std::cout << " |";
			}
		}

		if (i < 2)
		{
			std::cout << "\n-----------" << std::endl;
		}
	}

	std::cout << "\n" << std::endl;
}
