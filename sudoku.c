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
    int i, j, k;
    int seen[10];

    for (i = 0; i < 9; i++) {
        for (k = 0; k < 10; k++) seen[k] = 0;
        for (j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0;
                seen[num] = 1;
            }
        }
    }

    for (j = 0; j < 9; j++) {
        for (k = 0; k < 10; k++) seen[k] = 0;
        for (i = 0; i < 9; i++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num]) return 0;
                seen[num] = 1;
            }
        }
    }

    for (int boxRow = 0; boxRow < 3; boxRow++) {
        for (int boxCol = 0; boxCol < 3; boxCol++) {
            for (k = 0; k < 10; k++) seen[k] = 0;
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    int num = n->sudo[boxRow * 3 + i][boxCol * 3 + j];
                    if (num != 0) {
                        if (seen[num]) return 0;
                        seen[num] = 1;
                    }
                }
            }
        }
    }

    return 1;
}

List* get_adj_nodes(Node* n)
{
    List* adj_nodes = createList();

    int i, j;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = num;

                    if (is_valid(new_node)) {
                        pushBack(adj_nodes, new_node);
                    } else {
                        free(new_node);
                    }
                }
                return adj_nodes;
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
    Stack* stack = createStack();
    push(stack, initial);

    while (!is_empty(stack))
    {
        Node* current = top(stack);
        pop(stack);
        (*cont)++;

        if (is_final(current))
        {
            return current;
        }

        List* adj_nodes = get_adj_nodes(current);
        Node* next_node = first(adj_nodes);

        while (next_node != NULL)
        {
            push(stack, next_node);
            next_node = next(adj_nodes);
        }
    }

    return NULL;
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