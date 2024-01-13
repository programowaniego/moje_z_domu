#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include "Plansza.c"
#include "wykonywanie_ruchow.c"
#include "ocena.c"
#include "alfabeta.c"

void main()
{
    plansza* stol = utworz_plansze(stol,"O",0,1);
    element* lista_posuniec = NULL;
    
    int glebokosc_O, glebokosc_X,alfa,beta,debesciak;
    char gracz_O, gracz_X;
    
    printf("Wybierz tryb gry: BB -> bot - bot ; BG -> bot - gracz ; GG -> gracz - gracz");
    scanf(" %c%c",&gracz_O,&gracz_X);
    
    if(gracz_O == 'B'){
        
        printf("Podaj glebokosc bota grajacego O:");
        scanf("%d",&glebokosc_O);

    }
    if(gracz_X == 'B'){
        
        printf("Podaj glebokosc bota grajacego X:");
        scanf("%d",&glebokosc_X);
        
    }

    wypisz(stol);
    int polozenie = 0, i = 0;
    
    while(polozenie != 2137 && i != 50){        //polozenie 2137 oznacza ze gracz spasowal drugi warunek mowi o tym ze wykonujemy w sumie i ruchow
        alfa = 1000;
        beta = -1000;
        debesciak = 0;
        if(stol->gracz_na_ruchu == "O")
        {   
            if(gracz_O == 'G'){
                
                polozenie = pozycja(stol,lista_posuniec);
                postaw_pionek(stol,&polozenie);
            
            }
            else if(gracz_O == 'B'){
                
                alfaBeta(stol,glebokosc_O,&alfa,beta,&debesciak);
                postaw_pionek(stol,&debesciak);
                printf("Debesciak -> %c%d\n",debesciak%kolumny + 'A',(debesciak - debesciak%kolumny)/kolumny + 1); 
            }
        }
        else
        {

            if(gracz_X == 'G'){
                
                polozenie = pozycja(stol,lista_posuniec);
                postaw_pionek(stol,&polozenie);
            
            }
            else if(gracz_X == 'B'){
                
                alfaBeta(stol,glebokosc_X,&alfa,beta,&debesciak);
                postaw_pionek(stol,&debesciak);
                printf("Debesciak -> %c%d\n",debesciak%kolumny + 'A',(debesciak - debesciak%kolumny)/kolumny + 1);
            }
        }
        //element* lista_posuniec = dostepne_ruchy(stol,lista_posuniec,polozenie,1);
        wypisz(stol);
        i++;
        stol->gracz_na_ruchu = stol->gracz_na_ruchu == "O" ? "X" : "O";
    }
    
    terytorium_po_calosci(stol,"X");
    terytorium_po_calosci(stol,"O");
    wypisz(stol);
    printf("Podsumowanie rozgrywki:\nTerytorium X - %d Terytorium O - %d\nPionki X - %d     Pionki O - %d\nKomi - 5.5        Punkty O - %d\nPunkty X - %.1f\n",stol->terytoriumX,stol->terytoriumO,ile_pionkow(stol,"X"),ile_pionkow(stol,"O"),stol->terytoriumX + ile_pionkow(stol,"X") + 5.5,stol->terytoriumO + ile_pionkow(stol,"O"));
}
