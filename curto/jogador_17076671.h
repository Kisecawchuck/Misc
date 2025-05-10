typedef enum {
	Quatro,
	Cinco,
	Seis,
	Sete,
	Q,
	J,
	K,
	As,
	Dois,
	Tres
} Valor;

typedef enum {
	O,
	E,
	C,
	P
} Naipe;

typedef struct {
    Valor valor;
    Naipe naipe;
} Carta;
