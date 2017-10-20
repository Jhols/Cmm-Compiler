#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "analex.h"

#define QTD_LEXEMA 100
#define QTD_DIGITO 100

//variável global - contador de vezes que o ENTER foi pressionado
int qtd_linhas = 1;

//Função que realiza a cópia dos valores dos sinais no Token
token copiaTokenSinal(char* sinal) {
  token t;
  int i = 0;
  while (i<QTD_SINAIS && strcmp(sinal, sinais[i].lexema) != 0) i++;

  strcpy(t.categoria, categorias[1]);
  strcpy(t.sinal, sinais[i].sinal);
  strcpy(t.lexema, sinais[i].lexema);

  return t;
}

void transicao_sinais(int *estado, char *lexema, int *l, char c, FILE *FD) {
  switch (*estado) {
    case 1:
      *estado = 2;
      break;
    case 4:
      *estado = 6;
      break;
    case 7:
      *estado = 8;
      break;
    case 9:
      *estado = 10;
      break;
    case 12:
      *estado = 13;
      break;
    case 15:
      *estado = 17;
      break;
    case 18:
      *estado = 19;
      break;
    case 25:
      *estado = 26;
      lexema[*l] = c;
      *l = *l + 1;
      break;
    case 28:
      *estado = 29;
      lexema[*l] = c;
      *l = *l + 1;
      break;
    case 29:
      *estado = 29;
      lexema[*l] = c;
      *l = *l + 1;
      break;
    case 33:
      *estado = 33;
      break;
    case 34:
      *estado = 33;
      lexema[*l] = c;
      *l = *l + 1;
      break;
  }
}

