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
    //seta os filhos do nó como nulos e o dado é o parâmetro de entrada da função.
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
  }
  return newNode;
}

//Função para inserir nós na árvore.
bool insertNode(node **rootptr, int data){
  //seta um ponteiro que aponta para a raiz, que também é um ponteiro
  node *root = *rootptr; 
  //caso a raíz da sub-árvore atual seja nula, crie o nó. 
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
  //caso a raiz da sub-árvore atual for nulo, retorna falso (0), pois o mesmo não foi achado
  if(root == NULL){
    return false;
  }
  //caso o valor da raíz da sub-árovre atual seja igual ao valor procurado, retorna verdadeiro (1), o valor foi encontrado!
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

//acha o menor nó da árvore (o nó mais a esquerda)
node* findMin(node* root){
    //enquanto houver nó na esquerda, caminhe para a esquerda
    while(root->left != NULL){
        root = root->left;
    }
    //quando o filho da esquerda for nulo, retorne o nó, visto que o menor nó foi encontrado
    return root;
}

//Função para remover o nó
bool removeNode(node **rootptr, int data) {
    //seta o ponteiro da raiz
    node *root = *rootptr;
    //caso a raiz atual seja nula, retorna falso, visto que o nó a ser apagado nã existe
    if(root == NULL){
        return false;
    }
    //caso o dado seja menor que a raiz atual, caminha para a esquerda
    if(data < root->data){
        return removeNode(&(root->left), data);
    }
    //caso o dado seja maior que a raiz atual, caminha para a direita
    else if(data > root->data){
        return removeNode(&(root->right), data);
    } 
    //quando o nó for achado faça:    
    else{
        //caso o nó não tenha filhos, libere a memória e sete o nó como nulo
        if(root->left == NULL && root->right == NULL){
            free(root);
            *rootptr = NULL;
        } 
        //caso o nó tenha apenas um filho na direita:
        else if(root->left == NULL){ 
            node *temp = root->right; //armazena o filho da direita em um ponteiro temporário
            free(root); //libera a raiz
            *rootptr = temp; //seta a raiz como o filho da direita, que estava armezanado no ponteiro temporário
        } 
        //caso o nó tenha apenas um filho na esquerda:
        else if(root->right == NULL){
            node *temp = root->left; //armazena o filho da esquerda em um ponteiro temporário
            free(root); //libera a raiz
            *rootptr = temp; //seta a raiz como o filho da esquerda, que estava armezanado no ponteiro temporário
        }
        else{
            //caso o nó tenha ambos os filhos:
            node *temp = findMin(root->right); //acha o menor filho da sub-árvore da direita e armazena em um ponteiro temporário 
            root->data = temp->data; //seta o dado da raiz como o dado armazenado no nó temporário 
            return removeNode(&(root->right), temp->data); //apaga o nó substituido
        }
        return true;
    }
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

int main(void) {
  //criando a árvore
  node *root = NULL;
  insertNode(&root, 15);
  insertNode(&root, 11);
  insertNode(&root, 24);
  insertNode(&root, 5);
  insertNode(&root, 19);
  insertNode(&root, 16);

  printTree(root); //printando a árvore

  //achando nós a partir de seus dados, retorna 1 caso o valor seja achado, 0 caso não for achado
  printf("%d (%d)\n", 16, findNode(root, 16));
  printf("%d (%d)\n", 15, findNode(root, 15));
  printf("%d (%d)\n", 55, findNode(root, 55));
  printf("%d (%d)\n", 166, findNode(root, 166));

  removeNode(&root, 16); //remove um nó existente
  printTree(root); //printa a árvore sem o nó removido
  printf("%d (%d)\n", 16, findNode(root, 16)); //função para achar o nó, antes retorna 1 (pois o nó se encontrava na árvore), agora retorna 0 (pois o nó foi excluido)
  return 0;
}
