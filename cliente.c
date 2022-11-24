#include <stdio.h>
#include <string.h>

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

void function2(size_t n, char string[n]);

void cliente_alta() {
  struct clientes cliente;
  FILE *fp;

  fflush(stdin);
  fgets(cliente.nombre, sizeof(cliente.nombre), stdin);
  function2(sizeof(cliente.nombre), cliente.nombre);

  fflush(stdin);
  fgets(cliente.correo, sizeof(cliente.correo), stdin);
  function2(sizeof(cliente.correo), cliente.correo);

  fflush(stdin);
  fgets(cliente.telefono, sizeof(cliente.telefono), stdin);
  function2(sizeof(cliente.telefono), cliente.telefono);

  fflush(stdin);
  fgets(cliente.dom.calle, sizeof(cliente.dom.calle), stdin);
  function2(sizeof(cliente.dom.calle), cliente.dom.calle);

  fflush(stdin);
  fgets(cliente.dom.colonia, sizeof(cliente.dom.colonia), stdin);
  function2(sizeof(cliente.dom.colonia), cliente.dom.colonia);

  fflush(stdin);
  fgets(cliente.dom.numero, sizeof(cliente.dom.numero), stdin);
  function2(sizeof(cliente.dom.numero), cliente.dom.numero);

  fflush(stdin);
  fgets(cliente.dom.cp, sizeof(cliente.dom.cp), stdin);
  function2(sizeof(cliente.dom.cp), cliente.dom.cp);

  cliente.status = 1;
  char status[20];
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

  fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", id, cliente.nombre,
          cliente.correo, cliente.telefono, cliente.dom.calle,
          cliente.dom.colonia, cliente.dom.numero, cliente.dom.cp, status);

  fclose(fp);
}

void function2(size_t n, char string[n]) {
  size_t ln = strlen(string) - 1;
  if (string[ln] == '\n')
    string[ln] = '\0';
}
