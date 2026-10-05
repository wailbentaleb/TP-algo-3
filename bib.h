#ifndef bib_H
#define  bib_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure pour les maillons des Piles et Files
typedef struct Element {
    char info[50];
    struct Element* next;
} Element;

// Structure Pile
typedef struct stack {
    Element* top;
} stack;

// Structure File
typedef struct queue {
    Element* head;
    Element* tail;
} Queue;

// Structure du Record Client
typedef struct clientRecord {
    char nom[20];
    int numero_compte;
    bool statut_abonnement;
    stack usages_Restants;
    Queue achat_en_attente;
    struct clientRecord* next; // Optionnel si on utilise clientRNode
} clientRecord;

// Structure pour le Noeud de la Liste Chaînée principale
typedef struct clientRNode {
    clientRecord client;
    struct clientRNode* next;
} clientRNode;

// --- Prototypes des fonctions (La Librairie) ---
stack InitStack();
void Stack(stack* s, char* x);
void Unstack(stack* s, char* x);
bool StackEmpty(stack x);
int Summit(stack* s);

Queue InitQueue();
bool QueueEmpty(Queue q);
void Queueq(Queue* q, char* x);
void UnQueue(Queue* q, char* x);
clientRecord CreateClientRecord();
clientRNode* CreateNode(clientRecord c);
void AddClient(clientRNode** list, clientRecord c);
void ModifyClientInfo(clientRNode** list, int numero_cmp, char* newName, int newstatus);
clientRNode* SearchClient(clientRNode* list, char* name, int numerocompte);
bool CheckSubscription(clientRNode* list, int numero_cmp);
void DisplayList(clientRNode* list);
void SubscribeToPremiem(clientRNode* list, char* name, int numaccount, int N, char services[][50]);
void UseService(clientRecord* c);
void DisplayHistory(Queue* q);
void AskAndConsumeAgain(clientRecord* c);

#endif