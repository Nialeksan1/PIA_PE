#ifndef AUTO_H_INCLUDED
#define AUTO_H_INCLUDED

void token2(size_t n, char string[n], int *aux);
void status2(size_t n, char string[n],char linea[255]);

struct autos {
  int ID;
  int IDmarca;
  int IDsubmarca;
  int tipo;
  char anio[6];
  char precio[10];
  int version;
  int status;
};
struct autos auto_s;


void auto_alta()
{
  int opc;
  int i;
  FILE *fp;
  char *marcas[] = {"Honda","Nissan","Ford","Chevrolet"};
  char *submarcas[][4] = {{"CR-v","Pilot","Civic","Accord"},{"Xtrail","Sentra","Frontier","Altima"},{"Mustang","Explorer","Expedition","Lobo"},{"Suburban","Tahoe","Aveo","Cavalier"}};
  char *tipo[] = {"nuevo","semi-nuevo"};
  char *version[] = {"estandar","automatico"};

  do
  {
      printf("Con base a estas opciones\n1.- Honda\n2.- Nissan\n3.- Ford\n4.- Chevrolet\nIngresa el numero que corresponda a la marca: ");
      fflush(stdin);
      scanf("%d",&auto_s.IDmarca);

      printf("\nEstas son las opciones para %s: \n",marcas[auto_s.IDmarca-1]);
      for(i=0;i<4;i++)
      {
          printf("%d.- %s\n",i+1,submarcas[auto_s.IDmarca-1][i]);
      }
      printf("\nIngresa el numero que corresponda a la marca deseada: ");
      fflush(stdin);
      scanf("%d",&auto_s.IDsubmarca);

      printf("Ingresa [1] si el auto es nuevo o [2] si es semi-nuevo: ");
      fflush(stdin);
      scanf("%d",&auto_s.tipo);

      memset(auto_s.anio,'\0',sizeof(auto_s.anio));
      printf("Ingresa el anio del modelo: ");
      fflush(stdin);
      fgets(auto_s.anio, sizeof(auto_s.anio), stdin);
      new_string(sizeof(auto_s.anio), auto_s.anio);

      memset(auto_s.precio,'\0',sizeof(auto_s.precio));
      printf("Ingresa el precio: ");
      fflush(stdin);
      fgets(auto_s.precio, sizeof(auto_s.precio), stdin);
      new_string(sizeof(auto_s.precio), auto_s.precio);

      printf("Ingresa [1] si el auto es estandar o [2] si es automatico: ");
      fflush(stdin);
      scanf("%d",&auto_s.version);

      printf("\n\nSon los datos ingresados anteriormente correctos?\n[1] Si\t[0] No\nTu respuesta:  ");
      scanf("%d",&opc);
  }while(!opc);

  auto_s.status = 1;

  fp = fopen("autos.csv", "a+");

  char line[450] = "";
  char c;
  int counts = 1;
  if (fgets(line, sizeof(line), fp) == NULL) {
    auto_s.ID = 1;
  } else {
    for (c = getc(fp); c != EOF; c = getc(fp))
      if (c == '\n')
        counts += 1;
    counts++;
    auto_s.ID = counts;
  }

  fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d\n", auto_s.ID,marcas[auto_s.IDmarca-1], submarcas[auto_s.IDmarca-1][auto_s.IDsubmarca-1],tipo[auto_s.tipo-1],auto_s.anio,auto_s.precio,version[auto_s.version-1], auto_s.status);

    system("cls");
    printf("Se ha guardado correctamente el registro\nPresiona enter para continuar...");
    getch();
  fclose(fp);
}


void auto_baja()
{
    char line[255], linea[255];
    FILE *fTemp, *fp;
    fp=NULL;
    fTemp=NULL;
    int aux, op=0, idstat, counts;
    do
    {
        fp = fopen("autos.csv", "r");
        aux=0;
        memset(line, '\0', 255);
        printf("\nA continuacion se muestran todos los autos activos y no activos:\n\n");
        printf("ID          Marca          Modelo          Uso          Anio          Precio          Version     Estatus\n");
        printf("_________________________________________________________________________________________________________\n");

        fseek(fp,0,SEEK_SET);
        while(fgets(line, 255, fp) != NULL)
        {
            new_string(sizeof(line),line);
            token2(255,line,&aux);
        }
        fclose(fp);
        fp=NULL;
        printf("\nIngresa el ID del registro a dar de baja o presiona 0 para canclear: ");
        fflush(stdin);
        scanf("%d",&idstat);
        if(idstat == 0)
        {
            printf("\nDecidiste canclear la operacion\nPresiona enter para continuar...");
            break;
        }
        else
        {
            memset(line, '\0', 255);
            memset(linea, '\0', 255);
            fp = fopen("autos.csv", "r");
            fTemp = fopen("replace.tmp", "w");
            counts=0;
            fseek(fp,0,SEEK_SET);
            while(fgets(line, 255, fp) != NULL)
            {
                counts++;
                if(counts == idstat)
                {
                    new_string(sizeof(line),line);
                    status2(255,line,linea);
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
                remove("autos.csv");
            }

            if(fclose(fTemp)==0)
            {
                fTemp=NULL;
                rename("replace.tmp", "autos.csv");
            }
            printf("\nPresiona enter para continuar...");
            op=0;
        }
    }while(op);
    getch();
}


void status2(size_t n, char string[n],char linea[255])
{
    char cli[8][50];
    int i,j,x=0;
    memset(linea, '\0', 255);
    for(i=0;i<8;i++)
    {
        memset(cli[i], '\0', 50);
        for(j=x; string[j]!=',' && j<strlen(string); j++)
        {
            if(i==7)
            {
                if(string[j]=='0')
                    printf("\nEste cliente ya esta dado de baja");
                else
                {
                    system("cls");
                    printf("Diste de baja este cliente exitosamente");
                }
                strncpy(cli[7],"0",1);
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
    for(i=0;i<8;i++)
    {
        strcat(linea,cli[i]);
        if(i<7)
            strcat(linea,",");
    }
}


void token2(size_t n, char string[n], int *aux)
{
    char cli[8][50];
    int i,j,x=0;
    for(i=0;i<8;i++)
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
    printf("%2s%15s%16s%13s%14s     $%7s.00%17s%12s\n",cli[0],cli[1],cli[2],cli[3],cli[4],cli[5],cli[6],cli[7]);
}

#endif // AUTO_H_INCLUDED
