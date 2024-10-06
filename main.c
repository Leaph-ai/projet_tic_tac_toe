#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// afficher le tableau
void printchart(char chart[5][9]) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%c", chart[i][j]);
    }
    printf("\n");
  }
}

int victory(char simplchart[9]) {
  // lignes
  if (simplchart[0] == 'X' && simplchart[1] == 'X' && simplchart[2] == 'X') return 1;
  if (simplchart[3] == 'X' && simplchart[4] == 'X' && simplchart[5] == 'X') return 1;
  if (simplchart[6] == 'X' && simplchart[7] == 'X' && simplchart[8] == 'X') return 1;

  // colonnes
  if (simplchart[0] == 'X' && simplchart[3] == 'X' && simplchart[6] == 'X') return 1;
  if (simplchart[1] == 'X' && simplchart[4] == 'X' && simplchart[7] == 'X') return 1;
  if (simplchart[2] == 'X' && simplchart[5] == 'X' && simplchart[8] == 'X') return 1;

  // diagonales
  if (simplchart[0] == 'X' && simplchart[4] == 'X' && simplchart[8] == 'X') return 1;
  if (simplchart[2] == 'X' && simplchart[4] == 'X' && simplchart[6] == 'X') return 1;

  return 0;
}

int defeat(char simplchart[9]) {
  if (simplchart[0] == 'O' && simplchart[1] == 'O' && simplchart[2] == 'O') return 1;
  if (simplchart[3] == 'O' && simplchart[4] == 'O' && simplchart[5] == 'O') return 1;
  if (simplchart[6] == 'O' && simplchart[7] == 'O' && simplchart[8] == 'O') return 1;

  if (simplchart[0] == 'O' && simplchart[3] == 'O' && simplchart[6] == 'O') return 1;
  if (simplchart[1] == 'O' && simplchart[4] == 'O' && simplchart[7] == 'O') return 1;
  if (simplchart[2] == 'O' && simplchart[5] == 'O' && simplchart[8] == 'O') return 1;

  if (simplchart[0] == 'O' && simplchart[4] == 'O' && simplchart[8] == 'O') return 1;
  if (simplchart[2] == 'O' && simplchart[4] == 'O' && simplchart[6] == 'O') return 1;

  return 0;
}

int draw(char simplchart[9]) {
  for (int i = 0; i < 9; i++) {
    if (simplchart[i] == ' ') {
      return 0;
    }
  }
  return 1;
}

//prendre le milieu si il n'est pas pris, faire un nombre aléatoire tant que la position !=  ' '
void robotmove(char simplchart[9]) {
  int position;
  if (simplchart[4] == ' ') {
    simplchart[4] = 'O';
  } 
  else {
    do {
      position = rand() % 9;  
    } 
    while (simplchart[position] != ' '); 

    simplchart[position] = 'O';
  }
}

int main() {
  int position;
  int end = 0;

  srand(time(0));

  char simplchart[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

  char chart[5][9] = {
      {simplchart[0], ' ', '|', ' ', simplchart[1], ' ', '|', ' ', simplchart[2]},
      {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
      {simplchart[3], ' ', '|', ' ', simplchart[4], ' ', '|', ' ', simplchart[5]},
      {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
      {simplchart[6], ' ', '|', ' ', simplchart[7], ' ', '|', ' ', simplchart[8]}
  };

  printchart(chart);

  while (end != 1) {
    printf("Choisissez où jouer :\n");
    scanf("%d", &position);

    // position entre 0 et 8 et n'est pas égale a ' '
    if (position < 0 || position > 8 || simplchart[position] != ' ') {
      printf("Mauvaise position, entrez en une nouvelle : \n");
      continue;
    }

    simplchart[position] = 'X';

    // faire correspondre le tableau chart avec simplifié chart
    chart[0][0] = simplchart[0]; chart[0][4] = simplchart[1]; chart[0][8] = simplchart[2];
    chart[2][0] = simplchart[3]; chart[2][4] = simplchart[4]; chart[2][8] = simplchart[5];
    chart[4][0] = simplchart[6]; chart[4][4] = simplchart[7]; chart[4][8] = simplchart[8];

    printchart(chart);

    if (victory(simplchart)) {
      printf("C'est gagné !\n");
      end = 1;
      break;
    }

    if (draw(simplchart)) {
     printf("Match nul !\n");
     end = 1;
     break;
    }

    printf("\n");
    robotmove(simplchart);

    chart[0][0] = simplchart[0]; chart[0][4] = simplchart[1]; chart[0][8] = simplchart[2];
    chart[2][0] = simplchart[3]; chart[2][4] = simplchart[4]; chart[2][8] = simplchart[5];
    chart[4][0] = simplchart[6]; chart[4][4] = simplchart[7]; chart[4][8] = simplchart[8];

    printchart(chart);

    if (defeat(simplchart)) {
      printf("C'est perdu !\n");
      end = 1;
      break;
    }

    if (draw(simplchart)) {
      printf("Match nul !\n");
      end = 1;
      break;
    }
  }

  return 0;
}
