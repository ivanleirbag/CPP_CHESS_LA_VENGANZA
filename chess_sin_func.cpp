#include <ncurses.h>
#include <iostream>
#include <string.h>
#include <locale.h>


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
    setlocale(LC_ALL, ""); //Inicializo caracteres unicode   
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
                    //--------Dibujado del selector-------///*&& (i%3 == 0 || (i+1)%3 == 0)/*Chequea que el selector esté en la primer o última fila*/
                    if(posy == i/3 && posx == j&& (i%3 == 0 || (i+1)%3 == 0)){
                        if (mostrar_mov ){
                            if(i%3 == 0){
                                printw("▼   ▼");
                            }else if((i+1)%3 == 0){
                                printw("▲   ▲");
                            }
                        }else{
                            if(i%3 == 0){
                                printw("┌   ┐");
                            }else if((i+1)%3 == 0){
                                printw("└   ┘");
                            }    
                        }
                    //--------Chequea si la pieza está en el centro del casillero-------//
                    //-----------------------y dibujado de la pieza---------------------//   
                    }else if(pieza.seleccionada && pieza.x == j && pieza.y == i/3){   
                        switch (pieza.figura)
                        {
                        case 'A':
                            printw("  ♝  ");
                            break;
                        case 'T':
                            printw("  ♜  ");
                            break;
                        case 'R':
                            printw("  ♛  ");
                            break;
                        default:
                            break;
                        }
                    }else if(mostrar_mov && (i-1)%3 == 0){
                        switch(pieza.figura){
                        //-----------Dibujado de los movimientos del alfil-----------//
                        case 'A':
                            if((pieza.x-j==pieza.y-i/3)||((i/3)+j == pieza.x+pieza.y)){
                                printw("  ♦  ");
                            }else{
                                printw("     ");
                            }
                        break;
                        //-----------Dibujado de los movimientos de la torre-----------//
                        case 'T':
                            if(pieza.y == i/3 || pieza.x == j){
                                printw("  ♦  ");
                            }else{
                                printw("     ");
                            }
                            break;
                        //-----------Dibujado de los movimientos de la reina-----------//
                        case 'R':
                            if(pieza.y == i/3 || pieza.x == j || (pieza.x-j==pieza.y-i/3)||((i/3)+j == pieza.x+pieza.y)){
                                printw("  ♦  ");
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

            //-----------Dibujado de las instrucciones-----------//
            move(1, 45); printw("CONTROLES");
            move(2, 45); printw("───────────────────────────────────");
            if(mostrar_mov){
                move(4, 45);
                switch (pieza.figura)
                {
                case 'A':
                    printw("ALFIL SELECCIONADO { ♝ }");
                    break;
                case 'T':
                    printw("TORRE SELECCIONADA { ♜ }");
                    break;
                case 'R':
                    printw("REINA SELECCIONADA { ♛ }");
                    break;
                default:
                    break;
                }
                move(6, 45); printw("PRESIONE CUALQUIER TECLA");
                move(7, 45); printw("PARA DESELECCIONAR");
                move(9, 45); printw("PRESIONE [ESC] PARA SALIR");
            }else{
                move(4, 45); printw("[ENTER]"); move(4, 57); printw("Mostrar movimientos");
                move(6, 45); printw("[FLECHAS]"); move(6, 57); printw("Mover selector");
                move(8, 45); printw("[A]"); move(8, 57); printw("Seleccionar alfil { ♝ }");
                move(10, 45); printw("[T]"); move(10, 57); printw("Seleccionar torre { ♜ }");
                move(12, 45); printw("[R]"); move(12, 57); printw("Seleccionar reina { ♛ }");
                move(14, 45); printw("[ESC]"); move(14, 57); printw("Salir");
            }

            //---------------- INPUT en el juego----------------//
            key = getch();
            clear();
            switch (key){
            //Cerrar el menu o juego
            case 27:
                jugando = false;
                menu = false;
                endwin();
                break;
            //ENTER input
            case 10:
                if(pieza.seleccionada){
                    mostrar_mov = !mostrar_mov;
                }
                break;
            //A y a input
            case 65: case 97:
                pieza.seleccionada = true;
                pieza.figura = 'A';
                pieza.x = posx;
                pieza.y = posy;
                break;
            //R y r input
            case 82: case 114:
                pieza.seleccionada = true;
                pieza.figura = 'R';
                pieza.x = posx;
                pieza.y = posy;
                break;
            //T y t input
            case 84: case 116:
                pieza.seleccionada = true;
                pieza.figura = 'T';
                pieza.x = posx;
                pieza.y = posy;
                break;
            //FLECHAS input
            case KEY_LEFT:
                if(mostrar_mov){
                    mostrar_mov = false;
                }else if (posx > 0){
                    posx -= 1; pieza.x = posx;
                }
                break;
            case KEY_RIGHT:
                if(mostrar_mov){
                    mostrar_mov = false;
                }else if (posx<7){
                    posx += 1; pieza.x = posx;
                }
                break;
            case KEY_UP:
                if(mostrar_mov){
                    mostrar_mov = false;
                }else if (posy > 0){
                    posy -= 1; pieza.y = posy;
                }
                break;
            case KEY_DOWN:
                if(mostrar_mov){
                    mostrar_mov = false;
                }else if (posy<7){
                    posy += 1; pieza.y = posy;
                }
                break;
            //Cualquier otra tecla cancela el dibujado de movimientos
            default:
                mostrar_mov = false;
                break;
            }
        }
    }   

    endwin();
    return 0;
}