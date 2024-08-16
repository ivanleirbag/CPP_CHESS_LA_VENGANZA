#include <ncurses.h>
#include <iostream>
#include <string.h>

int i, j, k, l, key;
int posx = 0;
int posy = 0;
bool menu = true;
bool jugando = false;

struct Pieza{
    int x;
    int y;
    bool seleccionada = false;
    char figura;
};

int main(){
    //---------------- inicializacion de ncurses----------------//
    //-------------- e inicializacion de las piezas-------------//
    initscr();
    keypad(stdscr, TRUE);
    Pieza torre; 
        torre.x = 0; 
        torre.y = 0;
        torre.figura = 'T';
    Pieza alfil; 
        alfil.x = 1;
        alfil.y = 1;
        alfil.figura = 'A';
    Pieza reina; 
        reina.x = 1;
        reina.y = 2;
        reina.figura = 'R';

    //---------------- Bucle menú de inicio----------------//
    while (menu){

        //---------------- Renderizado del menú de inicio----------------//
        attroff(A_REVERSE);
        curs_set(0);
        clear();
        printw("> Presiona [ENTER] para comenzar a jugar.\n\n");
        printw("> Presiona [ESC] para cerrar el programa.");
        refresh();

        //---------------- INPUT menú de inicio----------------//
        key = getch();
        switch (key)
        {
        case 27:
            endwin();
            menu = false;
            break;
        case 10:
            jugando = true;
            clear();
            break;
        default:
            break;
        }
        //---------------- bucle del juego----------------//
        while (jugando){

            //----------------Renderizado del tablero----------------//
            move(0,0);
            for (i = 0; i<24; i++){
                for (j=0; j<8; j++){
                    attroff(A_REVERSE);
                    if((i/3+j)%2){
                        attron(A_REVERSE);
                    }
                    printw("       ");    
                }
                printw("\n");
            }
            attroff(A_REVERSE);


            //---------------- INPUT en el juego----------------//
            key = getch();
            switch (key)
            {
            case 27:
                endwin();
                jugando = false;
                menu = false;
                break;
            case 10:
                jugando = true;
                clear();
                break;
            default:
                break;
            }
        }
    }   

    endwin();
    return 0;
}