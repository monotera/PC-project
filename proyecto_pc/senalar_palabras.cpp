void abrir_texto(char *nombre, TNodo <Palabras> *listapalabras)
{
    ifstream abrir;
    struct TNodo<Palabras> *aux; //Se pone el aux al principio de la lista
    abrir.open(nombre);
    if(abrir)
    {
        char linea_libro[200];
        while(!abrir.eof())
        {
            if (contador < 30)
            {
                abrir.getline(linea_libro, sizeof(linea_libro));
                minusculas(linea_libro);//Se pone en minusculas la linea
                minusculas((aux->dato).Palabra); //Se pone en minusculas la palabra
                p=strtok(linea_libro, ",- ."); //Se separa el tok
                aux=listapalabras;
                while(aux!=NULL)
            {
                while(p!=NULL)
                {
                    if(strcmp(p,(aux->dato).Palabra)==0) //Se compara el tok con la palabra para ver si existe
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_GREEN);
                        cout<< p << " ";
                    }
                    else
                    {
                        cout << p << " ";
                    }
                    p=strtok(NULL," ,.-");
                }
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
