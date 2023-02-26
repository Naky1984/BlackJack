// HolaMundo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<time.h>
using namespace std;
//Nombre de jugador que será dado por el usuario y nombre del empleado.
string player;
string crupier = "Roberto";
char plantarse;
char pedirCarta;
//Creación de mis arrays, que serán un total de 4 palos x 13 cartas en cada palo
string cartas[4][13] = { {"A","2","3","4","5","6","7","8","9","10","J","Q","K"},
						 {"A","2","3","4","5","6","7","8","9","10","J","Q","K"},
						 {"A","2","3","4","5","6","7","8","9","10","J","Q","K"},
						 {"A","2","3","4","5","6","7","8","9","10","J","Q","K"} };

string nombresPalos[4] = { "Corazones","Diamantes","Treboles","Picas" };

bool cartasRepetidas[4][13] = { false };


int cardsRandom = 0;
int palosRandom = 0;
int playerPoints = 0;
int homePoints = 0;
int cardValue = 0;
//booleanos de victoria o derrota de los jugadores

bool winPlayer = false;
bool winHome = false;

//La intro del juego con saludo incial, donde se presenta el empleado y, introduces nombre del jugador
// Funcion que luego pasaremos al main
void casinoStart() {
	cout << "Hola! soy " << crupier << " Bienvenido a casino Barcelona.En la noche de hoy, sere su crupier." << endl;
	cout << "Si es tan amable me puede decir su nombre?" << endl;
	cout << "Introduce el nombre del jugador: " << endl;
	cin >> player;
	cout << "Encantando " << player << " Le deseo buena suerte. Cuando quiera podemos empezar" << endl;
}

