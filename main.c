#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "cliente.h"
#include "auto.h"


int menu(int max, int min, char opcs[], char return_menu[])
{
    int opt=1;
    do
    {
        if(opt<min || opt>max)
        {
            system("cls");
            printf("El valor ingresado debe estar en el rango de %d a %d para poder continuar...\n\n",min,max);
        }
        printf("%s", opcs);
        scanf("%d",&opt);
        if(opt==max)
        {
            printf("%s",return_menu);
            getch();
            if(max==6)
                exit(0);
        }
    }while(opt<min || opt>max);
    return opt;

}

int main()
{
    int opc1;
    int opc2;
    char opc1_s[6][18] = {"Clientes", "Autos", "Cotizacion", "Reportes", "Reactivar usuario"};
    do
    {
        opc1 = menu(6,1,"Agencia de Autos FCFM\n\n1.\tClientes\n2.\tAutos\n3.\tCotizacion\n4.\tReportes\n5.\tReactivar usuario\n6.\tSalir\n\nTu respuesta: ","\n\nHas decidido salir del programa\nPresiona enter para continuar...");
        system("cls");
        switch(opc1)
        {
            case 1:
                do
                {
                    printf("%d. %s\n\n",opc1,opc1_s[opc1-1]);
                    opc2 = menu(3,1,"1.\tAlta\n2.\tBaja\n3.\tRegresar\n\nTu respuesta: ","\n\nHas decidido regresar al menu\nPresiona enter para continuar...\n");
                    if(opc2 == 1)
                        cliente_alta();
                    else if(opc2 == 2)
                        cliente_baja();
                    system("cls");
                }while(opc2==1 || opc2==2);
                break;
            case 2:
                do
                {
                    printf("%d. %s\n\n",opc1,opc1_s[opc1-1]);
                    opc2 = menu(3,1,"1.\tAlta\n2.\tBaja\n3.\tRegresar\n\nTu respuesta: ","\n\nHas decidido regresar al menu\nPresiona enter para continuar...\n");
                    if(opc2 == 1)
                        auto_alta();
                    else if(opc2 == 2)
                        auto_baja();
                    system("cls");
                }while(opc2==1 || opc2==2);
            case 3:
                break;
            case 4:
                printf("1.\tListado de clientes\n2.\tListado de autos\n3.\tImpresion de cotizacion\n4.\tRegresar\n\nTu respuesta: ");
                break;
            case 5:
                break;
        }
        system("cls");
    }while(((opc1==1 || opc1==2) && opc2==3) || (opc1==4 && opc2==4));
    return 0;
}
