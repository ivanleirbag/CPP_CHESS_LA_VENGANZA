#include <ncurses.h>
#include <iostream>
#include <string.h>

int i, j, k, l, key;
int posx = 0;
int posy = 0;
bool menu = true;
bool jugando = false;
bool mostrar_mov = false;

struct Pieza{
    int x;
    int y;
    bool seleccionada = false;
    char figura;
};

int main(){
   
    //---------------- inicializacion de ncurses----------------//
    //-------------- e inicializacion de la pieza-------------//
    initscr();
    keypad(stdscr, TRUE);
    Pieza pieza; 
        pieza.x = 9; 
        pieza.y = 9;

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
        switch (key){
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

                    //--------Dibujado del selector-------//
                    if(posy == i/3 && posx == j && (i%3 == 0 || (i+1)%3 == 0)/*Chequea que el selector esté en la primer o última fila*/){
                        if (mostrar_mov){
                            printw(" $ $ ");
                        }else{
                            printw(" = = ");
                        }
                    //--------Chequea si la pieza está en el centro del casillero-------//
                    //-----------------------y dibujado de la pieza---------------------//   
                    }else if(pieza.seleccionada && pieza.x == j && pieza.y == i/3){   
                        printw("  %c  ", pieza.figura);
                    }else if(mostrar_mov && (i-1)%3 == 0){
                        switch(pieza.figura){
                            //-----------Dibujado de los movimientos del alfil-----------//
                            case 'A':
                                if((pieza.x-j==pieza.y-i/3)||((i/3)+j == pieza.x+pieza.y)){
                                    printw("  0  ");
                                }else{
                                    printw("     ");
                                }
                            break;
                            //-----------Dibujado de los movimientos de la torre-----------//
                            case 'T':
                                if(pieza.y == i/3 || pieza.x == j){
                                    printw("  0  ");
                                }else{
                                    printw("     ");
                                }
                                break;
                            //-----------Dibujado de los movimientos de la reina-----------//
                            case 'R':
                                if(pieza.y == i/3 || pieza.x == j || (pieza.x-j==pieza.y-i/3)||((i/3)+j == pieza.x+pieza.y)){
                                    printw("  0  ");
                                }else{
                                    printw("     ");
                                }
                                break;
                            default:
                             break;
                        }
                    }else{
                        printw("     ");
                    }
                    
                }       
                printw("\n");
            }



            //---------------- INPUT en el juego----------------//
            key = getch();
            clear();
            switch (key){
            //Cerrar el menu o juego
            case 27:
                if(pieza.seleccionada)
                {
                    pieza.seleccionada = false;
                    mostrar_mov = false;
                }else{
                    endwin();
                    jugando = false;
                    menu = false;
                }
                break;
            //ENTER input
            case 10:
                if(pieza.seleccionada){
                    mostrar_mov = !mostrar_mov;
                }
                break;
            case 65: case 97:
                pieza.seleccionada = true;
                pieza.figura = 'A';
                pieza.x = posx;
                pieza.y = posy;
                break;
            case 82: case 114:
                pieza.seleccionada = true;
                pieza.figura = 'R';
                pieza.x = posx;
                pieza.y = posy;
                break;
            case 84: case 116:
                pieza.seleccionada = true;
                pieza.figura = 'T';
                pieza.x = posx;
                pieza.y = posy;
                break;
            //FLECHAS input
            case KEY_LEFT:
                if (posx > 0){posx -= 1; pieza.x = posx;}
                break;
            case KEY_RIGHT:
                if (posx<7){posx += 1; pieza.x = posx;}
                break;
            case KEY_UP:
                if (posy > 0){posy -= 1; pieza.y = posy;}
                break;
            case KEY_DOWN:
                if (posy<7){posy += 1; pieza.y = posy;}
                break;
            default:
                mostrar_mov = false;
                break;
            }
        }
    }   

    endwin();
    return 0;
}