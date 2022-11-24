#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

void new_string(size_t n, char string[n]);
void token(size_t n, char string[n], char nombre[50], int *aux);
void status(size_t n, char string[n],char linea[255]);


struct domicilio {
  char calle[50];
  char colonia[50];
  char numero[6];
  char cp[6];
};
struct clientes {
  int ID;
  char nombre[50];
  char correo[50];
  char telefono[15];
  struct domicilio dom;
  int status;
};
struct clientes cliente;


void cliente_alta()
{
  int opc;
  FILE *fp;

  do
  {
      memset(cliente.nombre,'\0',sizeof(cliente.nombre));
      printf("Ingresa el nombre completo del cliente: ");
      fflush(stdin);
      fgets(cliente.nombre, sizeof(cliente.nombre), stdin);
      new_string(sizeof(cliente.nombre), cliente.nombre);

      memset(cliente.correo,'\0',sizeof(cliente.correo));
      printf("Ingresa el correo del cliente: ");
      fflush(stdin);
      fgets(cliente.correo, sizeof(cliente.correo), stdin);
      new_string(sizeof(cliente.correo), cliente.correo);

      memset(cliente.telefono,'\0',sizeof(cliente.telefono));
      printf("Ingresa el telefono del cliente: ");
      fflush(stdin);
      fgets(cliente.telefono, sizeof(cliente.telefono), stdin);
      new_string(sizeof(cliente.telefono), cliente.telefono);

      memset(cliente.dom.calle,'\0',sizeof(cliente.dom.calle));
      printf("Ingresa la calle del cliente: ");
      fflush(stdin);
      fgets(cliente.dom.calle, sizeof(cliente.dom.calle), stdin);
      new_string(sizeof(cliente.dom.calle), cliente.dom.calle);

      memset(cliente.dom.colonia,'\0',sizeof(cliente.dom.colonia));
      printf("Ingresa la colonia del cliente: ");
      fflush(stdin);
      fgets(cliente.dom.colonia, sizeof(cliente.dom.colonia), stdin);
      new_string(sizeof(cliente.dom.colonia), cliente.dom.colonia);

      memset(cliente.dom.numero,'\0',sizeof(cliente.dom.numero));
      printf("Ingresa el numero exterior del cliente: ");
      fflush(stdin);
      fgets(cliente.dom.numero, sizeof(cliente.dom.numero), stdin);
      new_string(sizeof(cliente.dom.numero), cliente.dom.numero);

      memset(cliente.dom.cp,'\0',sizeof(cliente.dom.cp));
      printf("Ingresa el codigo postal del cliente: ");
      fflush(stdin);
      fgets(cliente.dom.cp, sizeof(cliente.dom.cp), stdin);
      new_string(sizeof(cliente.dom.cp), cliente.dom.cp);

      printf("\n\nSon los datos ingresados anteriormente correctos?\n[1] Si\t[0] No\nTu respuesta:  ");
      fflush(stdin);
      scanf("%d",&opc);
  }while(!opc);

  cliente.status = 1;
  char status[2];
  sprintf(status, "%d", cliente.status);

  fp = fopen("clientes.csv", "a+");

  char line[350] = "";
  char c;
  int count = 1;
  if (fgets(line, sizeof(line), fp) == NULL) {
    cliente.ID = 1;
  } else {
    for (c = getc(fp); c != EOF; c = getc(fp))
      if (c == '\n')
        count += 1;
    count++;
    cliente.ID = count;
  }

  char id[20];
  sprintf(id, "%d", cliente.ID);

  fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s,%d\n", cliente.ID, cliente.nombre,
          cliente.correo, cliente.telefono, cliente.dom.calle,
          cliente.dom.colonia, cliente.dom.numero, cliente.dom.cp, cliente.status);

    system("cls");
    printf("Se ha guardado correctamente el registro\nPresiona enter para continuar...");
    getch();
  fclose(fp);
}


