#include "Btree.h"

BTreeNode *create_BTree_node(int t) {
    BTreeNode* new = (BTreeNode*) malloc(sizeof(BTreeNode));
    new->num_keys = 0;
    new->keys = (int*) malloc(sizeof(int*)*(t*2-1));
    new->is_leaf = 1;
    new->children = (BTreeNode**) malloc(sizeof(BTreeNode*)*t*2);
    for (int i = 0; i < t*2; i++)
        new->children[i] = NULL;
    return new;
}

void free_BTree(BTreeNode *a) {
    if (a) {
        if (!a->is_leaf) {
            for (int i = 0; i <= a->num_keys; i++)
                free_BTree(a->children[i]);
        }
        free(a->keys);
        free(a->children);
        free(a);
    }
}

void imp_rec(BTreeNode *a, int level) {
    if (a) {
        int i;
        for (i = 0; i <= a->num_keys-1; i++) {
            imp_rec(a->children[i], level+1);
            for (int j = 0; j<=level; j++)
                printf("\t");
            printf("%d\n", a->keys[i]);
        }
        imp_rec(a->children[i],level+1);
    }
}

void print_BTree(BTreeNode *a) {
    imp_rec(a, 0);
}

BTreeNode *search_BTree(BTreeNode* x, int ch) {
    if (!x) return NULL;
    int i = 0;
    while (i < x->num_keys && ch > x->keys[i]) i++;
    if (i < x->num_keys && ch == x->keys[i]) return x;
    if (x->is_leaf) return NULL;
    return search_BTree(x->children[i], ch);
}

BTreeNode *init_BTree() {
    return NULL;
}

