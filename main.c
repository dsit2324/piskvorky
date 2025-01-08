#include <stdio.h>

// konstanta pro velikost herni desky
#define SIZE 10
#define WINNER 5

// vytvoreni prazdne herni desky, pouzijeme char protoze chceme znaky a ne cisla
void createBoard(char board[SIZE][SIZE]) {
    printf("  Vitej v me hre na piskvorky. \n"
           "---------------------------------\n"
           "  cilem je spojit %d pole\n"
           "     (hor, ver nebo dia)\n", WINNER);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' '; // vyprazdeni jednotlivych policek
        }
    }
}

// vypis herni desky
void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    printf("   ");
    for (int j = 0; j < SIZE; j++) {
        printf(" |%2d", j + 1); // cisla sloupcu
    }
    printf(" |");
    printf("\n    +---");
    for (int y = 0; y < SIZE - 1; y++) {
        printf("+---");
    }
    printf("+\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" %2d ", i + 1); // cisla radku
        for (int j = 0; j < SIZE; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n"); // pipeline je zde jako vertikalni ohraniceni
        printf("    +---");
        for (int y = 0; y < SIZE - 1; y++) {
            printf("+---");
        }
        printf("+\n");
    }
    printf("\n \n");
}

// funkce pro kontrolovani, jestli nekdo vyhral
int checkWinner(char board[SIZE][SIZE]) {
    // kontrola radku
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE - WINNER; j++) {
            int count = 1;
            for (int k = 1; k < WINNER; k++) {
                if (board[i][j] != ' ' && board[i][j] == board[i][j + k]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == WINNER) return 1;
        }
    }

    // kontrola vertikalnich vyher
    for (int i = 0; i <= SIZE - WINNER; i++) {
        for (int j = 0; j < SIZE; j++) {
            int count = 1;
            for (int k = 1; k < WINNER; k++) {
                if (board[i][j] != ' ' && board[i][j] == board[i + k][j]) {
                    count++;
                } else {
                    break ;
                }
            }
            if (count == WINNER) return 1;
        }
    }

    // kontrola diagonal
    // prvni diagonala (zleva doprava)
    for (int i = 0; i <= SIZE - WINNER; i++) {
        for (int j = 0; j <= SIZE - WINNER; j++) {
            int count = 1;
            for (int k = 1; k < WINNER; k++) {
                if (board[i][j] != ' ' && board[i][j] == board[i + k][j + k]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == WINNER) return 1;
        }
    }

    // druhá diagonala (zprava doleva)
    for (int i = 0; i <= SIZE - WINNER; i++) {
        for (int j = WINNER - 1; j < SIZE; j++) {
            int count = 1;
            for (int k = 1; k < WINNER; k++) {
                if (board[i][j] != ' ' && board[i][j] == board[i + k][j - k]) {
                    count++;
                } else {
                    break;
                }
            }
            if (count == WINNER) return 1;
        }
    }

    return 0; // zadny vitez
}

// funkce pro zjisteni remizy
int checkDraw(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0; // jeste se muze hrat
            }
        }
    }
    return 1; // pokud je remiza, tak se vrati jednicka
}

int main() {
    if (WINNER > SIZE) {
        printf("Hra nelze spustit.\n");
        return 0;
    } else {
        char board[SIZE][SIZE];
        int row, col; // vytvoreni promenych pro radek a sloupec
        int turn = 1; // 1 pro hrace X, -1 pro hrace O
        int winner = 0; // promenna pro vyherce
        int cycle = 0;

        createBoard(board);

        while (cycle == 0) {
            printBoard(board);
            do {
                printf(" Hrac %c, zadejte radek (1-%d) a sloupec (1-%d): ", (turn == 1) ? 'X' : 'O', SIZE, SIZE);
                // ternarni operator pro zjisteni, kdo je na tahu

                scanf("%d %d", &row, &col);
                row = row - 1;  // upravime vstupy na indexy
                col = col - 1;  // upravime vstupy na indexy

                // jestli hrac nezadal souradnice mimo pole
                if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') {
                    printf("Neplatny tah, zkuste to znovu.\n");
                }
            } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ');

            // vypsani tahu na desku
            board[row][col] = (turn == 1) ? 'X' : 'O';

            // kontrolovani vyherce
            winner = checkWinner(board);
            if (winner == 1) {
                printBoard(board);
                printf("Hrac %c vyhral!\n", (turn == 1) ? 'X' : 'O');
                cycle = 1; //preruseni cyklu, kdyz nekdo vyhraje
            }

            // kontrolovani remizy
            if (checkDraw(board) == 1) {
                printBoard(board);
                printf("Remiza!\n");
                cycle = 1; //preruseni cyklu, kdyz bude remiza
            }

            // vymena kola
            turn = -turn;
        }


        return 0;
    }
}
