#include <stdio.h>
#include <stdlib.h>

//Criação da estrutura do nó com um dado inteiro, um filho na esquerda e outro na direita. Além da altura inteira.
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    int height;
} node;

//Cria um nó alocando espaço na memória. 
struct node *createNode(int data) {
    node *newNode = malloc(sizeof(struct node));
    //seta os filhos do nó como nulos, sua altura como 0 e o dado é o parâmetro de entrada da função.
    if (newNode != NULL) {
      newNode->data = data;
      newNode->left = NULL;
      newNode->right = NULL;
      newNode->height = 0;
    }
    return newNode;
}

//seta a altura do nó
int height(struct node *node) {
    //Para o nó nulo (após a folha), sua altura é -1 
    if (node == NULL){
        return -1;
    }
    return node->height;
}

//calcula do fator de balanceamento
int balanceFactor(struct node *node) {
    //caso o nó seja nulo, seu fator é 0
    if (node == NULL){
        return 0;
    }
    //caso não seja, seu fator é altura esquerda - altura direita
    return height(node->left) - height(node->right);
}

//Rodação direita
struct node *rightRotation(struct node *node) {
    struct node *newRoot = node->left;     // O novo nó raiz será o filho esquerdo do nó desbalanceado.
    struct node *subTree = newRoot->right; // A subárvore direita do novo nó raiz se tornará a subárvore esquerda do nó original.
    newRoot->right = node;                 // Ajusta o filho direito do novo nó raiz para ser o nó desbalanceado.
    node->left = subTree;                  // Atualiza o filho esquerdo do nó desbalanceado para ser a subárvore que foi deslocada.

    // Atualiza a altura do nó desbalanceado (antiga raiz) após a rotação
    if (height(node->left) > height(node->right)){ 
        node->height = 1 + height(node->left);
    }
    else{ 
        node->height = 1 + height(node->right);
    }
    // Atualiza a altura do novo nó raiz após a rotação.
    if (height(newRoot->left) > height(newRoot->right)){ 
        newRoot->height = 1 + height(newRoot->left);
    }
    else{ 
        newRoot->height = 1 + height(newRoot->right);
    }
    // Retorna o novo nó raiz após a rotação.
    return newRoot;
}

//Rotação esquerda
struct node *leftRotation(struct node *node) {
    struct node *newRoot = node->right;     // Realiza uma rotação à esquerda em torno de um nó desbalanceado para balancear a árvore.
    struct node *subTree = newRoot->left;   // O novo nó raiz será o filho direito do nó desbalanceado.
    newRoot->left = node;                   // Ajusta o filho esquerdo do novo nó raiz para ser o nó desbalanceado.
    node->right = subTree;                  // Atualiza o filho direito do nó desbalanceado para ser a subárvore que foi deslocada.

    // Atualiza a altura do nó desbalanceado (antiga raiz) após a rotação.
    if (height(node->left) > height(node->right)){ 
        node->height = 1 + height(node->left);
    }
    else{
        node->height = 1 + height(node->right);
    }
    // Atualiza a altura do novo nó raiz após a rotação.
    if (height(newRoot->left) > height(newRoot->right)){ 
        newRoot->height = 1 + height(newRoot->left);
    }
    else{ 
        newRoot->height = 1 + height(newRoot->right);
    }
    // Retorna o novo nó raiz após a rotação.
    return newRoot;
}