void cliente_baja()
{
    char nombre[50], line[255], linea[255];
    FILE *fTemp, *fp;
    fp=NULL;
    fTemp=NULL;
    int aux, op=0, idstat, counts;
    do
    {
        fp = fopen("clientes.csv", "r");
        aux=0;
        memset(nombre, '\0', 50);
        memset(line, '\0', 255);
        printf("Ingresa el nombre del cliente o presione 0 para canclear: ");
        fflush(stdin);
        fgets(nombre, sizeof(nombre), stdin);
        new_string(sizeof(nombre),nombre);

        if(strcmp(nombre,"0")==0)
        {
            printf("\nDecidiste canclear la operacion\nPresiona enter para continuar...");
            break;
        }
        printf("Numero ID                                        Nombre    Status\n");
        printf("_________________________________________________________________\n");

        while(fgets(line, 255, fp) != NULL)
        {
            new_string(sizeof(line),line);
            token(255,line,nombre,&aux);
        }
        fclose(fp);
        fp=NULL;
        if(aux==0)
        {
            printf("\nNo se encontraron coincidencias con ese nombre\nDeseas ingresar otro cliente?\n[1] Si\t[0] No\n\nTu respuesta: ");
            fflush(stdin);
            scanf("%d",&op);
            system("cls");
        }
        else
        {
            printf("\nIngresa el ID del cliente que se dara de baja o presione 0 para cancelar: ");
            fflush(stdin);
            scanf("%d",&idstat);
            if(idstat==0)
            {
                printf("\nDecidiste canclear la operacion\nPresiona enter para continuar...");
                break;
            }
            memset(line, '\0', 255);
            memset(linea, '\0', 255);
            fp = fopen("clientes.csv", "r");
            fTemp = fopen("replace.tmp", "w");
            counts=0;
            fseek(fp,0,SEEK_SET);
            while(fgets(line, 255, fp) != NULL)
            {
                counts++;
                if(counts == idstat)
                {
                    new_string(sizeof(line),line);
                    status(255,line,linea);
                    fprintf(fTemp,"%s\n",linea);
                }
                else
                {
                    new_string(sizeof(line),line);
                    fprintf(fTemp,"%s\n",line);
                }
            }
            if(fclose(fp)==0)
            {
                fp=NULL;
                remove("clientes.csv");
            }

            if(fclose(fTemp)==0)
            {
                fTemp=NULL;
                rename("replace.tmp", "clientes.csv");
            }
            printf("\nPresiona enter para continuar...");
            op=0;
        }
    }while(op);
    getch();
}


void status(size_t n, char string[n],char linea[255])
{
    char cli[9][50];
    int i,j,x=0;
    memset(linea, '\0', 255);
    for(i=0;i<9;i++)
    {
        memset(cli[i], '\0', 50);
        for(j=x; string[j]!=',' && j<strlen(string); j++)
        {
            if(i==8)
            {
                if(string[j]=='0')
                    printf("\nEste cliente ya esta dado de baja");
                else
                {
                    system("cls");
                    printf("Diste de baja este cliente exitosamente");
                }
                strncpy(cli[8],"0",1);
            }
            else
            {
                strncat(cli[i], &string[j], 1);
            }
            x++;
            if (x >= strlen(string))
                break;
        }
        x++;
    }
    for(i=0;i<9;i++)
    {
        strcat(linea,cli[i]);
        if(i<8)
            strcat(linea,",");
    }
}


void token(size_t n, char string[n],char nombre[50], int *aux)
{
    char cli[9][50];
    int i,j,x=0;
    for(i=0;i<9;i++)
    {
        memset(cli[i], '\0', 50);
        for(j=x; string[j]!=',' && j<strlen(string); j++)
        {
            strncat(cli[i], &string[j], 1);
            x++;
            if (x >= strlen(string))
                break;
        }
        x++;
    }
    x=0;
    for(i=0; i<strlen(string); i++)
    {
        for(j=0; j<strlen(nombre); j++)
        {
            if(nombre[j]==string[i])
            {
                x++;
                i++;
            }
            else
            {
                break;
            }
        }
    }
    if(x==strlen(nombre))
    {
        printf("%9s%46s%10s\n",cli[0],cli[1],cli[8]);
        (*aux)++;
    }
}


void new_string(size_t n, char string[n])
{
    /*Funcion que quita el salto de linea*/
    size_t ln = strlen(string) - 1;
    if (string[ln] == '\n')
        string[ln] = '\0';
}

#endif // CLIENTE_H_INCLUDED