//Repartir cartas 
// int puntosJugador hace referencia a playerPoints 
// int puntosCasa hace referencia a homePoints
// cartasRepetidas es un array de boleanos inicializados en false, si pasan a true es que esa carta esta repartida y ya no vuelve a salir
// Boleanos pasados por referencia para indicar la victoria de player o de crupier.
void repartirCartaADosJugadores(int& puntosJugador, int& puntosCasa, bool& jugador, bool& casa, string nameJugador, string nameCasa, char plantarseJugador, bool(&cartasRepetidas)[4][13]) {
	cartasRepetidas[cardsRandom][palosRandom] = false;
	cout << "Se reparten dos cartas a  jugador y una a crupier..." << endl;
	cout << "Cartas de " << nameJugador << ": ";
	jugador = false;
	casa = false;
	for (int i = 0; i < 2; i++) { // Hago un for para que reparta dos cartas a player aleatoriamente
		cardsRandom = rand() % 13;
		palosRandom = rand() % 4;
		if (!cartasRepetidas[cardsRandom][palosRandom]) {
			cartasRepetidas[cardsRandom][palosRandom] = true;
			if ((nameJugador == player && puntosJugador == 21)) // si player tiene 21 puntos gana
			{
				cout << "Genial! has ganado. Tienes un BlackJack " << nameJugador << endl;
				jugador = true;
			}
			else if ((nameJugador == player && puntosJugador > 21)) // si player supera los 21 puntos pierde
			{

				cout << "Lo siento, te has pasado de 21 puntos. El croupier gana automaticamente. " << nameJugador << endl;
				jugador = true;
			}
			if (cardsRandom == 0 && nameJugador == player) {
				do
				{
					cout << "Que quieres que valga la carta? un 1 o un 11?:" << endl;
					cin >> cardValue;
					switch (cardValue)
					{
					case 1: cardValue = 1; break;
					case 11: cardValue = 11; break;
					default:
						cout << "Esa no es una opcion" << endl;break;
					}
				} while (cardValue != 1 && cardValue != 11);

			}
			else if (cardsRandom > 9) {
				cardValue = 10;

			}
			else {
				cardValue = cardsRandom + 1;

			}
			puntosJugador = puntosJugador + cardValue;
			cout << nameJugador << " Ha recibido esta carta: " << cartas[palosRandom][cardsRandom] << " de " << nombresPalos[palosRandom] << " y tienes un total de: " << puntosJugador << endl;

		}

	}
	if (nameCasa == crupier) {
		cardsRandom = rand() % 13;
		palosRandom = rand() % 4;
		if (!cartasRepetidas[cardsRandom][palosRandom]) {
			cartasRepetidas[cardsRandom][palosRandom] = true;
			cardValue = 0;
			if ((puntosCasa + 11) > 21)
			{
				cardValue = 1;
			}
			else
			{
				cardValue = 11;
			}if (cardsRandom > 9) {
				cardValue = 10;
			}
			else {
				cardValue = cardsRandom + 1;
			}
			puntosCasa = puntosCasa + cardValue;
			cout << nameCasa << " Ha recibido esta carta: " << cartas[palosRandom][cardsRandom] << " de " << nombresPalos[palosRandom] << " y tiene un total de: " << puntosCasa << endl;

			if ((nameCasa == crupier && puntosCasa == 21)) // si crupier tiene 21 puntos gana
			{
				cout << "La casa gana! " << nameCasa << endl;
				casa = true;
			}
			else if ((nameCasa == crupier && puntosCasa > 21)) // si crupier supera los 21 puntos pierde
			{

				cout << "El croupier se ha pasado de 21 puntos. Felicitaciones, has ganado! " << endl;
				casa = true;
			}
		}

	}

	if ((puntosJugador < 21 && !jugador) && (puntosCasa < 21 && !casa)) {
		jugador = false;
		casa = false;
		cout << "Quieres plantarte? s? n?" << endl; // si no los supera o iguala, sigue jugando. Tambien decide si quiere plantarse.
		cin >> plantarseJugador;
		switch (plantarseJugador)
		{
		case 's':
			cout << "Turno del crupier" << endl;  // si es sí, el crupier tiene la oportunidad de ganar.
			jugador = true;
			if (puntosCasa < 21 && plantarseJugador == 's')
			{
				cardsRandom = rand() % 13;
				palosRandom = rand() % 4;

				if (!cartasRepetidas[cardsRandom][palosRandom])
				{
					puntosCasa = puntosCasa + cardValue;
					cartasRepetidas[cardsRandom][palosRandom] = true;

					if (puntosCasa == 21) {
						cout << "La casa gana! Vuelva a jugar otro dia " << endl;
					}
					else if (puntosCasa > 21) {
						cout << "La casa se ha pasado de 21 puntos. Felicidades, has ganado! " << endl;
						casa = true;
					}
					else if (puntosJugador > puntosCasa) { // si los puntos del jugador es mayor que los de crupier, gana jugador.
						cout << "Gana " << nameJugador << endl;
						casa = true;
					}
					else if (puntosJugador < puntosCasa) { // si los puntos del jugador es menor que los de crupier, gana crupier. 
						cout << "Gana " << nameCasa << endl;
						casa = true;
					}
					if ((puntosCasa + 11) > 21)
					{
						cardValue = 1;
					}
					else
					{
						cardValue = 11;
					}if (cardsRandom > 9) {
						cardValue = 10;
					}
					else {
						cardValue = cardsRandom + 1;
					}
					puntosCasa = puntosCasa + cardValue;
					cout << nameCasa << " Ha recibido esta carta: " << cartas[palosRandom][cardsRandom] << " de " << nombresPalos[palosRandom] << " y tiene un total de: " << puntosCasa << endl;
				}


			}
			break;
		case 'n':
			pedirCarta = 's';
			while (!jugador && pedirCarta == 's') {
				cout << "Quieres pedir carta? s/n" << endl;
				cin >> pedirCarta;

				if ((nameJugador == player && puntosJugador == 21)) // si player tiene 21 puntos gana
				{
					cout << "Genial! has ganado. Tienes un BlackJack " << nameJugador << endl;
					jugador = true;
				}
				else if ((nameJugador == player && puntosJugador > 21)) // si player supera los 21 puntos pierde
				{

					cout << "Lo siento, te has pasado de 21 puntos. El croupier gana automaticamente. " << nameJugador << endl;
					jugador = true;
				}

				if (cardsRandom == 0 && nameJugador == player)
				{
					do
					{
						cout << "Que quieres que valga la carta? un 1 o un 11?:" << endl;
						cin >> cardValue;
						switch (cardValue)
						{
						case 1: cardValue = 1; break;
						case 11: cardValue = 11; break;
						default:
							cout << "Esa no es una opcion" << endl;break;
						}
					} while (cardValue != 1 && cardValue != 11);
				}
				else if (cardsRandom > 9) {
					cardValue = 10;
				}
				else {
					cardValue = cardsRandom + 1;
				}
				puntosJugador = puntosJugador + cardValue;
				cout << nameJugador << " Ha recibido esta carta: " << cartas[palosRandom][cardsRandom] << " de " << nombresPalos[palosRandom] << " y tienes un total de: " << puntosJugador << endl;

			}
			if (!jugador)
			{
				cout << "Te plantas con esta puntuacion: " << puntosJugador << endl;
				jugador = true;
				if ((nameJugador == player && puntosJugador == 21)) // si player tiene 21 puntos gana
				{
					cout << "Genial! has ganado. Tienes un BlackJack " << nameJugador << endl;
					jugador = true;
				}
				else if ((nameJugador == player && puntosJugador > 21)) // si player supera los 21 puntos pierde
				{

					cout << "Lo siento, te has pasado de 21 puntos. El croupier gana automaticamente. " << nameJugador << endl;
					jugador = true;
				}
			}
			jugador = true;
			break;
		default:
			cout << "Esa no es una opcion" << endl;
			break;
		}
	}

	if ((nameCasa == crupier && puntosCasa == 21)) // si crupier tiene 21 puntos gana
	{
		cout << "La casa gana! " << nameCasa << endl;
		casa = true;
	}
	else if ((nameCasa == crupier && puntosCasa > 21)) // si crupier supera los 21 puntos pierde
	{

		cout << "El croupier se ha pasado de 21 puntos. Felicitaciones, has ganado! " << endl;
		casa = true;
	}
	else {
		casa = false; // si no los super o iguala sigue jugando
	}
	if (puntosJugador == 21 && puntosCasa == 21) // comparar con los puntos del jugador y si estan igual de puntos hay empate
	{
		cout << "Empate" << endl;
		casa = true;
	}
}

int main()
{
	srand(time(0));
	casinoStart();
	repartirCartaADosJugadores(playerPoints, homePoints, winPlayer, winHome, player, crupier, plantarse, cartasRepetidas);


}