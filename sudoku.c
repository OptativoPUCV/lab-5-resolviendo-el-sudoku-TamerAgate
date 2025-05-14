#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  return 1;

}

List* get_adj_nodes(Node* n)
{
    List* adj_nodes = createList();
    int i, j;

    // Encontrar la primera celda vacía
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                // Probar números del 1 al 9
                for (int num = 1; num <= 9; num++) {
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = num;

                    // Verificar si el nuevo nodo es válido
                    if (is_valid(new_node)) {
                        pushBack(adj_nodes, new_node);
                    } else {
                        free(new_node);
                    }
                }
                return adj_nodes; // Solo generar nodos para la primera celda vacía
            }
        }
    }

    return adj_nodes;
}

int is_final(Node* n)
{
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(n->sudo[i][j]==0)
        return 0;
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont)
{
    Stack* stack = createStack(); // Esto es tu List*
    push(stack, copy(initial));   // Usamos pushBack desde tu push()

    while (!is_empty(stack)) {
        Node* current = (Node*) top(stack); // Último elemento de la lista (stack)
        pop(stack);                         // popBack desde tu pop()
        (*cont)++;

        if (is_final(current)) {
            return current; // No liberamos nada más, dejamos que el main lo haga
        }

        List* adj = get_adj_nodes(current);
        node* temp = adj->first;

        while (temp != NULL) {
            Node* neighbor = (Node*) temp->data;
            push(stack, copy(neighbor)); // Copiamos cada nodo antes de apilar
            temp = temp->next;
        }

        // Liberamos el nodo actual ya que no lo usaremos más
        free(current);
        free(adj); // Solo la estructura, no los nodos internos
    }

    return NULL; // No se encontró solución
}




/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/