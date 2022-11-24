#include <stdio.h>

struct domicilio
{
    char calle[50];
    char colonia[50];
    char numero[6];
    char cp[6];
};

struct cliente
{
    int ID;
    char nombre[50];
    char correo[50];
    char telefono[11];
    struct domicilio dom;
    int status;
};

int main()
{
    FILE *fp;
    /*fgets(cliente.nombre,sizeof(cliente.nombre),stdin);
    fgets(cliente.correo,sizeof(cliente.correo),stdin);
    fgets(cliente.telefono,sizeof(cliente.telefono),stdin);
    fgets(cliente.dom.calle,sizeof(cliente.dom.calle),stdin);
    fgets(cliente.dom.colonia,sizeof(cliente.dom.colonia),stdin);
    fgets(cliente.dom.numero,sizeof(cliente.dom.numero),stdin);
    fgets(cliente.dom.cp,sizeof(cliente.dom.cp),stdin);*/

    fp = fopen("clientes.csv","a+");
    if(feof(fp))
    {
        printf("Data file is emtpy, exiting the program");
        //exit(0);
    }
    //fprintf(fp,)

}
