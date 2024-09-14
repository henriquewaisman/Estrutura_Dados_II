#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Criação da estrutura do nó com um dado inteiro, um filho na esquerda, um filho na direita e uma altura inteira.
typedef struct node {
  int data;
  struct node *left;
  struct node *right;
  int height;
} node;

//Cria um nó alocando espaço na memória. 
node *createTree(int data) {
  node *newNode = malloc(sizeof(node));
  if (newNode != NULL) {
    //seta os filhos do nó como nulos, sua altura como 0 e o dado é o parâmetro de entrada da função.
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
    newNode->height = 0;
  }
  return newNode;
}

//Checa a altura do nó
int checkHeight(node *node){
    //Caso o nó seja nulo, sua altura é -1
    if (node == NULL){
        return -1;    
    }
    //Retorna a checkHeight do nó
    return node->height; 
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
  //caso contrártio (o dado seja maior que a raiz atual), caminha para a direta.
  else {
    return insertNode(&(root->right), data);
  }
}

//Calcula do fator de balanceamento do nó
int balanceFactor(node *node){
    //Se o nó for nulo, seu fator é 0
    if(node == NULL){
        return 0;
    }
    //caso não seja nulo, calcula o fator: altura da esquerda - altura da direita
    return checkHeight(node->left) - checkHeight(node->right);
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
            *rootptr = temp; //seta a raiz como o filho da direita, que estava armezanado node ponteiro temporário
        } 
        //caso o nó tenha apenas um filho na esquerda:
        else if(root->right == NULL){
            node *temp = root->left; //armazena o filho da esquerda em um ponteiro temporário
            free(root); //libera a raiz
            *rootptr = temp; //seta a raiz como o filho da esquerda, que estava armezanado node ponteiro temporário
        }
        else{
            //caso o nó tenha ambos os filhos:
            node *temp = findMin(root->right); //acha o menor filho da sub-árvore da direita e armazena em um ponteiro temporário 
            root->data = temp->data; //seta o dado da raiz como o dado armazenado node nó temporário 
            return removeNode(&(root->right), temp->data); //apaga o nó substituido
        }
        return true;
    }
}

struct node *rightRotation(struct node *node){
    struct node *newRoot = node->left;      
    struct node *subTree = newRoot->right;
    newRoot->right = node;   
    node->left = subTree; 
    if (checkHeight(node->left) > checkHeight(node->right)){
        node->height = 1 + checkHeight(node->left);    
    }
    else{
        node->height = 1 + checkHeight(node->right);
    }
    if (checkHeight(newRoot->left) > checkHeight(newRoot->right)){
        newRoot->height = 1 + checkHeight(newRoot->left);
    }
    else{
        newRoot->height = 1 + checkHeight(newRoot->right); 
    }
    return newRoot; 
}

struct node *leftRotation(struct node *node){
    struct node *newRoot = node->right;
    struct node *subTree = newRoot->left;
    newRoot->left = node; 
    node->right = subTree; 
    if (checkHeight(node->left) > checkHeight(node->right))
        node->height = 1 + checkHeight(node->left);     
    else
        node->height = 1 + checkHeight(node->right); 

    if (checkHeight(newRoot->left) > checkHeight(newRoot->right)) 
        newRoot->height = 1 + checkHeight(newRoot->left);     
    else
        newRoot->height = 1 + checkHeight(newRoot->right); 
    return newRoot; 
}

struct node *balance(struct node *root, int data){
    if (root == NULL){
        return root;
    }
    if (checkHeight(root->left) > checkHeight(root->right)){
        root->height = 1 + checkHeight(root->left);
    }
    else{
        root->height = 1 + checkHeight(root->right);
    }
    int balance = balanceFactor(root);
    if (balance > 1 && data < root->left->data){
        return rightRotation(root); 
    }
    if (balance < -1 && data > root->right->data){
        return leftRotation(root);             
    }
    if (balance > 1 && data > root->left->data){
        root->left = leftRotation(root->left); 
        return rightRotation(root);
    }
    if (balance < -1 && data < root->right->data){
        root->right = rightRotation(root->right); 
        return leftRotation(root);                  
    }
    return root; 
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
  printf("data = %d, balance factor = %d\n", root->data, balanceFactor(root));
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
  
  
  return 0;
}
