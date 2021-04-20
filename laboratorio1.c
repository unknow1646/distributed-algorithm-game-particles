/*
Autores: Hernán Díaz y Gina Ozimisa
Objetivo: Juego de partículas
Fecha: 04/01/2020
*/
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

#define PARTICULA   "*"
pthread_mutex_t mutex;
unsigned int **matriz;
int maxx,h,ban, maxy, random1, random2, random3,random4, n1,n2,n3,n4,k; //maxx y maxy limites de la pantalla. random: números random de cada jugador
FILE* fichero;

void *movimiento1(void *n)//movimiento del jugador 1
{
  int posx=matriz[0][0];
  int posy=matriz[0][1];
  int rapidez,numero;
  rapidez=1;
  pthread_mutex_lock(&mutex);
  if (n1<=0){
    mvprintw(5,0,"Jugador 1 muerto");
    matriz[0][0]=-13;
    matriz[0][1]=-13;
  }
  else
  {
    if(k>=2 && posx==matriz[1][0] && posy==matriz[1][1]){ //choque entre 1 y 2
      n1=n1-1;
      n2=n2-1;
      fprintf(fichero,"Los jugadores 1 y 2 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=0;
      posy=rand()%maxy-1;

      matriz[1][0]=rand()%maxx-1;
      matriz[1][1]=0;
    }
    if(k>=3 && posx==matriz[2][0] && posy==matriz[2][1]){ //choque entre 1 y 3
      n1=n1-1;
      n3=n3-1;
      fprintf(fichero,"Los jugadores 1 y 3 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=0;
      posy=rand()%maxy-1;

      matriz[2][0]=maxx;
      matriz[2][1]=rand()%maxy-1;

    }
    if(k==4 && posx==matriz[3][0] && posy==matriz[3][1]){ //choque entre 1 y 4
      n1=n1-1;
      n4=n4-1;
      fprintf(fichero,"Los jugadores 1 y 4 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=0;
      posy=rand()%maxy;

      matriz[3][0]=rand()%maxx-1;
      matriz[3][1]=maxy;
    }
    if (posx <= 0) { //funcion random entre {1,5,6}
      numero = rand()%3;
      if(numero==0)
        random1=1;
      if(numero==1)
        random1=5;
      if(numero==2)
        random1=6;
    }
    if (posy <= 0) {
      numero = rand()%3;
      if(numero==0)
        random1=3;
      if(numero==1)
        random1=5;
      if(numero==2)
        random1=8;
        //funcion random entre {3,5,8}
    }
    if (posx >= maxx-1) {
      numero = rand()%3;
      if(numero==0)
        random1=2;
      if(numero==1)
        random1=7;
      if(numero==2)
        random1=8;
          //funcion random entre {2,7,8}
    }
    if (posy >= maxy-1) {
      numero = rand()%3;
      if(numero==0)
        random1=4;
      if(numero==1)
        random1=6;
      if(numero==2)
        random1=7; //funcion random entre {4,6,7}
    }

    mvprintw(posy,posx,PARTICULA); //print de la particula
    if(random1==1)
      posx=posx+rapidez;
    if(random1==2)
      posx=posx-rapidez;
    if(random1==3)
      posy=posy+rapidez;
    if(random1==4)
      posy=posy-rapidez;
    if(random1==5){
      posx=posx+rapidez;
      posy=posy+rapidez;
    }
    if(random1==6){
      posx=posx+rapidez;
      posy=posy-rapidez;
    }
    if(random1==7){
      posx=posx-rapidez;
      posy=posy-rapidez;
    }
    if(random1==8){
      posx=posx-rapidez;
      posy=posy+rapidez;
    }
    matriz[0][0]=posx;
    matriz[0][1]=posy;
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
}

void *movimiento2(void *n)//movimiento del jugador 2
{
  int posx=matriz[1][0];
  int posy=matriz[1][1];
  int random, count,rapidez,numero;
  rapidez=1;
  pthread_mutex_lock(&mutex);
  if (n2<=0)
  {
    mvprintw(0,5,"Jugador 2 muerto");
    matriz[1][0]=-11;
    matriz[1][1]=-11;
  }
  else
  {
    if(k>=2 && posx==matriz[0][0] && posy==matriz[0][1]){ //choque entre 2 y 1
      n1=n1-1;
      n2=n2-1;
      fprintf(fichero,"Los jugadores 1 y 2 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=0;
      posy=rand()%maxy-1;

      matriz[1][0]=rand()%maxx-1;
      matriz[1][1]=0;
    }
    if(k>=3 && posx==matriz[2][0] && posy==matriz[2][1]) { //choque entre 2 y 3
      n2=n2-1;
      n3=n3-1;
      fprintf(fichero,"Los jugadores 2 y 3 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=rand()%maxx-1;
      posy=0;

      matriz[2][0]=maxx;
      matriz[2][1]=rand()%maxy-1;
    }
    if(k==4 && posx==matriz[3][0] && posy==matriz[3][1]){ //choque entre 2 y 4
      n2=n2-1;
      n4=n4-1;
      fprintf(fichero,"Los jugadores 2 y 4 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=rand()%maxx-1;
      posy=0;

      matriz[3][0]=rand()%maxx-1;
      matriz[3][1]=maxy;
    }
    if (posx <= 0) { //funcion random entre {1,5,6}
      numero = rand()%3;
      if(numero==0)
        random2=1;
      if(numero==1)
        random2=5;
      if(numero==2)
        random2=6;
    }
    if (posy <= 0) {
      numero = rand()%3;
      if(numero==0)
        random2=3;
      if(numero==1)
        random2=5;
      if(numero==2)
        random2=8;
        //funcion random entre {3,5,8}
    }
    if (posx >= maxx-1) {
      numero = rand()%3;
      if(numero==0)
        random2=2;
      if(numero==1)
        random2=7;
      if(numero==2)
        random2=8;
          //funcion random entre {2,7,8}
    }
    if (posy >= maxy-1) {
      numero = rand()%3;
      if(numero==0)
        random2=4;
      if(numero==1)
        random2=6;
      if(numero==2)
        random2=7; //funcion random entre {4,6,7}
    }
    mvprintw(posy,posx,PARTICULA); //print de la particula
    if(random2==1)
      posx=posx+rapidez;
    if(random2==2)
      posx=posx-rapidez;
    if(random2==3)
      posy=posy+rapidez;
    if(random2==4)
      posy=posy-rapidez;
    if(random2==5){
      posx=posx+rapidez;
      posy=posy+rapidez;
    }
    if(random2==6){
      posx=posx+rapidez;
      posy=posy-rapidez;
    }
    if(random2==7){
      posx=posx-rapidez;
      posy=posy-rapidez;
    }
    if(random2==8){
      posx=posx-rapidez;
      posy=posy+rapidez;
    }
    matriz[1][0]=posx;
    matriz[1][1]=posy;
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
}

void *movimiento3(void *n)//movimiento del jugador 3
{
  int posx=matriz[2][0];
  int posy=matriz[2][1];
  int rapidez,numero;
  rapidez=1;
  pthread_mutex_lock(&mutex);
  if (n3<=0){
    mvprintw(5,maxx-16,"Jugador 3 muerto");
    matriz[2][0]=-10;
    matriz[2][1]=-10;
  }
  else
  {
    if(k>=3 && posx==matriz[0][0] && posy==matriz[0][1]){ //choque entre 3 y 1
      n1=n1-1;
      n3=n3-1;
      fprintf(fichero,"Los jugadores 1 y 3 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=0;
      posy=rand()%maxy-1;

      matriz[2][0]=maxx;
      matriz[2][1]=rand()%maxy-1;
    }
    if(k>=3 && posx==matriz[1][0] && posy==matriz[1][1]) { //choque entre 3 y 2
      n2=n2-1;
      n3=n3-1;
      fprintf(fichero,"Los jugadores 2 y 3 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=rand()%maxx-1;
      posy=0;

      matriz[2][0]=maxx;
      matriz[2][1]=rand()%maxy-1;
    }
    if(k==4 && posx==matriz[3][0] && posy==matriz[3][1]){ //choque entre 3 y 4
      n3=n3-1;
      n4=n4-1;
      fprintf(fichero,"Los jugadores 3 y 4 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=maxx;
      posy=rand()%maxy-1;

      matriz[3][0]=rand()%maxx-1;
      matriz[3][1]=maxy;
    }
    if (posx <= 0) { //funcion random entre {1,5,6}
      numero = rand()%3;
      if(numero==0)
        random3=1;
      if(numero==1)
        random3=5;
      if(numero==2)
        random3=6;
    }
    if (posy <= 0) {
      numero = rand()%3;
      if(numero==0)
        random3=3;
      if(numero==1)
        random3=5;
      if(numero==2)
        random3=8;
        //funcion random entre {3,5,8}
    }
    if (posx >= maxx-1) {
      numero = rand()%3;
      if(numero==0)
        random3=2;
      if(numero==1)
        random3=7;
      if(numero==2)
        random3=8;
          //funcion random entre {2,7,8}
    }
    if (posy >= maxy-1) {
      numero = rand()%3;
      if(numero==0)
        random3=4;
      if(numero==1)
        random3=6;
      if(numero==2)
        random3=7; //funcion random entre {4,6,7}
    }
    mvprintw(posy,posx,PARTICULA);
    if(random3==1)
      posx=posx+rapidez;
    if(random3==2)
      posx=posx-rapidez;
    if(random3==3)
      posy=posy+rapidez;
    if(random3==4)
      posy=posy-rapidez;
    if(random3==5){
      posx=posx+rapidez;
      posy=posy+rapidez;
    }
    if(random3==6){
      posx=posx+rapidez;
      posy=posy-rapidez;
    }
    if(random3==7){
      posx=posx-rapidez;
      posy=posy-rapidez;
    }
    if(random3==8){
      posx=posx-rapidez;
      posy=posy+rapidez;
    }
    matriz[2][0]=posx;
    matriz[2][1]=posy;
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
}

void *movimiento4(void *n)//movimiento del jugador 4
{
  int posx=matriz[3][0];
  int posy=matriz[3][1];
  int rapidez,numero;
  rapidez=1;
  pthread_mutex_lock(&mutex);
  if(n4<=0){
    mvprintw(maxy-1,5,"Jugador 4 muerto");
    matriz[3][0]=-15;
    matriz[3][1]=-15;
  }
  else{
    if(k==4 && posx==matriz[0][0] && posy==matriz[0][1]){ //choque entre 4 y 1
      n1=n1-1;
      n4=n4-1;
      fprintf(fichero,"Los jugadores 1 y 4 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=0;
      posy=rand()%maxy-1;

      matriz[3][0]=rand()%maxx-1;
      matriz[3][1]=maxy;
    }
    if(k==4 && posx==matriz[1][0] && posy==matriz[1][1]){ //choque entre 4 y 2
      n2=n2-1;
      n4=n4-1;
      fprintf(fichero,"Los jugadores 2 y 4 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=rand()%maxx-1;
      posy=0;

      matriz[3][0]=rand()%maxx-1;
      matriz[3][1]=maxy;
    }
    if(k==4 && posx==matriz[2][0] && posy==matriz[2][1]){ //choque entre 4 y 3
      n3=n3-1;
      n4=n4-1;
      fprintf(fichero,"Los jugadores 3 y 4 chocaron en la posicion (%d,%d) y en la iteracion %d\n", posx,posy,h );
      posx=maxx;
      posy=rand()%maxy-1;

      matriz[3][0]=rand()%maxx-1;
      matriz[3][1]=maxy;
    }
    if (posx <= 0) { //funcion random entre {1,5,6}
      numero = rand()%3;
      if(numero==0)
        random4=1;
      if(numero==1)
        random4=5;
      if(numero==2)
        random4=6;
    }
    if (posy <= 0) {
      numero = rand()%3;
      if(numero==0)
        random4=3;
      if(numero==1)
        random4=5;
      if(numero==2)
        random4=8;
      //funcion random entre {3,5,8}
    }
    if (posx >= maxx-1) {
      numero = rand()%3;
      if(numero==0)
        random4=2;
      if(numero==1)
        random4=7;
      if(numero==2)
        random4=8; //funcion random entre {2,7,8}
    }
    if (posy >= maxy-1) {
      numero = rand()%3;
      if(numero==0)
        random4=4;
      if(numero==1)
        random4=6;
      if(numero==2)
        random4=7; //funcion random entre {4,6,7}
    }
    mvprintw(posy,posx,PARTICULA);
    if(random4==1)
      posx=posx+rapidez;
    if(random4==2)
      posx=posx-rapidez;
    if(random4==3)
      posy=posy+rapidez;
    if(random4==4)
      posy=posy-rapidez;
    if(random4==5){
      posx=posx+rapidez;
      posy=posy+rapidez;
    }
    if(random4==6){
      posx=posx+rapidez;
      posy=posy-rapidez;
    }
    if(random4==7){
      posx=posx-rapidez;
      posy=posy-rapidez;
    }
    if(random4==8){
      posx=posx-rapidez;
      posy=posy+rapidez;
    }
    matriz[3][0]=posx;
    matriz[3][1]=posy;
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit(0);
}

int main(int argc, char **argv)
{
  fichero = fopen("OUTPUT.txt", "wt");
  pthread_t *thread;
  pthread_attr_t attribute;
  void *exit_status;
  WINDOW *w;
  int n,i,d,j;
  n1=n2=n3=n4=0;
  n=atoi(argv[1]);//cantidad de particulas
  k=atoi(argv[2]);//cantidad de jugadores
  i=atoi(argv[3]);//iteraciones
  d=atoi(argv[4]);//delay
  //inicialización de mutex
  pthread_mutex_init(&mutex,NULL);
  pthread_attr_init(&attribute);
  thread = calloc(k,sizeof(pthread_t));
  pthread_attr_setdetachstate(&attribute,PTHREAD_CREATE_JOINABLE);
  initscr();
  getmaxyx(stdscr,maxy,maxx);//dimension de pantalla
  noecho();
  matriz = calloc(k,sizeof(unsigned int *));
  for(j=0;j<k;j++)//asignación de memoria para matriz que guardará las posiciones de cada jugador
    matriz[j] = calloc(2,sizeof(unsigned int *));
  //posición de jugador 1
  matriz[0][0]=0;
  srand(time(NULL));
  n1=n;
  matriz[0][1]=rand()%maxy;
  //posición de jugador 2
  if(k>=2)
  {
    n2=n;
    matriz[1][0]=rand()%maxx;
    matriz[1][1]=0;
  }
  //posición de jugador 3
  if(k>=3)
  {
    n3=n;
    matriz[2][0]=maxx;
    matriz[2][1]=rand()%maxy;
  }
  //posición de jugador 4
  if(k==4)
  {
    n4=n;
    matriz[3][0]=rand()%maxx;
    matriz[3][1]=maxy;
  }

  //creación de hebras
  for(h=0;h<i;h++)
  {
    clear();
    pthread_create(&thread[0],&attribute,movimiento1,(void *) 0);
    if(k>=2)
      pthread_create(&thread[1],&attribute,movimiento2,(void *) 1);
    if(k>=3)
      pthread_create(&thread[2],&attribute,movimiento3,(void *) 2);
    if(k==4)
      pthread_create(&thread[3],&attribute,movimiento4,(void *) 3);
    if(n1<=0 && n2<=0 && n3<=0 && n4<=0){
      fprintf(fichero,"El juego se detuvo en la iteracion %d debido a que todos los jugadores murieron\n",h );
      break;
    }
    refresh();
    usleep(d);
  }
  for (j = 0; j < k; j = j + 1)
    pthread_join(thread[j],&exit_status);
  pthread_mutex_destroy(&mutex);
  fclose(fichero);
  endwin();
}
