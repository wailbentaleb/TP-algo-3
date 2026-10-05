#include "bib.h"

int main() {
    //clientRecord :
    clientRNode* crn = NULL;
    int choice;
    int compte_counter = 1;

    do {
        printf("\n--- Subscriber Management Menu ---\n");
        printf("1- Create new clients\n");
        printf("2- Display existing clients\n");
        printf("3- Modify client information\n");
        printf("4- Add premium services\n");
        printf("5- Consume services\n");
        printf("6- Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                int nn;
                printf("Enter number of clients: ");
                scanf("%d", &nn);
                for(int i = 0; i < nn; i++) {
                    clientRecord c = CreateClientRecord();
                    printf("Name of client %d: ", i+1);
                    scanf("%s", c.nom);
                    c.numero_compte = compte_counter++;
                    AddClient(&crn, c);
                    printf("Added with ID: %d\n", c.numero_compte);
                }
                break;
            }
            case 2:
                DisplayList(crn);
                break;
            case 3: {
                int id, stat; char name[20];
                printf("ID to modify: "); scanf("%d", &id);
                printf("New name: "); scanf("%s", name);
                printf("Status (1/0): "); scanf("%d", &stat);
                ModifyClientInfo(&crn, id, name, stat);
                break;
            }
            case 4: {
                char name[20]; int id, N;
                printf("ID: "); scanf("%d", &id);
                printf("Name: "); scanf("%s", name);
                printf("How many services? "); scanf("%d", &N);
                char srv[N][50];
                for(int i=0; i<N; i++) {
                    printf("Service %d: ", i+1);
                    scanf(" %[^\n]", srv[i]);
                }
                SubscribeToPremiem(crn, name, id, N, srv);
                break;
            }
            case 5: {
                char name[20]; int id;
                printf("ID: "); scanf("%d", &id);
                printf("Name: "); scanf("%s", name);
                clientRNode* f = SearchClient(crn, name, id);
                if(f) AskAndConsumeAgain(&f->client);
                break;
            }
        }
    } while(choice != 6);

    return 0;
}