BTreeNode *Divisao(BTreeNode *x, int i, BTreeNode* y, int t) {
    BTreeNode *z = create_BTree_node(t);
    z->num_keys = t - 1;
    z->is_leaf = y->is_leaf;
    int j;
    for (j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
    if (!y->is_leaf) {
        for(j = 0; j < t; j++){
            z->children[j] = y->children[j+t];
            y->children[j+t] = NULL;
      }
    }
    y->num_keys = t - 1;
    for (j = x->num_keys; j >= i; j--)
        x->children[j+1]=x->children[j];
    x->children[i] = z;
    for (j = x->num_keys; j >= i; j--)
        x->keys[j] = x->keys[j-1];
    x->keys[i-1] = y->keys[t-1];
    x->num_keys++;
    return x;
}

BTreeNode *Insere_Nao_Completo(BTreeNode *x, int k, int t) {
    int i = x->num_keys - 1;
    if (x->is_leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->num_keys++;
        return x;
    }
    while (i >= 0 && k < x->keys[i])
        i--;
    i++;
    if (x->children[i]->num_keys == 2*t-1){
        x = Divisao(x, i+1, x->children[i], t);
        if (k > x->keys[i])
            i++;
    }
    x->children[i] = Insere_Nao_Completo(x->children[i], k, t);
    return x;
}

BTreeNode *insert_BTree(BTreeNode *T, int k, int t) {
    if (search_BTree(T,k))
        return T;

    if (!T) {
        T=create_BTree_node(t);
        T->keys[0] = k;
        T->num_keys = 1;
        return T;
    }

    if (T->num_keys == 2*t-1) {
        BTreeNode *S = create_BTree_node(t);
        S->num_keys = 0;
        S->is_leaf = 0;
        S->children[0] = T;
        S = Divisao(S,1,T, t);
        S = Insere_Nao_Completo(S, k, t);
        return S;
    }

    T = Insere_Nao_Completo(T, k, t);
    return T;
}

BTreeNode *TARVB_Libera_Remocao(BTreeNode *a) {
    free(a->keys);
    free(a->children);
    free(a);
    return NULL;
}

BTreeNode* remover(BTreeNode* arv, int ch, int t){
    if (!arv)
        return arv;

    int i;
    printf("Removendo %d...\n", ch);
    for(i = 0; i < arv->num_keys && arv->keys[i] < ch; i++);

    if (i < arv->num_keys && ch == arv->keys[i]) { //CASOS 1, 2A, 2B e 2C

    if (arv->is_leaf) { //CASO 1
        printf("\nCASO 1\n");
        for(int j = i; j < arv->num_keys-1; j++)
            arv->keys[j] = arv->keys[j+1];
        arv->num_keys--;
        if (!arv->num_keys) {
            free_BTree(arv);
            arv = NULL;
        }
        return arv;
    }

    if (!arv->is_leaf && arv->children[i]->num_keys >= t) { //CASO 2A
        printf("\nCASO 2A\n");
        BTreeNode *y = arv->children[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
        while (!y->is_leaf)
            y = y->children[y->num_keys];
        int temp = y->keys[y->num_keys-1];
        arv->children[i] = remover(arv->children[i], temp, t);
        //Eliminar recursivamente K e substitua K por K' em x
        arv->keys[i] = temp;
        return arv;
    }

    if (!arv->is_leaf && arv->children[i+1]->num_keys >= t) { //CASO 2B
        printf("\nCASO 2B\n");
        BTreeNode *y = arv->children[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
        while(!y->is_leaf) y = y->children[0];
        int temp = y->keys[0];
        y = remover(arv->children[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
        arv->keys[i] = temp;
        return arv;
    }

    if (!arv->is_leaf && arv->children[i+1]->num_keys == t-1 && arv->children[i]->num_keys == t-1) { //CASO 2C
        printf("\nCASO 2C\n");
        BTreeNode *y = arv->children[i];
        BTreeNode *z = arv->children[i+1];
        y->keys[y->num_keys] = ch;          //colocar ch ao final de filho[i]
        int j;
        for (j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
            y->keys[t+j] = z->keys[j];
        for (j=0; j<t; j++) {                 //juntar filho[i+1] com filho[i]
            y->children[t+j] = z->children[j];
            z->children[j] = NULL;
        }
        y->num_keys = 2*t-1;
        for (j=i; j < arv->num_keys-1; j++)   //remover ch de arv
            arv->keys[j] = arv->keys[j+1];
        for(j=i+1; j < arv->num_keys; j++)
        arv->children[j] = arv->children[j+1]; //remover ponteiro para filho[i+1]
        arv->children[j] = NULL;
        TARVB_Libera_Remocao(z);
        arv->num_keys--;
        if(!arv->num_keys){ //ultima revisao: 04/2020
        BTreeNode *temp = arv;
        arv = arv->children[0];
        temp->children[0] = NULL;
        TARVB_Libera_Remocao(temp);
        arv = remover(arv, ch, t);
        }
        else arv->children[i] = remover(arv->children[i], ch, t);
        return arv;
    }
    }

    BTreeNode *y = arv->children[i], *z = NULL;
    if (y->num_keys == t-1){ //CASOS 3A e 3B
    if((i < arv->num_keys) && (arv->children[i+1]->num_keys >=t)){ //CASO 3A
      printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->children[i+1];
      y->keys[t-1] = arv->keys[i];   //dar a y a chave i da arv
      y->num_keys++;
      arv->keys[i] = z->keys[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->num_keys-1; j++)  //ajustar chaves de z
        z->keys[j] = z->keys[j+1];
      y->children[y->num_keys] = z->children[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->num_keys; j++)       //ajustar filhos de z
        z->children[j] = z->children[j+1];
      z->num_keys--;
      arv->children[i] = remover(arv->children[i], ch, t);
      return arv;
    }
    if((i > 0) && (!z) && (arv->children[i-1]->num_keys >=t)){ //CASO 3A
      printf("\nCASO 3A: i igual a nchaves\n");
      z = arv->children[i-1];
      int j;
      for(j = y->num_keys; j>0; j--)               //encaixar lugar da nova chave
        y->keys[j] = y->keys[j-1];
      for(j = y->num_keys+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->children[j] = y->children[j-1];
      y->keys[0] = arv->keys[i-1];              //dar a y a chave i da arv
      y->num_keys++;
      arv->keys[i-1] = z->keys[z->num_keys-1];   //dar a arv uma chave de z
      y->children[0] = z->children[z->num_keys];         //enviar ponteiro de z para o novo elemento em y
      z->num_keys--;
      arv->children[i] = remover(y, ch, t);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->num_keys && arv->children[i+1]->num_keys == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->children[i+1];
        y->keys[t-1] = arv->keys[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->num_keys++;
        int j;
        for(j=0; j < t-1; j++){
          y->keys[t+j] = z->keys[j];     //passar filho[i+1] para filho[i]
          y->num_keys++;
        }
        if(!y->is_leaf){
          for(j=0; j<t; j++){
            y->children[t+j] = z->children[j];
            z->children[j] = NULL; //ultima revisao: 04/2020
          }
        }
        free_BTree(z);
        for(j=i; j < arv->num_keys-1; j++){ //limpar referências de i
          arv->keys[j] = arv->keys[j+1];
          arv->children[j+1] = arv->children[j+2];
        }
        arv->children[arv->num_keys] = NULL;
        arv->num_keys--;
        if(!arv->num_keys){ //ultima revisao: 04/2020
          BTreeNode *temp = arv;
          arv = arv->children[0];
          temp->children[0] = NULL;
          free_BTree(temp);
        }
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->children[i-1]->num_keys == t-1)){
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->children[i-1];
        if(i == arv->num_keys)
          z->keys[t-1] = arv->keys[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->keys[t-1] = arv->keys[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->num_keys++;
        int j;
        for(j=0; j < t-1; j++){
          z->keys[t+j] = y->keys[j];     //passar filho[i+1] para filho[i]
          z->num_keys++;
        }
        if(!z->is_leaf){
          for(j=0; j<t; j++){
            z->children[t+j] = y->children[j];
            y->children[j] = NULL; //ultima revisao: 04/2020
          }
        }
        free_BTree(y);
        arv->children[arv->num_keys] = NULL;
        arv->num_keys--;
        if(!arv->num_keys){ //ultima revisao: 04/2020
          BTreeNode *temp = arv;
          arv = arv->children[0];
          temp->children[0] = NULL;
          free_BTree(temp);
        }
        else arv->children[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }
    }
    arv->children[i] = remover(arv->children[i], ch, t);
    return arv;
}


BTreeNode* remove_BTree(BTreeNode* arv, int k, int t) {
    if(!arv || !search_BTree(arv, k))
        return arv;
    return remover(arv, k, t);
}
