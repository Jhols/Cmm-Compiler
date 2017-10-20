#define QTD_SINAIS sizeof(sinais)/sizeof(token)+1
#define QTD_PR sizeof(PR)/sizeof(char*)
#define QTD_CATEGORIAS sizeof(categorias)/sizeof(char*)

typedef struct token {
  char categoria[30];
  char lexema[30];
  char sinal[30];
  int codigo;
  int valor_int;
  float valor_float;
} token;

                    // 0     1     2      3        4       5       6          7
char *categorias[] = {"PR", "SN", "ID", "CT_I", "CT_R", "CT_LT", "CT_C", "FIM_ARQUIVO"};

// Conjunto de sinais e operadores da linguagem
token sinais[] = { {"SN", "+", "mais"}, {"SN", "-", "menos"}, {"SN", "*", "asterisco"},
                   {"SN", "/", "barra"}, {"SN", "=", "igual"}, {"SN", "<", "menor"},
                   {"SN", ">", "maior"}, {"SN", "<=", "menor_igual"}, {"SN", ">=", "maior_igual"},
                   {"SN", "(", "abre_par"}, {"SN", ")", "fecha_par"}, {"SN", "{", "abre_chaves"},
                   {"SN", "}", "fecha_chaves"}, {"SN", "[", "abre_colchetes"}, {"SN", "]", "fecha_colchetes"},
                   {"SN", "&&", "e_logico"}, {"SN", "||", "ou_logico"}, {"SN", "!", "nao_logico"},
                   {"SN", "!=", "nao_igual"}, {"SN", "\'", "apostofo"}, {"SN", "\"", "aspas"},
                   {"SN", ";", "ponto_virgula"}, {"SN", ".", "ponto"}, {"SN", ",", "virgula"}, {"SN", "\\", "contra-barra"}
                };

// Conjunto de Palavras Reservadas da linguagem Cmm
char *PR[] = {
  "semretorno", "caracter", "inteiro", "real", "booleano", "semparam", "se", "senao", "enquanto", "para", "retorne", "principal"
};

char ID[100][100];
int qtd_ID = 0;

char literais[100][100];
int qtd_literais = 0;

//Lê um caracter e retorna 1 caso seja um sinal da linguagem e 0 (zero), caso contrário
int ehsinal(char c) {
  int i = 0;

  while (i < QTD_SINAIS) {
    if (c == sinais[i].lexema[0])
      return 1;
    i++;
  }

  return 0;
}
