#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char human);
void announceWinner(char winner, char computer, char human);

int main() {
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();

	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;

	displayBoard(board);

	while (winner(board) == NO_ONE)
	{
		if (turn == human) {
			move = humanMove(board, human);
			board[move] = human;
		}
		else {
			move = computerMove(board, computer);
			board[move] = computer;
		}

		displayBoard(board);
		turn = opponent(turn);
	}

	announceWinner(winner(board), computer, human);

	return 0;
}

/// <summary>
/// Правила игры
/// </summary>
void instructions() {
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silicon processor\n\n";
	cout << "Make your move known by entering a number, 0-8. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << "0 | 1 | 2\n";
	cout << "---------\n";
	cout << "3 | 4 | 5\n";
	cout << "---------\n";
	cout << "6 | 7 | 8\n";
	cout << "Prepare youself, human. The battle is about to begin.\n\n";
}

/// <summary>
/// Задаёт вопрос, на который можно ответить Да или Нет
/// </summary>
/// <param name="question">Вопрос</param>
/// <returns></returns>
char askYesNo(string question) {
	char response;

	do {
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}

/// <summary>
/// Запрашивает у пользователя число из диапазона
/// </summary>
/// <param name="question">Вопрос</param>
/// <param name="high">Максимальное число</param>
/// <param name="low">Минимальное число</param>
/// <returns>Число из указанного диапазона</returns>
int askNumber(string question, int high, int low) {
	int number;

	do {
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);

	return number;
}

/// <summary>
/// Предлагает пользователю выбрать свой игровой символ
/// </summary>
/// <returns>Выбраный символ игрока</returns>
char humanPiece() {
	char goFirst = askYesNo("Do you require the first move?");
	
	if (goFirst == 'y') {
		cout << "\nThen take the first move. You will need it.\n";
		return X;
	}
	
	cout << "\nYour bravery will be your undoing... I will go first.\n";
	return O;
}

/// <summary>
/// Передаёт ход другому игроку
/// </summary>
/// <param name="piece"></param>
/// <returns>Символ игрока</returns>
char opponent(char piece) {
	if (piece == X) {
		return O;
	}
	
	return X;
}

/// <summary>
/// Отображает игровое поле
/// </summary>
/// <param name="board">Игровое поле</param>
void displayBoard(const vector<char>& board) {
	cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n\t" << "---------";
	cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
	cout << "\n\t" << "---------";
	cout << "\n\n";
}

/// <summary>
/// Возвращает победителя игры
/// </summary>
/// <param name="board">Игровое поле</param>
/// <returns>Символ игрока-победителя или промежуточный результат</returns>
char winner(const vector<char>& board) {
	const int WINNING_ROWS[8][3] = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6}
	};
	
	const int TOTAL_ROWS = 8;

	for (int row = 0; row < TOTAL_ROWS; ++row) {
		// проверяет выигрышные комбинации
		// на полное совпадение символа одного из игроков
		if (
			board[WINNING_ROWS[row][0]] != EMPTY &&
			board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]] &&
			board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]
		) {
			// возвращает символ игрока-победителя
			return board[WINNING_ROWS[row][0]];
		}
	}

	// cчитает незаполненные клетки на поле. 0 = ничья
	if (count(board.begin(), board.end(), EMPTY) == 0) {
		return TIE;
	}

	// если победитель ещё не определился
	return NO_ONE;
}

/// <summary>
/// Проверяет правильность сделанного хода
/// </summary>
/// <param name="move">Сделанный ход</param>
/// <param name="board">Игровое поле</param>
/// <returns></returns>
inline bool isLegal(const vector<char>& board, int move) {
	return board[move] == EMPTY;
}

/// <summary>
/// Обрабатывает ход игрока
/// </summary>
/// <param name="board">Игровое поле</param>
/// <param name="human">Символ игрока-человека</param>
/// <returns></returns>
int humanMove(const vector<char>& board, char human) {
	int move = askNumber("Where will you move?", board.size() - 1);

	while (!isLegal(board, move)) {
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", board.size() - 1);
	}

	cout << "Fine...\n";

	return move;
}

/// <summary>
/// Обрабатывает ход компьютера
/// </summary>
/// <param name="board">Игровое поле</param>
/// <param name="computer">Символ игрока-компьютера</param>
/// <returns></returns>
int computerMove(vector<char> board, char computer) {
	unsigned int move = 0;
	bool found = false;
	
	// проверяет возможность игрока-компьютера победить в 1 ход
	while (!found && move < board.size()) {
		if (isLegal(board, move)) {
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}

		if (!found) {
			++move;
		}
	}

	// если победный ход игрока-компьютера не найден
	// проверяет необходимость блокировать победный ход игрока-человека
	if (!found) {
		move = 0;
		char human = opponent(computer);

		while (!found && move < board.size()) {
			if (isLegal(board, move)) {
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}

			if (!found) {
				++move;
			}
		}
	}

	if (!found) {
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

		while (!found && i < board.size()) {
			move = BEST_MOVES[i];
			if (isLegal(board, move)) {
				found = true;
			}
			++i;
		}
	}

	cout << "I shall take square number " << move << endl;

	return move;
}

/// <summary>
/// Определяет победителя игры
/// </summary>
/// <param name="winner">Символ победителя</param>
/// <param name="computer">Символ игрока-компьютера</param>
/// <param name="human">Символ игрока-человека</param>
void announceWinner(char winner, char computer, char human) {
	if (winner == computer) {
		cout << winner << "`s won!\n";

	}
	else if (winner == human) {
		cout << winner << "`s won!\n";
		cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else {
		cout << "It's a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate... for this is the best you will ever achive.\n";
	}
}
