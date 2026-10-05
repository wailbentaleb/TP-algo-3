# TP ALSDD - Système de Gestion des Abonnés & Services

Projet universitaire réalisé dans le cadre du module **ALSDD** (*Algorithmique et Structures de Données Dynamiques*) en langage C.

**Auteurs :** Wail Bentaleb & El Mahdi  
**Groupe :** 03  

---

## 📋 Présentation du Projet

Ce projet a pour objectif d'implémenter un système complet de gestion d'abonnés et de consommation de services en utilisant des **structures de données dynamiques** en C. 

Le système gère :
1. Une **liste simplement chaînée** pour enregistrer et parcourir les clients.
2. Une **pile dynamique (LIFO)** associée à chaque client pour stocker ses usages de services restants (services premium).
3. Une **file dynamique (FIFO)** associée à chaque client pour enregistrer l'historique des services consommés / achats en attente.

---

## 🗂️ Structure des Fichiers

| Fichier | Rôle |
|---|---|
| [`bib.h`](file:///c:/Users/wail%20bentaleb/Desktop/bentaleb%20wail%20%20el%20mahdi%20grp%2003/bib.h) | Fichier d'en-tête contenant la définition des structures (`Element`, `stack`, `Queue`, `clientRecord`, `clientRNode`) et les prototypes des fonctions. |
| [`fonction.c`](file:///c:/Users/wail%20bentaleb/Desktop/bentaleb%20wail%20%20el%20mahdi%20grp%2003/fonction.c) | Implémentation des primitives (Pile, File, Liste chaînée) et des règles de gestion des clients et services. |
| [`main1.c`](file:///c:/Users/wail%20bentaleb/Desktop/bentaleb%20wail%20%20el%20mahdi%20grp%2003/main1.c) | Programme principal fournissant un menu interactif en ligne de commande pour manipuler l'ensemble des fonctionnalités. |
| `rapport projet TP.pdf` | Rapport détaillé du projet de TP. |
| [`README.md`](file:///c:/Users/wail%20bentaleb/Desktop/bentaleb%20wail%20%20el%20mahdi%20grp%2003/README.md) | Guide d'utilisation et documentation technique du projet. |

---

## 🧩 Structures de Données Utilisées

### 1. Maillon Élémentaire (`Element`)
Sert de nœud de base pour les piles et les files :
```c
typedef struct Element {
    char info[50];
    struct Element* next;
} Element;
```

### 2. Pile (`stack`) - Principe LIFO
Gère les usages restants (`usages_Restants`). Le dernier service ajouté est le premier consommé :
```c
typedef struct stack {
    Element* top;
} stack;
```

### 3. File (`Queue`) - Principe FIFO
Gère l'historique des consommations (`achat_en_attente`). Les services consommés sont stockés dans l'ordre chronologique :
```c
typedef struct queue {
    Element* head;
    Element* tail;
} Queue;
```

### 4. Fiche Client (`clientRecord`)
Regroupe les informations du client ainsi que ses structures dynamiques :
```c
typedef struct clientRecord {
    char nom[20];
    int numero_compte;
    bool statut_abonnement;
    stack usages_Restants;
    Queue achat_en_attente;
    struct clientRecord* next;
} clientRecord;
```

### 5. Nœud de la Liste Principale (`clientRNode`)
Permet de chaîner l'ensemble des clients :
```c
typedef struct clientRNode {
    clientRecord client;
    struct clientRNode* next;
} clientRNode;
```

---

## ⚙️ Fonctionnalités Principales

### 📦 Primitives des Piles & Files
- **Pile :** `InitStack`, `Stack` (empiler), `Unstack` (dépiler), `StackEmpty`, `Summit`.
- **File :** `InitQueue`, `Queueq` (enfiler), `UnQueue` (défiler), `QueueEmpty`.

### 👥 Gestion des Clients
- **`CreateClientRecord`** : Initialise un enregistrement client avec une pile et une file vides.
- **`AddClient`** : Insère un nouveau client en tête de liste chaînée.
- **`SearchClient`** : Recherche un client par son nom ou son numéro de compte.
- **`ModifyClientInfo`** : Met à jour le nom ou le statut d'abonnement d'un client.
- **`CheckSubscription`** : Vérifie si un client possède un abonnement actif.
- **`DisplayList`** : Affiche l'ensemble des clients enregistrés.

### ⭐ Services Premium & Consommation
- **`SubscribeToPremiem`** : Passe le client en statut Premium et empile $N$ services dans sa pile `usages_Restants`.
- **`UseService`** : Dépile le prochain service disponible et l'ajoute à la file `achat_en_attente`.
- **`AskAndConsumeAgain`** : Propose à l'utilisateur de consommer ses services un par un tant que la pile n'est pas vide.
- **`DisplayHistory`** : Fonction récursive qui défile et affiche l'historique complet des services consommés.

---

## 🖥️ Menu Utilisateur (`main1.c`)

Au lancement du programme, un menu console interactif est proposé :
```text
--- Subscriber Management Menu ---
1- Create new clients
2- Display existing clients
3- Modify client information
4- Add premium services
5- Consume services
6- Exit
Choice: 
```

---

## 🚀 Compilation et Exécution

### Prérequis
- Un compilateur C tel que **GCC** (MinGW sous Windows, ou GCC sous Linux / macOS).

### 1. Compilation
Ouvrez un terminal dans le dossier du projet et exécutez :
```bash
gcc -Wall -Wextra main1.c fonction.c -o tp_alsdd.exe
```

### 2. Exécution
Sous Windows (PowerShell ou Invite de commandes) :
```powershell
.\tp_alsdd.exe
```
Sous Linux / macOS :
```bash
./tp_alsdd.exe
```

---

## 📌 Remarques & Améliorations Futures
- L'affichage de l'historique via `DisplayHistory` consomme les éléments de la file (libération mémoire par `UnQueue`).
- Possibilité d'ajouter la sauvegarde et le chargement des clients depuis un fichier texte ou binaire.
- Sécurisation des saisies utilisateur (`fgets` au lieu de `scanf`).