token analex(FILE *FD) {
  int estado = 0, l = 0, d = 0, i = 0;
  char c, lexema[QTD_LEXEMA], digito[QTD_DIGITO];
  token t;

  //loop principal
  while(1) {
    c = fgetc(FD); //Lê um caractere

    if (feof(FD)) { //Verificar se o arquivo está vazio ou chegou ao fim
      if (!estado) {
        strcpy(t.categoria, categorias[7]);
        strcpy(t.lexema, "EOF");
        t.codigo = 0;
        return t;
      }
      else {
        printf("-- Erro na linha: %d --\n", qtd_linhas);
        getchar();
        exit(1);
      }
    }

    if (isalpha(c)) { //verifica se o caracter lido é uma letra
      switch (estado) {
        case 0:
          estado = 1;
          lexema[l++] = c;
          break;
        case 1:
          estado = 1;
          lexema[l++] = c;
          break;
        case 4:
          estado = 6;
          break;
        case 7:
          estado = 8;
          break;
        case 9:
          estado = 10;
          break;
        case 12:
          estado = 13;
          break;
        case 15:
          estado = 17;
          break;
        case 18:
          estado = 19;
          break;
        case 25:
          estado = 26;
          lexema[l++] = c;
          break;
        case 28:
          estado = 29;
          lexema[l++] = c;
          break;
        case 29:
          estado = 29;
          lexema[l++] = c;
          break;
        case 31:
          estado = 32;
          break;
        case 33:
          estado = 33;
          break;
        case 34:
          estado = 33;
          break;
        case 36:
          switch (c) {
            case 'n':
              estado = 38;
              strcpy(t.categoria, categorias[6]);
              lexema[l++] = '\\';
              lexema[l++] = c;
              strcpy(t.lexema, lexema);
              return t;
            case 't':
              estado = 39;
              strcpy(t.categoria, categorias[6]);
              lexema[l++] = '\\';
              lexema[l++] = c;
              strcpy(t.lexema, lexema);
              return t;
            case 'r':
              estado = 40;
              strcpy(t.categoria, categorias[6]);
              lexema[l++] = '\\';
              lexema[l++] = c;
              strcpy(t.lexema, lexema);
              return t;
          }
        case 43: //caracteres '\n', '\t' e '\r' no estado de aspas
          switch (c) {
            case 'n':
            case 't':
            case 'r':
              estado = 29;
              [l++] = '\\';
              lexema[l++] = c;
              break;
          }
        case 44: //caracteres '\n', '\t' e '\r' no estado de aspostofo
          switch (c) {
            case 'n':
            case 't':
            case 'r':
              estado = 26;
              lexema[l++] = '\\';
              lexema[l++] = c;
              break;
          }
      }
    }

    else if (c == '_') {
      switch (estado) {
        case 1:
          estado = 1;
          lexema[l++] = c;
          break;
        case 18:
          estado = 19;
          break;
        case 25:
          estado = 26;
          lexema[l++] = c;
          break;
        case 28:
          estado = 29;
          lexema[l++] = c;
          break;
        case 29:
          estado = 29;
          lexema[l++] = c;
          break;
        case 33:
          estado = 33;
          break;
        case 34:
          estado = 33;
          break;
      }
    }

    else if (isdigit(c)) { //verifica se o caracter lido é um dígito
      switch (estado) {
        case 0:
          estado = 4;
          digito[d++] = c;
          break;
        case 1:
          estado = 1;
          lexema[l++] = c;
          break;
        case 4:
          estado = 4;
          digito[d++] = c;
          break;
        case 5:
          estado = 7;
          digito[d++] = c;
          break;
        case 7:
          estado = 7;
          digito[d++] = c;
          break;
        case 9:
          estado = 10;
          break;
        case 12:
          estado = 13;
          break;
        case 15:
          estado = 17;
          break;
        case 25:
          estado = 26;
          lexema[l++] = c;
          break;
        case 28:
          estado = 29;
          lexema[l++] = c;
          break;
        case 29:
          estado = 29;
          lexema[l++] = c;
          break;
        case 33:
          estado = 33;
          break;
        case 34:
          estado = 33;
          break;
        case 36:
          switch (c) {
            case '0':
              estado = 45;
              strcpy(t.categoria, categorias[6]);
              lexema[l++] = '\\';
              lexema[l++] = c;
              strcpy(t.lexema, lexema);
              return t;
          }
        case 43:
          if (c == '0') { //caracter barra-zero no estado de aspas
            estado = 29;
            lexema[l++] = '\\';
            lexema[l++] = c;
          }
          break;
        case 44:
          if (c == '0') { //caracter barra-zero no estado de aspostofo
            estado = 26;
            lexema[l++] = '\\';
            lexema[l++] = c;
          }
          break;
      }
    }

    else if (ehsinal(c)) { //verifica se o caracter lido é um sinal
      switch (c) {
        case ';':
          if (!estado) {
            t = copiaTokenSinal(";");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '+':
          if (!estado) {
            t = copiaTokenSinal("+");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '-':
          if (!estado) {
            t = copiaTokenSinal("-");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '*':
          if (!estado) {
            t = copiaTokenSinal("*");
            return t;
          }
          else if (estado == 31)
            estado = 33;
          else if (estado == 33)
            estado = 34;
          else if (estado == 34)
            estado = 33;
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '/':
          if (!estado)
            estado = 31;
          else if (estado == 34)
            estado = 0;
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '=':
          switch (estado) {
            case 0:
              estado = 9;
              lexema[l++] = c;
              break;
            case 9:
              t = copiaTokenSinal("==");
              estado = 11;
              return t;
            case 12:
              t = copiaTokenSinal("<=");
              estado = 14;
              return t;
            case 15:
              t = copiaTokenSinal(">=");
              estado = 16;
              return t;
            case 18:
              t = copiaTokenSinal("!=");
              estado = 20;
              return t;
            default:
              transicao_sinais(&estado, lexema, &l, c, FD);
          }
        break;

        case '.':
          switch (estado) {
            case 0:
              t = copiaTokenSinal(".");
              estado = 3;
              return t;
            case 4:
              estado = 5;
              digito[d++] = c;
              break;
            default:
              transicao_sinais(&estado, lexema, &l, c, FD);
          }
        break;

        case ',':
          if (!estado) {
            t = copiaTokenSinal(",");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '<':
          if (!estado) {
            estado = 12;
            lexema[l++] = c;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '>':
          if (!estado) {
            estado = 15;
            lexema[l++] = c;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '!':
          if (!estado) {
            estado = 18;
            lexema[l++] = c;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '&':
          if (!estado) {
            estado = 21;
            lexema[l++] = c;
          }
          else if (estado == 21) {
            t = copiaTokenSinal("&&");
            estado = 22;
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '|':
          if (!estado) {
            estado = 23;
            lexema[l++] = c;
          }
          else if (estado == 23) {
            t = copiaTokenSinal("||");
            estado = 24;
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '[':
          if (!estado) {
            t = copiaTokenSinal("[");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case ']':
          if (!estado) {
            t = copiaTokenSinal("]");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '{':
          if (!estado) {
            t = copiaTokenSinal("{");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '}':
          if (!estado) {
            t = copiaTokenSinal("}");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '(':
          if (!estado) {
            t = copiaTokenSinal("(");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case ')':
          if (!estado) {
            t = copiaTokenSinal(")");
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '\"':
          if (!estado) {
            estado = 28;
          }
          else if (estado == 28) {
            t = copiaTokenSinal("\"");
            estado = 30;
            return t;
          }
          else if (estado == 29) {
            estado = 30;
            i=0;
            while (i<qtd_literais && strcmp(lexema, literais[i]) != 0) i++;
            if (i<qtd_literais && strcmp(lexema, literais[i]) == 0) { //verifica se o lexema é um literal existente
              strcpy(t.categoria, categorias[5]);
              lexema[l] = '\0';
              strcpy(t.lexema, lexema);
              return t;
            }
            //criação de um novo literal
            strcpy(t.categoria, categorias[5]);
            lexema[l] = '\0';
            strcpy(t.lexema, lexema);

            strcpy(literais[qtd_literais], lexema); //armazena no vetor de literais o lexema para criar um novo literal
            qtd_literais++;
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '\'':
          if (!estado) {
            estado = 25;
          }
          else if (estado == 25) {
            t = copiaTokenSinal("\'");
            estado = 27;
            return t;
          }
          else if (estado == 26) { //retorna um caracter
            strcpy(t.categoria, categorias[6]);
            lexema[l++] = '\0';
            strcpy(t.lexema, lexema);

            estado = 27;
            return t;
          }
          else
            transicao_sinais(&estado, lexema, &l, c, FD);
        break;

        case '\\':
          if (!estado)
            estado = 36;
          else if (estado == 36) {
            t = copiaTokenSinal("\\");
            estado = 37;
            return t;
          }
          else if (estado == 28)
            estado = 43;
          else if (estado == 29) {
            estado = 43;
            lexema[l++] = c;
          }
          else if (estado == 43)
            estado = 29;
          else if (estado == 25)
            estado = 44;
          else if (estado == 26)
            estado = 44;
          else if (estado == 44)
            estado = 26;
      }
    }

    else if (isspace(c)) { //verifica se o caracter lido é um espaço em branco
      if (c == '\n') {
        if (estado == 0 || estado == 33 || estado == 34) {
          qtd_linhas++;
        }
      }
      if (!estado)
        estado = 0;
      else if (estado == 25)
        estado = 26;
      else if (estado == 28) {
        estado = 29;
        lexema[l++] = c;
      }
      else if (estado == 29) {
        estado = 29;
        lexema[l++] = c;
      }
      else if (estado == 31)
        estado = 32;
      else if (estado == 33)
        estado = 33;
      else if (estado == 34)
        estado = 33;
      else
      transicao_sinais(&estado, lexema, &l, c, FD);
    }

    //Estados de aceitação ainda não retornados
    switch (estado) {
      case 2: //Palavra Reservada ou Identificador
        lexema[l++] = '\0';
        i=0;

        while (i<QTD_PR && strcmp(lexema, PR[i]) != 0)  i++;

        if (i<QTD_PR && strcmp(lexema, PR[i]) == 0) { //verifica se o lexema é uma palavra reservada
          strcpy(t.categoria, categorias[0]);
          strcpy(t.lexema, lexema);
          ungetc(c, FD);
          return t;
        }

        i=0;
        while (i<qtd_ID && strcmp(lexema, ID[i]) != 0) i++;
        if (i<qtd_ID && strcmp(lexema, ID[i]) == 0) { //verifica se o lexema é um ID existente
          strcpy(t.categoria, categorias[2]);
          lexema[l++] = '\0';
          strcpy(t.lexema, lexema);
          ungetc(c, FD);
          return t;
        }

        //criação de um novo ID
        strcpy(t.categoria, categorias[2]);
        lexema[l++] = '\0';
        strcpy(t.lexema, lexema);

        strcpy(ID[qtd_ID], lexema); //armazena no vetor de IDs o lexema para criar um novo ID
        qtd_ID++;
        ungetc(c,FD);
        return t;

      case 6: //Constante Inteira
        digito[d++] = '\0';
        strcpy(t.categoria, categorias[3]);
        strcpy(t.lexema, digito);
        t.valor_int = atoi(digito);
        ungetc(c,FD);
        return t;

      case 8: //Constante Real
        digito[d++] = '\0';
        strcpy(t.categoria, categorias[4]);
        strcpy(t.lexema, digito);
        t.valor_float = atof(digito);
        ungetc(c,FD);
        return t;

      case 10: //Sinal =
        t = copiaTokenSinal("=");
        ungetc(c,FD);
        return t;

      case 13: //Sinal <
        t = copiaTokenSinal("<");
        ungetc(c,FD);
        return t;

      case 17: //Sinal >
        t = copiaTokenSinal(">");
        ungetc(c,FD);
        return t;

      case 19: //Sinal !
        t = copiaTokenSinal("!");
        ungetc(c,FD);
        return t;

      case 32: //Sinal /
        t = copiaTokenSinal("/");
        ungetc(c,FD);
        return t;

      /*case 33:
        strcpy(t.categoria, "COMENT");
        strcpy(t.lexema, lexema);
        ungetc(c,FD);
        break;*/

    }

  } //fim do loop

}

int main() {

  FILE *FD;
  int c, i=0;
  token t;

  FD = fopen("querover.c", "r");

  if (FD == NULL) { //teste de abertura do arquivo
   printf ("Houve um erro ao abrir o arquivo.\n");
   return 1;
  }

  while(1) {
    t = analex(FD);

    printf("< %s, %s >\n", t.categoria, t.lexema);

    if (strcmp(t.categoria, "FIM_ARQUIVO") == 0)
      break;
  }

  fclose(FD);
  return 0;
}
