#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Criação da estrutura do nó com um dado inteiro, um filho na esquerda e outro na direita.
typedef struct node {
  int data;
  struct node *left;
  struct node *right;
} node;

//Cria um nó alocando espaço na memória. 
node *createTree(int data) {
  node *newNode = malloc(sizeof(node));
  if (newNode != NULL) {
    //setra os filhos do nó como nulos e o dado é o parâmetro da função.
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
  }
  return newNode;
}

//printa os níveis da árvore
void printTabs(int numtabs) {
  for (int i = 0; i < numtabs; i++) {
    printf("\t");
  }
}

//printa a árvore por níveis
void printTree_Rec(node *root, int level) {
  if (root == NULL) {
    printTabs(level);
    printf("--<empty>--\n");
    return;
  }
  printTabs(level);
  printf("data = %d\n", root->data);
  printTabs(level);
  printf("left\n");
  printTree_Rec(root->left, level + 1);
  printTabs(level);
  printf("right\n");
  printTree_Rec(root->right, level +1);
  printTabs(level);
  printf("done\n");
}

//printa a ávore recursivamente
void printTree(node* root){
  printTree_Rec(root, 0);
}

//Função para inserir nós na árvore.
bool insertNode(node **rootptr, int data){
  node *root = *rootptr; 
  //insere o nó caso a raíz da sub-árvore atual seja nula. 
  if (root == NULL) {
    (*rootptr) = createTree(data);
    return true;
  }
  //caso o valor do nó já exista, retorna falso, visto que o 2 nós não podem ter o mesmo dado.  
  if (data == root->data) {
    return false;
  }
  //caso o dado inserido seja menor que a raíz da sub-árovre atual, caminha para a esquerda.
  if (data < root->data) {
    return insertNode(&(root->left), data);
  } 
  //caso contrártio (o dado seja maior que a raiz atual), caminha para a direita.
  else {
    return insertNode(&(root->right), data);
  }
}

//Função para achar um nó na árvore.
bool findNode(node * root, int data){
  //caso a raiz da sub-árvore atual for nulo, retorna falso, pois o mesmo não foi achado
  if(root == NULL){
    return false;
  }
  //caso o valor da raíz da sub-árovre atual seja igual ao valor procurado, retorna verdadeiro, o valor foi encontrado!
  if(root->data == data){
    return true;
  }
  //caso o dado seja menor que a raíz da sub-árovre atual, caminha para a esquerda
  if(data < root->data){
    return findNode(root->left, data);
  }
  //caso o dado seja maior que a raíz da sub-árovre atual, caminha para a direita
  else{
    return findNode(root->right, data);
  }
}

node* findMin(node* root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

bool removeNode(node **rootptr, int data) {
    node *root = *rootptr;
    if(root == NULL){
        return false;
    }
    if(data < root->data){
        return removeNode(&(root->left), data);
    }
    else if(data > root->data){
        return removeNode(&(root->right), data);
    } 
    else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            *rootptr = NULL;
        } 
        else if(root->left == NULL){
            node *temp = root->right;
            free(root);
            *rootptr = temp;
        } 
        else if(root->right == NULL){
            node *temp = root->left;
            free(root);
            *rootptr = temp;
        }
        else{
            node *temp = findMin(root->right);
            root->data = temp->data;
            return removeNode(&(root->right), temp->data);
        }
        return true;
    }
}


int main(void) {
  node *root = NULL;
  insertNode(&root, 15);
  insertNode(&root, 11);
  insertNode(&root, 24);
  insertNode(&root, 5);
  insertNode(&root, 19);
  insertNode(&root, 16);

  printTree(root);

  printf("%d (%d)\n", 16, findNode(root, 16));
  printf("%d (%d)\n", 15, findNode(root, 15));
  printf("%d (%d)\n", 55, findNode(root, 55));
  printf("%d (%d)\n", 166, findNode(root, 166));
  
  removeNode(&root, 16);
  printTree(root);
  printf("%d (%d)\n", 16, findNode(root, 16));
  return 0;
}
