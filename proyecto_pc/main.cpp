#include <iostream>
#include <iomanip>
#include<cstdlib>
#include <string.h>
#include <fstream>
#include "lista.cpp"
#include <windows.h>
#include <iomanip>

using namespace std;

struct Libro
{
    char ISBN[200];
    char Titulo[400];
    char Autor[200];
    char Editorial[200];
    char Fecha[50];
    char Claves[900];
    char Texto[200];
    int contador = 0;   // contador para saber el numero de ocurrencia de palabras
    int num_libro = -50;  // para escoger que libro se va a abrir
    int abierto = 0; //numero de veces abierto
    bool imprimir = false;
};
struct buscador
{

    char palabra[50];
    int contador = 0;

};
struct paginas
{
    char hoja[40][200];
    int num_linea = 0;
};
/*Funciones para el buscador*/
void buscar_palabras(struct TNodo <Libro> **lista_libros);
void llenar_lista(struct TNodo <Libro> **lista_libros);
void separar(char *buscar,struct TNodo <buscador> **lista);
void prender_lista(struct TNodo <buscador> **lista_buscador,struct TNodo <Libro> **lista_libros);
bool comparar (struct TNodo <buscador> **lista_buscador,struct TNodo <buscador> **lista_linea,bool buscar);
void mostrar_lista(struct TNodo <Libro> **lista_libros);
void abrir_texto(struct TNodo <Libro> **lista_libros,TNodo <buscador> **listapalabras);
void ContaPTexto(char *nombre, TNodo <buscador> **listapalabras, int &suma); //La lista contiene las palabras a buscar
void ordenar(TNodo <buscador> **listapalabras,struct TNodo <Libro> **lista_libros,int opcion);
void apagar_lista(struct TNodo <Libro> **lista_libros);
/*Funciones para la parte administrativa*/
void administrador(struct TNodo <Libro> **Lista);
void InsertarLibros(struct TNodo <Libro> **Lista);
void ListarLibros();
void ConsultarLibros();
void ModificarLibros(struct TNodo <Libro> **Lista);
void BorrarLibros(struct TNodo <Libro> **Lista);
void top_5_mas(struct TNodo <Libro> **Lista);
void top_5_menos(struct TNodo <Libro> **Lista);

int main()
{
    system("color F0");
    char contrasena[100];
    struct TNodo <Libro> *Lista;
    CrearLista(&Lista);
    cout <<"   _     _                           _     _               "<<endl;
    cout <<"  | |   (_)                         (_)   | |              "<<endl;
    cout <<"  | |__  _  ___ _ ____   _____ _ __  _  __| | ___          "<<endl;
    cout <<"  | '_ \\| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\  "<<endl;
    cout <<"  | |_) | |  __/ | | \\ V /  __/ | | | | (_| | (_) |       "<<endl;
    cout <<"  |_.__/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/    "<<endl;
    cout <<"                                                           "<<endl;
    llenar_lista(&Lista);
    int opcion=0;
    do
    {

        system("cls");
        cout << "BIBLIOTECA: "<<endl<<
             "Ingrese la opcion deseada"<<endl<<
             "1. BUSCAR libro: "<<endl<<
             "2. Administrador: "<<endl<<
             "3. salir del programa: "<<endl;
        cin>>opcion;
        switch(opcion)
        {
        case 1:
        {
            buscar_palabras(&Lista);
            break;
        }
        case 2:
            cout << "Digite la clave"<<endl;
            cin.ignore();
            cin.getline(contrasena,sizeof(contrasena));
            if(strcmp(contrasena,"abc123")==0)
            {
                administrador(&Lista);
                system("pause");
            }
            else
            {
                system("color f4");
                system("cls");
                cout << "contrasena incorrecta"<<endl;
                system("pause");
            }

            break;
        case 3:
            system("cls");
            cout << "Fin del programa." <<endl;
            system("pause");
            system("cls");
            break;
        default:
            system("cls");
            cout << "respuesta invalida"<<endl
                 << "vuelva a intentar" <<endl;
            system("pause");

        }
    }
    while(opcion!=3);
    DestruirLista(&Lista);
}