struct node *balance(struct node *root, int data) {
    if (root == NULL) {
        return root;
    }
    // Atualiza a altura do nó corrente (raiz) com base nas alturas das subárvores esquerda e direita.
    if (height(root->left) > height(root->right)) {
        root->height = 1 + height(root->left);
    } else {
        root->height = 1 + height(root->right);
    }
    // Calcula o fator de balanceamento do nó corrente.
    int balance = balanceFactor(root);
    // Caso o esbalanceamento seja para a esquerda, e inserção seja na esquerda-esquerda: RSD:
    if (balance > 1 && data < root->left->data) 
        return rightRotation(root);
    // Caso o desbalanceamento seja para a direita, e inserção seja na direita-direita: RSE.
    if (balance < -1 && data > root->right->data) 
        return leftRotation(root);
    // Caso o desbalanceamento seja para a esquerda,e inserção seja na esquerda-direita: RDD.
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    // Caso o desbalanceamento seja para a esquerda,e inserção seja na direita-esquerda: RDE.
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

struct node *insertNode(struct node *root, int data) {
    //Se o nó for nulo, crie o nó
    if (root == NULL){
        return createNode(data);
    }
    //Se o dado for menor que o nó atual, caminhe para a esquerda
    if (data < root->data){
        root->left = insertNode(root->left, data);
    } 
    //Se o dado for maior que o nó atual, caminhe para a direita
    else if (data > root->data){
        root->right = insertNode(root->right, data);
    } 
    //Caso o valor do nó já esteja na árovre, retone o nó
    else{
        return root;
    }
    //Balancear a cada inserção
    return balance(root, data);
}

//Acha o menor nó da árvore caminhando para a esquerda
struct node *findMin(struct node *node) {
    struct node *currentNode = node;
    while (currentNode && currentNode->left != NULL)
        currentNode = currentNode->left;
    return currentNode;
}

//Acha o maior nó da árvore caminhando para a direita
struct node *findMax(struct node *node) {
    if (node == NULL) return NULL;
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

struct node *removeNode(struct node *root, int data) {
    if (root == NULL) {
        return root;
    }
    // Caso o valor a ser removido seja menor que o valor da raiz, continua a busca pela esquerda.
    if (data < root->data) {
        root->left = removeNode(root->left, data);
    } 
    // Caso o valor a ser removido seja maior que o valor da raiz, continua a busca pela direita.
    else if (data > root->data) {
        root->right = removeNode(root->right, data);
    } 
    // Se o valor a ser removido for igual ao valor da raiz, esse é o nó a ser removido.
    else {
        // Caso o nó não tenha filhos ou tenha apenas um filho à direita.
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        // Caso o nó não tenha filhos ou tenha apenas um filho à esquerda.
        else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
         // Caso o nó tenha dois filhos. Se a subárvore esquerda for mais alta ou igual, encontra o maior valor da subárvore esquerda.
        if (height(root->left) >= height(root->right)) {
            struct node *temp = findMax(root->left);
            root->data = temp->data;
            root->left = removeNode(root->left, temp->data);
        }
        // Se a subárvore direita for mais alta, encontra o menor valor da subárvore direita.
        else {
            struct node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = removeNode(root->right, temp->data);
        }
    }
    //Balanceia a cada remoção
    return balance(root, data);
}

//Acha a altura do nó/sub-árovre
int findHeight(struct node *node) {
    if (node == NULL) {
        return -1;
    }
    //incrementa a altura a cada nó passado
    int left_height = findHeight(node->left) + 1;
    int right_height = findHeight(node->right) + 1;
    //Retorna a maior altura
    if (1 + ((left_height > right_height))) {
        return left_height;
    } else {
        return right_height;
    }
}

//Caminha na árvore para achar um nó, comparando o dado procurado com cada nó atual e caminhando na árvore
node *findNode(struct node *root, int data) {
    if (root == NULL || root->data == data) 
        return root;

    if (data < root->data) 
        return findNode(root->left, data);
    else 
        return findNode(root->right, data);
}

//Funções alvulsas de print:
void printTabs(int numtabs) {
    for (int i = 0; i < numtabs; i++) {
        printf("\t");
    }
}

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
    printTree_Rec(root->right, level + 1);
    printTabs(level);
    printf("done\n");
}

void printTree(node *root) {
    printTree_Rec(root, 0);
}

int main() {
    node *root = NULL;
    root = insertNode(root, 15);
    root = insertNode(root, 11);
    root = insertNode(root, 24);
    root = insertNode(root, 5);
    root = insertNode(root, 19);
    root = insertNode(root, 16);
    printTree(root);
    root = removeNode(root, 15);
    printTree(root);
    return 0;
}
