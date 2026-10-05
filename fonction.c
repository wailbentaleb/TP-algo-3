#include "bib.h"
//  fonction des pile  :
stack InitStack() {
    stack s; s.top = NULL; return s;
}

void Stack(stack* s, char* x) {
    Element* newNode = (Element*)malloc(sizeof(Element));
    strcpy(newNode->info, x);
    newNode->next = s->top;
    s->top = newNode;
}

void Unstack(stack* s, char* x) {
    if (s->top == NULL) { printf("stack empty\n"); return; }
    Element* temp = s->top;
    s->top = s->top->next;
    strcpy(x, temp->info);
    free(temp);
}

bool StackEmpty(stack x) {   return x.top == NULL; }

int Summit(stack* s) {
    if (s->top == NULL) { printf("Stack is empty!\n"); return -1; }
    return 0;
}

//  fonction des file :
Queue InitQueue() {
    Queue q; q.head = NULL; q.tail = NULL; return q;
}

bool QueueEmpty(Queue q) { return q.head == NULL; }

void Queueq(Queue* q, char* x) {
    Element* newNode = (Element*)malloc(sizeof(Element));
    strcpy(newNode->info, x);
    newNode->next = NULL;
    if (q->head == NULL) { q->head = q->tail = newNode; }
    else { q->tail->next = newNode; q->tail = newNode; }
}

void UnQueue(Queue* q, char* x) {
    if (q->head == NULL) { printf("queue is empty\n"); return; }
    Element* temp = q->head;
    strcpy(x, temp->info);
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    free(temp);
}

// --- GESTION CLIENTS ---

clientRecord CreateClientRecord() {
    clientRecord c;
    c.numero_compte = 0;
    strcpy(c.nom, "");
    c.statut_abonnement = false;
    c.usages_Restants = InitStack();
    c.achat_en_attente = InitQueue();
    c.next = NULL;
    return c;
}
// linked list node 
clientRNode* CreateNode(clientRecord c) {
    clientRNode* NewNode = (clientRNode*)malloc(sizeof(clientRNode));
    NewNode->client = c;
    NewNode->next = NULL;
    return NewNode;
}

void AddClient(clientRNode** list, clientRecord c) {
    clientRNode* NEW = CreateNode(c);
    NEW->next = *list;
    *list = NEW;
}

void ModifyClientInfo(clientRNode** list, int numero_cmp, char* newName, int newstatus) {
    clientRNode* temp = *list;
    while (temp != NULL) {
        if (temp->client.numero_compte == numero_cmp) {
            if (newName != NULL) strcpy(temp->client.nom, newName);
            if (newstatus >= 0) temp->client.statut_abonnement = newstatus;
            printf(" UpDated !\n");
            return;
        }
        temp = temp->next;
    }
    printf(" not UpDated !\n");
}

clientRNode* SearchClient(clientRNode* list, char* name, int numerocompte) {
    clientRNode* temp = list;
    while (temp != NULL) {
        if ((strcmp(temp->client.nom, name) == 0) || (temp->client.numero_compte == numerocompte)) {
            printf("found!\n");
            return temp;
        }
        temp = temp->next;
    }
    printf("not found !\n");
    return NULL;
}

bool CheckSubscription(clientRNode* list, int numero_cmp) {
    clientRNode* temp = list;
    while (temp != NULL) {
        if (temp->client.numero_compte == numero_cmp) {
            return temp->client.statut_abonnement;
        }
        temp = temp->next;
    }
    return false;
}

void DisplayList(clientRNode* list) {
    clientRNode* temp = list;
    while (temp != NULL) {
        printf("\n Name: %s", temp->client.nom);
        printf("\n Account: %d", temp->client.numero_compte);
        printf("\n Subscription status: %d\n", temp->client.statut_abonnement);
        temp = temp->next;
    }
}

void SubscribeToPremiem(clientRNode* list, char* name, int numaccount, int N, char services[][50]) {
    clientRNode* found = SearchClient(list, name, numaccount);
    if (found != NULL) {
        found->client.statut_abonnement = true;
        for (int i = 0; i < N; i++) {
            Stack(&found->client.usages_Restants, services[i]);
        }
    } else {
        printf("Client not found !\n");
    }
}

void UseService(clientRecord* c) {
    char service[50];
    if (StackEmpty(c->usages_Restants)) {
        printf("the client is NOT allowed to use this service\n");
    } else {
        Unstack(&c->usages_Restants, service);
        Queueq(&c->achat_en_attente, service);
        printf("the client is allowed to use the service: %s\n", service);
    }
}

void DisplayHistory(Queue* q) {
    if (QueueEmpty(*q)) return;
    char service[50];
    UnQueue(q, service);
    printf("%s\n", service);
    DisplayHistory(q);
}

void AskAndConsumeAgain(clientRecord* c) {
    int choice = 1;
    while (choice == 1 && !StackEmpty(c->usages_Restants)) {
        UseService(c);
        if (StackEmpty(c->usages_Restants)) {
            printf("No more usages left.\n");
            break;
        }
        printf("Consume another? (1=yes, 0=no): ");
        scanf("%d", &choice);
    }
    printf("\n History: \n");
    DisplayHistory(&c->achat_en_attente);
}