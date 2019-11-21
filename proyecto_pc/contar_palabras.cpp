//CODIGO DESARROLLADO POR: GABRIEL EDUARDO ALMEIDA LUNA

#include <iostream>
#include <string.h>
#include <fstream>
#include "lista.cpp"

using namespace std;
/*Nombre: minusculas
  Entrada: char *linea
  Salida: No hay salida
  objetivo: Poner en minusculas todas las letras*/
void minusculas(char* linea);
struct Palabras
{
    char Palabra[100];
    int Cantidad;
};

void ContaPTexto(char *nombre, TNodo <Palabras> *listapalabras) //La lista contiene las palabras a buscar
{
    ifstream archivo(nombre); //Se abre el archivo

    if(archivo)
    {
        struct TNodo <LineaPalabra> *aux;
        struct TNodo <LineaPalabra> *aux2;
        char Linea[200]; //La linea que se va a coger
        char *p;
        while(!archivo.eof())
        {
            archivo.getline(Linea,200, '\n'); //Se toma la linea
            minusculas(Linea); //Se pone en minusculas la linea
            p=strtok(Linea, ",- ."); //Se separa el tok
            aux=listapalabras;

            while(aux!=NULL)
            {
                while(p!=NULL)
                {
                    if(strcmp(p,(aux->dato).Palabra)==0) //Se compara el tok con la palabra para ver si existe
                    {
                        (aux->dato).Cantidad+=1;
                    }
                    p=strtok(NULL," ,.-");
                }
                aux=aux->sig;
            }
        }
        aux=listapalabras;
        while(aux!=NULL) //Organizar de mayor a menor
        {
            aux2=aux->sig;
            while(aux2!=NULL)
            {
                if((aux->dato).Cantidad<(aux2->dato).Cantidad)
                {
                    struct LineaPalabra tmp2=aux->dato;
                    aux->dato=aux2->dato;
                    aux2->dato=tmp2;
                }
                aux2=aux2->sig;
            }
            cout<<(aux->dato).Palabra<<" : "<<(aux->dato).Cantidad<<endl;
            aux=aux->sig;
        }
        delete p,Linea;
    }
    else
    {
        cout<<"PROBLEMAS AL ABRIR EL ARCHIVO";
    }
}

void minusculas(char* linea)
{
    for(int i=0; i<strlen(linea); i++)
    {
        if(*(linea+i)>=65&&*(linea+i)<=90)
        {
            *(linea+i)=*(linea+i)+32;
        }
    }
}