void buscar_palabras(struct TNodo <Libro> **lista_libros)
{
    system("cls");
    cout <<"   _                             _               "<<endl;
    cout <<"  | |                           | |              "<<endl;
    cout <<"  | |__  _   _ ___  ___ __ _  __| | ___  _ __    "<<endl;
    cout <<"  | '_ \\| | | / __|/ __/ _` |/ _` |/ _ \\| '__|   "<<endl;
    cout <<"  | |_) | |_| \\__ \\ (_| (_| | (_| | (_) | |      "<<endl;
    cout <<"  |_.__/ \\__,_|___/\\___\\__,_|\\__,_|\\___/|_|      "<<endl;
    cout <<"                                                 "<<endl;

    int opcion = 0;
    bool bandera =  false;
    struct TNodo <buscador> *lista_buscador;
    CrearLista(&lista_buscador);
    char buscar[900];
    cout << "Bienvenido al la biblioteca virtual"<<endl
         << "digite el libro que desea buscar" <<endl;
    cin.ignore();
    cin.getline(buscar,200);
    strlwr(buscar);
    separar(buscar,&lista_buscador);//separa las palabras del ususario en una lista
    prender_lista(&lista_buscador,lista_libros);
    do
    {
        system("cls");
        cout <<"   _                             _               "<<endl;
        cout <<"  | |                           | |              "<<endl;
        cout <<"  | |__  _   _ ___  ___ __ _  __| | ___  _ __    "<<endl;
        cout <<"  | '_ \\| | | / __|/ __/ _` |/ _` |/ _ \\| '__|   "<<endl;
        cout <<"  | |_) | |_| \\__ \\ (_| (_| | (_| | (_) | |      "<<endl;
        cout <<"  |_.__/ \\__,_|___/\\___\\__,_|\\__,_|\\___/|_|      "<<endl;
        cout <<"                                                 "<<endl;

        if(opcion != 6 && opcion != 7)
        {
            ordenar(&lista_buscador,lista_libros,opcion);
            mostrar_lista(lista_libros);
            abrir_texto(lista_libros,&lista_buscador);
        }
        else
        {
            if(opcion == 6)
                top_5_mas(lista_libros);
            else
                top_5_menos(lista_libros);
            system("cls");
        }
        system("pause");
        system("cls");
        cout << "0) ordenar los libros por Ocurrencia"<<endl
             << "1) ordenar los libros por ISBN"<<endl
             << "2) ordenar los libros por Autor"<<endl
             << "3) ordenar los libros por Editorial"<<endl
             << "4) ordenar los libros por Titulo"<<endl
             << "5) MOSTRAR 5 MAS BUSCADOS: "<<endl
             << "6) MOSTRAR 5 MENOS BUSCADOS: "<<endl
             << "7) salir"<<endl;
        cin>>opcion;
        while(opcion>7 || opcion < 0)
        {
            cout << "respuesta invalida, vuelva a intentar" << endl;
            cin >> opcion;
        }
        system("cls");
    }
    while(opcion != 7);
    apagar_lista(lista_libros);



}
void llenar_lista(struct TNodo <Libro> **lista_libros)
{
    struct Libro Libros;
    ifstream archP ("Libros.dat", ios::binary);
    if(archP)
    {
        while(!archP.eof())
        {
            if (archP.read((char *)&Libros, sizeof(Libros)))
            {
                InsertarFinal(lista_libros,Libros);
            }


        }
        archP.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    system("pause");
}
void prender_lista(struct TNodo <buscador> **lista_buscador,struct TNodo <Libro> **lista_libros)
{
    struct Libro dato;
    int suma = 0;
    int j = 0;
    ifstream archivo ("Libros.dat",ios::binary);
    bool buscar  = true; //tiene que seguir buscando
    if (archivo)
    {
        struct TNodo <buscador> *lista_linea;
        struct TNodo <Libro> *aux_libros = *lista_libros;
        while(!archivo.eof())
        {
            if(archivo.read((char*)&dato,sizeof(dato)))
            {
                CrearLista(&lista_linea);
                separar(dato.Autor,&lista_linea);
                buscar = comparar(lista_buscador,&lista_linea,buscar);
                if(!buscar)
                {
                    while(aux_libros != NULL)
                    {
                        if(strcmp(dato.Titulo, (aux_libros->dato).Titulo)==0 && strcmp(dato.Autor, (aux_libros->dato).Autor)==0)
                        {
                            j++; //cuenta cuantos libros se han buscado, opcion
                            (aux_libros->dato).num_libro = j;
                            (aux_libros->dato).imprimir = true;
                        }
                        aux_libros = aux_libros->sig;
                    }
                    DestruirLista(&lista_linea);
                }
                aux_libros = *lista_libros;
                separar(dato.ISBN,&lista_linea);
                buscar = comparar(lista_buscador,&lista_linea,buscar);
                if(!buscar)
                {

                    while(aux_libros != NULL)
                    {
                        if(strcmp(dato.Titulo, (aux_libros->dato).Titulo)==0 && strcmp(dato.Autor, (aux_libros->dato).Autor)==0)
                        {
                            j++;
                            (aux_libros->dato).num_libro = j;
                            (aux_libros->dato).imprimir = true;
                        }
                        aux_libros = aux_libros->sig;
                    }
                    DestruirLista(&lista_linea);
                }
                aux_libros = *lista_libros;
                separar(dato.Editorial,&lista_linea);
                buscar = comparar(lista_buscador,&lista_linea,buscar);
                if(!buscar)
                {

                    while(aux_libros != NULL)
                    {
                        if(strcmp(dato.Titulo, (aux_libros->dato).Titulo)==0 && strcmp(dato.Autor, (aux_libros->dato).Autor)==0)
                        {
                            j++;
                            (aux_libros->dato).num_libro = j;
                            (aux_libros->dato).imprimir = true;
                        }
                        aux_libros = aux_libros->sig;
                    }
                    DestruirLista(&lista_linea);
                }
                aux_libros = *lista_libros;
                separar(dato.Titulo,&lista_linea);
                buscar = comparar(lista_buscador,&lista_linea,buscar);
                if(!buscar)
                {

                    while(aux_libros != NULL)
                    {
                        if(strcmp(dato.Titulo, (aux_libros->dato).Titulo)==0 && strcmp(dato.Autor, (aux_libros->dato).Autor)==0)
                        {
                            j++;
                            (aux_libros->dato).num_libro = j;
                            (aux_libros->dato).imprimir = true;
                        }
                        aux_libros = aux_libros->sig;
                    }
                    DestruirLista(&lista_linea);
                }
                aux_libros = *lista_libros;
                separar(dato.Claves,&lista_linea);
                buscar = comparar(lista_buscador,&lista_linea,buscar);
                if(!buscar)
                {

                    while(aux_libros != NULL)
                    {
                        if(strcmp(dato.Titulo, (aux_libros->dato).Titulo)==0 && strcmp(dato.Autor, (aux_libros->dato).Autor)==0)
                        {
                            j++;
                            (aux_libros->dato).num_libro = j;
                            (aux_libros->dato).imprimir = true;
                        }
                        aux_libros = aux_libros->sig;
                    }
                    DestruirLista(&lista_linea);
                }
                aux_libros = *lista_libros;
                suma = 0;
                ContaPTexto(dato.Texto,lista_buscador,suma);
                if(suma > 0)
                    buscar = false;
                if(!buscar)
                {

                    while(aux_libros != NULL)
                    {
                        if(strcmp(dato.Titulo, (aux_libros->dato).Titulo)==0 && strcmp(dato.Autor, (aux_libros->dato).Autor)==0 && (aux_libros->dato).imprimir != true)
                        {
                            j++;
                            (aux_libros->dato).num_libro = j;
                            (aux_libros->dato).imprimir = true;
                        }
                        aux_libros = aux_libros->sig;
                    }
                    DestruirLista(&lista_linea);


                }
                buscar = true;


            }

        }

        archivo.close();

    }
    else
    {
        cout <<"no se pudo abrir el archivo"<< endl;
    }

}
void separar(char *buscar,struct TNodo <buscador> **lista)
{
    char *p;
    struct TNodo <buscador> *aux_lis = *lista;
    char aux[200];
    struct buscador ins;
    strcpy(aux,buscar);
    p = strtok(buscar," ,;:");

    while(p != NULL)
    {
        strcpy(ins.palabra,p);
        InsertarFinal(lista,ins);
        p = strtok(NULL," ,;:");

    }
    strcpy(buscar,aux);
}
bool comparar (struct TNodo <buscador> **lista_buscador,struct TNodo <buscador> **lista_linea,bool buscar)
{
    struct TNodo <buscador> *aux_linea = *lista_linea;
    struct TNodo <buscador> *aux_buscador = *lista_buscador;
    while(aux_linea != NULL)
    {
        while(aux_buscador != NULL)
        {

            if (strcmp((aux_buscador->dato).palabra,(aux_linea->dato).palabra)==0)
            {
                return false;
            }
            aux_buscador = aux_buscador->sig;
        }
        aux_buscador = *lista_buscador;
        aux_linea = aux_linea->sig;
    }
    return true;

}
void mostrar_lista(struct TNodo <Libro> **lista_libros)
{

    cout << "==Posibles libros=="<<endl;
    struct TNodo<Libro> *aux=*lista_libros;
    struct TNodo<Libro> *aux2=*lista_libros;
    while(aux!= NULL)
    {
        if((aux->dato).imprimir)
        {
            cout <<(aux->dato).num_libro << ")"<<" Titulo:"<< (aux->dato).Titulo<<endl
                 << "informacion: "<< endl
                 << "ISBN: "<<(aux->dato).ISBN<<endl
                 << "Autor: "<<(aux->dato).Autor<<endl
                 << "Editorial: "<<(aux->dato).Editorial<<endl
                 << "veces abierto "<<(aux->dato).abierto<<endl;
        }
        aux = aux->sig;
    }


}
void abrir_texto(struct TNodo <Libro> **lista_libros,TNodo <buscador> **listapalabras)
{
    char cuadrado = 219;
    struct TNodo<Libro> *aux_libro=*lista_libros;
    int opcion, contador = 0;
    bool encontrado = false;
    ifstream abrir;
    while(aux_libro !=NULL)
    {
        if((aux_libro->dato).imprimir)
        {
            encontrado = true;
        }
        aux_libro = aux_libro->sig;
    }
    if(encontrado)
    {
        cout << "Escoja el libro que desea abrir"<<endl;
        cin >> opcion;
        while (opcion >= (LongitudLista(lista_libros)+1) || opcion <= 0)
        {
            cout << "opcion invalida, vuelva a intentar "<<endl;
            cin>>opcion;
        }
        encontrado = false;
        aux_libro = *lista_libros;
        while(aux_libro != NULL && !encontrado)
        {
            if ((aux_libro->dato).num_libro == opcion)
                encontrado = true;
            else
                aux_libro = aux_libro->sig;
        }
        cout <<"El libro es: " <<(aux_libro->dato).Titulo << endl;
        (aux_libro->dato).abierto++;
        system("cls");
        char *p;

        struct TNodo <buscador> *aux = *listapalabras; //Se pone el aux al principio de la lista
        abrir.open((aux_libro->dato).Texto);
        if(abrir)
        {
            char linea_libro[200];
            char linea_copia[200];
            while(!abrir.eof())
            {
                if (contador < 30)
                {
                    int contador2 = 0;
                    abrir.getline(linea_libro, sizeof(linea_libro));
                    strlwr(linea_libro);//Se pone en minusculas la linea
                    strcpy(linea_copia,linea_libro);
                    strlwr((aux->dato).palabra); //Se pone en minusculas la palabra
                    aux=*listapalabras;
                    while(aux!=NULL) //aux libro
                    {
                        p=strtok(linea_libro, ",- .;:"); //Se separa el tok
                        while(p!=NULL)
                        {

                            if(strcmp(p,(aux->dato).palabra)==0) //Se compara el tok con la palabra para ver si existe
                            {

                                cout << cuadrado << cuadrado<< cuadrado<< cuadrado;
                                //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_GREEN);
                                cout<< p << cuadrado<< cuadrado<< cuadrado<< cuadrado<<" ";
                            }
                            else
                            {
                                if(contador2==0)
                                    cout << p << " ";
                            }
                            p=strtok(NULL,",- .;:");
                        }
                        contador2++;
                        strcpy(linea_libro,linea_copia);
                        aux=aux->sig;

                    }
                    cout << " " <<endl;
                    contador++;
                }
                else
                {
                    contador = 0;
                    system("pause");
                    system("cls");
                    cout <<endl <<endl <<endl;
                }
            }
            abrir.close();
        }
        else
        {
            cout << "El libro no se pudo abrir "<<endl;
        }
        cout <<"====FIN DEL LIBRO===="<<endl;
    }
    else
    {
        cout << "No se encontraron libros"<<endl;
    }
}
void ContaPTexto(char *nombre, TNodo <buscador> **listapalabras, int &suma) //La lista contiene las palabras a buscar
{
    ifstream archivo(nombre); //Se abre el archivo

    if(archivo)
    {
        suma = 0;
        struct TNodo <buscador> *aux = *listapalabras;
        struct TNodo <buscador> *aux2;
        char Linea[200]; //La linea que se va a coger
        char linea_copia[200];
        char *p;
        while(!archivo.eof())
        {
            archivo.getline(Linea,200, '\n'); //Se toma la linea
            strlwr(Linea); //Se pone en minusculas la linea
            strcpy(linea_copia,Linea);

            aux=*listapalabras;
            while(aux!=NULL)
            {
                p=strtok(Linea, ",- ."); //Se separa el tok
                while(p!=NULL)
                {
                    if(strcmp(p,(aux->dato).palabra)==0) //Se compara el tok con la palabra para ver si existe
                    {
                        (aux->dato).contador++;
                        suma++;
                    }
                    p=strtok(NULL," ,.-");
                }
                strcpy(Linea,linea_copia);
                aux=aux->sig;
            }
        }
        aux=*listapalabras;
        delete p,Linea;
    }
    else
    {
        cout<<"PROBLEMAS AL ABRIR EL ARCHIVO";
    }
}

void ordenar(TNodo <buscador> **listapalabras,struct TNodo <Libro> **lista_libros,int opcion)
{
    struct TNodo <Libro> *aux = *lista_libros;
    struct TNodo <Libro> *aux2;
    int suma = 0;
    switch(opcion)
    {
    case 0:// caso por ocurrencia de palabras
    {
        struct TNodo <Libro> *aux_libros = *lista_libros;
        struct TNodo <buscador> *aux_buscador = *listapalabras;
        while(aux_libros != NULL)
        {
            ContaPTexto((aux_libros->dato).Texto,listapalabras,suma);
            (aux_libros->dato).contador = suma;
            aux_libros = aux_libros->sig;
        }
        while(aux!=NULL) //Organizar de mayor a menor
        {
            aux2=aux->sig;
            while(aux2!=NULL)
            {
                if((aux->dato).contador < (aux2->dato).contador)
                {
                    struct Libro tmp2=aux->dato;
                    aux->dato=aux2->dato;
                    aux2->dato=tmp2;
                }
                aux2=aux2->sig;
            }
            aux=aux->sig;
        }


        break;
    }
    case 1: //caso por isbn
    {
        while(aux!=NULL) //Organizar de mayor a menor
        {
            aux2=aux->sig;
            while(aux2!=NULL)
            {
                if(strcmp((aux->dato).ISBN,(aux2->dato).ISBN)<0)
                {
                    struct Libro tmp2=aux->dato;
                    aux->dato=aux2->dato;
                    aux2->dato=tmp2;
                }
                aux2=aux2->sig;
            }
            aux=aux->sig;
        }
        break;

    }
    case 2: //caso por autor
    {
        cout <<"entro"<<endl;
        while(aux!=NULL) //Organizar de mayor a menor
        {
            aux2=aux->sig;
            while(aux2!=NULL)
            {
                if(strcmp((aux->dato).Autor,(aux2->dato).Autor)>0)
                {
                    struct Libro tmp2=aux->dato;
                    aux->dato=aux2->dato;
                    aux2->dato=tmp2;
                }
                aux2=aux2->sig;
            }
            aux=aux->sig;
        }
        break;
    }
    case 3: //caso por editorial
    {
        while(aux!=NULL) //Organizar de mayor a menor
        {
            aux2=aux->sig;
            while(aux2!=NULL)
            {
                if(strcmp((aux->dato).Editorial,(aux2->dato).Editorial)>0)
                {
                    struct Libro tmp2=aux->dato;
                    aux->dato=aux2->dato;
                    aux2->dato=tmp2;
                }
                aux2=aux2->sig;
            }
            aux=aux->sig;
        }
        break;
    }
    case 4: //caso por titulo
    {
        while(aux!=NULL) //Organizar de mayor a menor
        {
            aux2=aux->sig;
            while(aux2!=NULL)
            {
                if(strcmp((aux->dato).Titulo,(aux2->dato).Titulo)>0)
                {
                    struct Libro tmp2=aux->dato;
                    aux->dato=aux2->dato;
                    aux2->dato=tmp2;
                }
                aux2=aux2->sig;
            }
            aux=aux->sig;
        }
        break;
    }
    case 5:
    {
        while(aux!=NULL) //Organizar de mayor a menor
        {
            aux2=aux->sig;
            while(aux2!=NULL)
            {
                if(strcmp((aux->dato).Fecha,(aux2->dato).Fecha)>0)
                {
                    struct Libro tmp2=aux->dato;
                    aux->dato=aux2->dato;
                    aux2->dato=tmp2;
                }
                aux2=aux2->sig;
            }
            aux=aux->sig;
        }
        break;
    }

    }

}
void apagar_lista(struct TNodo <Libro> **lista_libros)
{
    struct TNodo <Libro> *aux = *lista_libros;
    while(aux != NULL)
    {
        (aux->dato).imprimir = false;
        (aux->dato).num_libro = -50;
        aux = aux->sig;
    }
}





void administrador(struct TNodo <Libro> **Lista)
{

    int Opcion;
    do
    {
        system("cls");

        cout <<"             _           _       _     _                 _                "<<endl;
        cout <<"            | |         (_)     (_)   | |               | |               "<<endl;
        cout <<"    __ _  __| |_ __ ___  _ _ __  _ ___| |_ _ __ __ _  __| | ___  _ __     "<<endl;
        cout <<"   / _` |/ _` | '_ ` _ \\| | '_ \\| / __| __| '__/ _` |/ _` |/ _ \\| '__|    "<<endl;
        cout <<"  | (_| | (_| | | | | | | | | | | \\__ \\ |_| | | (_| | (_| | (_) | |       "<<endl;
        cout <<"   \\__,_|\\__,_|_| |_| |_|_|_| |_|_|___/\\__|_|  \\__,_|\\__,_|\\___/|_|       "<<endl;
        cout <<"                                                                          "<<endl;

        cout << "FUNCIONES ADMINISTRATIVAS: "<<endl<<
             "Ingrese funcion deseada"<<endl<<
             "1. AGREGAR LIBRO: "<<endl<<
             "2. MODIFICAR LIBRO: "<<endl<<
             "3. BORRAR LIBRO: "<<endl<<
             "4. CONSULTAR DATOS DE LIBROS: "<<endl<<
             "5. MOSTRAR 5 MAS BUSCADOS: "<<endl<<
             "6. MOSTRAR 5 MENOS BUSCADOS: "<<endl<<
             "7. SALIR: "<<endl;
        cin>>Opcion;
        switch(Opcion)
        {
        case 1:
            InsertarLibros(Lista);
            break;
        case 2:
            ModificarLibros(Lista);
            break;
        case 3:
            BorrarLibros(Lista);
            break;
        case 4:
            ListarLibros();
            break;
        case 5:
            top_5_mas(Lista);
            break;
        case 6:
            top_5_menos(Lista);
            break;
        case 7:
            return;

        }


    }
    while(Opcion != 7);

}
void InsertarLibros(struct TNodo <Libro> **Lista)
{
    system("cls");
    cout << "|||INSERTAR LIBRO|||"<< endl;
    struct Libro Libros;
    cout << "Digite ISBN ";
    cin.ignore();
    cin.getline(Libros.ISBN,200);
    cout << "Digite Titulo ";
    cin.getline(Libros.Titulo,200);
    cout << "Digite Autor ";
    cin.getline(Libros.Autor,200);
    cout << "Digite Editorial ";
    cin.getline(Libros.Editorial,200);
    cout << "Digite la Fecha ";
    cin.getline(Libros.Fecha,200);
    cout << "Digite las palabras claves: ";
    cin.getline (Libros.Claves,200);
    cout << "Digite el nombre de la ubicacion del libro: ";
    cin.getline (Libros.Texto,200);
    strlwr(Libros.Autor);
    strlwr(Libros.Claves);
    strlwr(Libros.Editorial);
    strlwr(Libros.Titulo);
    strlwr(Libros.ISBN);
    InsertarFinal(Lista,Libros);
    ofstream archP ("Libros.dat", ios::binary|ios::app);
    if(archP)
    {
        archP.write((char *) &Libros, sizeof(Libros));
        archP.close();
        cout << "Libro agregado correctamente" << endl;
    }
    else
    {
        cout << "No se pudo agregar el libro correctamente" << endl;
    }
    system("pause");
}
void ListarLibros()
{
    int contador = 0;
    system("cls");
    cout << "|||CONSULTAR LIBROS|||" << endl;
    struct Libro Libros;
    ifstream archP ("Libros.dat", ios::binary);
    if(archP)
    {
        while(!archP.eof())
        {
            if (archP.read((char *)&Libros, sizeof(Libros)))
            {
                cout << "Libro # " << contador <<endl;
                cout << " ISBN: " << Libros.ISBN << endl
                     <<" Titulo: " << Libros.Titulo << endl
                     <<" Autor: " << Libros.Autor << endl
                     <<" Editorial: "<< Libros.Editorial << endl
                     <<" Fecha: "<< Libros.Fecha <<endl
                     <<" Palabras Clave: "<< Libros.Claves <<endl
                     <<" Libro: "<< Libros.Texto << endl;
                contador++;
            }


        }
        archP.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    system("pause");
}

void ConsultarLibros()
{
    system("cls");
    cout << "|||CONSULTAR UN LIBRO|||" << endl;
    struct Libro Libros;
    ifstream archP("Libros.dat", ios::binary);
    if (archP)
    {
        char ISBN[20];
        bool Encontro=false;

        cout << "Digite el ISBN:"<< endl ;
        cin >> ISBN;
        while (!archP.eof() && !Encontro)
        {
            if (archP.read((char *)&Libros, sizeof(Libros)))
            {
                if (strcmp(ISBN, Libros.ISBN)==0)
                    Encontro=true;
            }
        }
        if (Encontro)
            cout << "ISBN: " << Libros.ISBN << " Titulo: " << Libros.Titulo << " Autor: " << Libros.Autor << " Editorial: "<< Libros.Editorial << " Palabras Clave: "<< Libros.Claves << " Libro: "<< Libros.Texto << endl;
        else
            cout << "El codigo de producto no existe!" << endl;
        archP.close();
    }
    else
        cout << "No se pudo abrir el archivo!" << endl;
    system("pause");
}

void ModificarLibros(struct TNodo <Libro> **Lista)
{

    int opcion;
    struct TNodo <Libro> *aux=*Lista;
    system("cls");
    cout << "|||MODIFICAR LIBROS|||" << endl;
    struct Libro Libros;
    fstream archP("Libros.dat", ios::binary|ios::in|ios::out);
    if (archP)
    {
        char ISBN[20];
        bool Encontro=false;

        cout << "Digite eL ISBN del libro a modificar:"<< endl ;
        cin >> ISBN;
        while (!archP.eof() && !Encontro)
        {
            if (archP.read((char *)&Libros, sizeof(Libros)))
            {
                if (strcmp(ISBN, Libros.ISBN)==0)
                    Encontro=true;
            }
        }
        if (Encontro)
        {
            cout << "ISBN: " << Libros.ISBN << " Titulo: " << Libros.Titulo << " Autor: " << Libros.Autor << " Editorial: "<< Libros.Editorial << " Palabras Clave: "<< Libros.Claves<< endl;
            cout<< "Que desea modificar?"<<endl<<
                "1. ISBN: "<<endl<<
                "2. TITULO: "<<endl<<
                "3. AUTOR: "<<endl<<
                "4. EDITORIAL: "<<endl;
            cin>> opcion;

            switch(opcion)
            {
            case 1:
                cout << "Digite el nuevo ISBN:" << endl;
                cin.ignore();
                cin.getline(Libros.ISBN, sizeof(Libros.ISBN));
                archP.seekg((int)(-1*sizeof(Libros)),ios::cur);
                archP.write((char *)&Libros, sizeof(Libros));
                while(aux != NULL)
                {
                    if(strcmp(ISBN,(aux->dato).ISBN)==0)
                    {
                        strcpy((aux->dato).ISBN,Libros.ISBN);
                    }
                    aux = aux->sig;
                }
                cout << "ISBN modificado correctamente!" << endl;
                break;
            case 2:
                cout << "Digite el nuevo titulo:" << endl;
                cin.ignore();
                cin.getline(Libros.Titulo, sizeof(Libros.Titulo));
                archP.seekg((int)(-1*sizeof(Libros)),ios::cur);
                archP.write((char *)&Libros, sizeof(Libros));
                while(aux != NULL)
                {
                    if(strcmp(ISBN,(aux->dato).ISBN)==0)
                    {
                        strcpy((aux->dato).Titulo,Libros.Titulo);
                    }
                    aux = aux->sig;
                }
                cout << "Titulo modificado correctamente!" << endl;
                break;
            case 3:
                cout << "Digite el nuevo autor:" << endl;
                cin.ignore();
                cin.getline(Libros.Autor, sizeof(Libros.Autor));
                archP.seekg((int)(-1*sizeof(Libros)),ios::cur);
                archP.write((char *)&Libros, sizeof(Libros));
                while(aux != NULL)
                {
                    if(strcmp(ISBN,(aux->dato).ISBN)==0)
                    {
                        strcpy((aux->dato).Autor,Libros.Autor);
                    }
                    aux = aux->sig;
                }
                cout << "Autor modificado correctamente!" << endl;
                break;
            case 4:
                cout << "Digite la nueva editorial:" << endl;
                cin.ignore();
                cin.getline(Libros.Editorial, sizeof(Libros.Editorial));
                archP.seekg((int)(-1*sizeof(Libros)),ios::cur);
                archP.write((char *)&Libros, sizeof(Libros));
                while(aux != NULL)
                {
                    if(strcmp(ISBN,(aux->dato).ISBN)==0)
                    {
                        strcpy((aux->dato).Editorial,Libros.Editorial);
                    }
                    aux = aux->sig;
                }
                cout << "Editorial modificada correctamente!" << endl;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
            }

        }
        else
            cout << "El ISBN no existe!" << endl;
        archP.close();
    }
    else
        cout << "No se pudo abrir el archivo!" << endl;
    system("pause");
}
void BorrarLibros(struct TNodo <Libro> **Lista)
{
    system("cls");
    struct TNodo <Libro> *aux = *Lista;
    Libro x;
    cout << "|||BORRAR LIBROS|||" << endl;
    struct Libro Libros;
    ifstream archP("Libros.dat", ios::binary);
    ofstream archTemp("LibrosTemp.dat", ios::binary);
    if (archP)
    {
        char ISBN[20];
        int z = 0;
        cout << "Digite el ISBN del libro a borrar:"<< endl ;
        cin >> ISBN;
        while(aux != NULL)
        {
            if (strcmp(ISBN, (aux->dato).ISBN)==0)
            {
                Eliminar(Lista,x,z);
            }
            z++;
            aux =aux->sig;
        }
        while (!archP.eof())
        {
            if (archP.read((char *)&Libros, sizeof(Libros)))
            {
                if (strcmp(ISBN, Libros.ISBN)!=0)
                {
                    archTemp.write((char *)&Libros, sizeof(Libros));
                }
            }
        }
        cout << "Libro borrado!" << endl;
        archP.close();
        archTemp.close();
        remove("Libros.dat");
        rename("LibrosTemp.dat","Libros.dat");
    }
    else
        cout << "No se pudo abrir el archivo!" << endl;
    system("pause");
}
void top_5_mas(struct TNodo <Libro> **Lista)
{
    system("cls");
    cout << endl << endl;
    char cuadrado = 220;
    char rectangulo = 219;
    char piso = 223;
    struct TNodo <Libro> *aux = *Lista;
    struct TNodo <Libro> *aux2;
    while(aux!=NULL) //Organizar de mayor a menor
    {
        aux2=aux->sig;
        while(aux2!=NULL)
        {
            if((aux->dato).abierto < (aux2->dato).abierto)
            {
                struct Libro tmp2=aux->dato;
                aux->dato=aux2->dato;
                aux2->dato=tmp2;
            }
            aux2=aux2->sig;
        }
        aux=aux->sig;
    }
    aux = *Lista;
    int j = 1;
    while(aux != NULL && j <= 5)
    {
        cout <<"libro "<< j <<")   "<<rectangulo<<" ";
        for(int i = 0; i < (aux->dato).abierto - 1; i++)
        {
            cout<<piso<<piso;
        }
        if((aux->dato).abierto == 1)
        {
            cout<<piso;
        }
        cout<<endl << "           "<<rectangulo<<" "<<endl;
        aux = aux->sig;
        j++;
    }
    cout <<"           ";
    for(int i = 0; i<57; i++)
    {
        if(i<40)
            cout<<piso;
        else if(i == 40)
            cout <<endl<<"             ";
        else
            cout <<i-40<<" ";
    }
    aux = *Lista;
    cout << endl;
    j = 1;
    while(aux != NULL && j <= 5)
    {
        cout << j <<") "<<(aux->dato).Titulo << " fue buscado "<< (aux->dato).abierto << " veces"<<endl;
        aux= aux->sig;
        j++;

    }
    system("pause");

}
void top_5_menos(struct TNodo <Libro> **Lista)
{
    system("cls");
    cout << endl << endl;
    char cuadrado = 220;
    char rectangulo = 219;
    char piso = 223;
    struct TNodo <Libro> *aux = *Lista;
    struct TNodo <Libro> *aux2;
    while(aux!=NULL) //Organizar de mayor a menor
    {
        aux2=aux->sig;
        while(aux2!=NULL)
        {
            if((aux->dato).abierto > (aux2->dato).abierto)
            {
                struct Libro tmp2=aux->dato;
                aux->dato=aux2->dato;
                aux2->dato=tmp2;
            }
            aux2=aux2->sig;
        }
        aux=aux->sig;
    }
    aux = *Lista;
    int j = 1;
    while(aux != NULL && j <= 5)
    {
        cout <<"libro "<< j <<")   "<<rectangulo<<" ";
        for(int i = 0; i < (aux->dato).abierto - 1; i++)
        {
            cout<<piso<<piso;
        }
        if((aux->dato).abierto == 1)
        {
            cout<<piso;
        }
        cout<<endl << "           "<<rectangulo<<" "<<endl;
        aux = aux->sig;
        j++;
    }
    cout <<"           ";
    for(int i = 0; i<57; i++)
    {
        if(i<40)
            cout<<piso;
        else if(i == 40)
            cout <<endl<<"             ";
        else
            cout <<i-40<<" ";
    }
    aux = *Lista;
    cout << endl;
    j = 1;
    while(aux != NULL && j <= 5)
    {
        cout << j <<") "<<(aux->dato).Titulo << " fue buscado "<< (aux->dato).abierto << " veces"<<endl;
        aux= aux->sig;
        j++;

    }
    system("pause");
}
