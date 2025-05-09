#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <curl/curl.h>
#include <windows.h>

#define MAX_VERTICES 10
#define INF INT_MAX


 char locationNames[MAX_VERTICES][20] = {
    "Kotturpuram", "Guindy", "Tambaram", "Velachery", "Perungudi",
    "Tharamani", "Thiruvanmiyur", "Adyar", "Saidapet", "T_Nagar"
};


//Stack
typedef struct Stack {
    int cargo_id;
    float weight;
    int from;
    int to;
    struct Stack* next;
} Stack;


void push(Stack** top, int cargo_id, float weight, int from, int to) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    newStack->cargo_id = cargo_id;
    newStack->weight = weight;
    newStack->from = from;
    newStack->to = to;
    newStack->next = *top;
    *top = newStack;
    printf("Cargo id %d is pushed for delivery into pending deliveries stack \n",cargo_id);
}


int pop(Stack** top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    Stack* temp = *top;
    int cargo_id = temp->cargo_id;
    *top = (*top)->next;
    free(temp);
    printf("Cargo with ID: %d delivered (popped from delivery stack).\n\n", cargo_id);
    return cargo_id;
}


void displayStack(Stack* top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }

    printf("\nPending Deliveries - Stack contents (Last In, First Out):\n");
    while (top != NULL) {
        printf("Cargo ID: %d\n", top->cargo_id);
        printf("Weight: %.2f\n", top->weight);
        printf("From: %s\n", locationNames[top->from]); 
        printf("To: %s\n", locationNames[top->to]); 
        printf("----------------------------\n");
        top = top->next;
    }
}


int peek(Stack* top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    return top->cargo_id; 
}


//Binary Search Tree
typedef struct TreeNode {
    int cargo_id;
    float weight;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int cargo_id, float weight) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->cargo_id = cargo_id;
    newNode->weight = weight;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* insertBST(TreeNode* root, int cargo_id, float weight) {
    if (root == NULL) {
        return createNode(cargo_id, weight);
    }
    if (cargo_id < root->cargo_id) {
        root->left = insertBST(root->left, cargo_id, weight);
    } else {
        root->right = insertBST(root->right, cargo_id, weight);
    }
    return root;
}

void displayBST(TreeNode* root) {
    if (root == NULL) return;
    displayBST(root->left);
    printf("Cargo ID: %d, Weight: %.2f\n", root->cargo_id, root->weight);
    displayBST(root->right);
}
TreeNode* searchBST(TreeNode* root, int cargo_id) {
    if (root == NULL || root->cargo_id == cargo_id) {
        return root; 
    }
    if (cargo_id < root->cargo_id) {
        return searchBST(root->left, cargo_id); 
    }
    return searchBST(root->right, cargo_id); 
}

TreeNode* findMin(TreeNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}
void printSearchResult(TreeNode* result) {
    if (result != NULL) {
        printf("CargoBox found: cargo_id = %d, weight = %.2f\n", result->cargo_id, result->weight);
    } else {
        printf("CargoBox with the given cargo_id not found.\n");
    }
}
TreeNode* deleteBST(TreeNode* root, int cargo_id) {
    if (root == NULL) {
        return root;
    }

   
    if (cargo_id < root->cargo_id) {
        root->left = deleteBST(root->left, cargo_id);
    } else if (cargo_id > root->cargo_id) {
        root->right = deleteBST(root->right, cargo_id); 
    } else {
     
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp; 
        }

        
        TreeNode* temp = findMin(root->right);
        root->cargo_id = temp->cargo_id; 
        root->weight = temp->weight; 
        root->right = deleteBST(root->right, temp->cargo_id); 
    }
    return root;
}
int _print_t(TreeNode *tree, int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;
 
    if (!tree) return 0;
 
    sprintf(b, "(%03d)", tree->cargo_id);
 
    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
 
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
 
    if (depth && is_left) {
        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width / 2 + i] = '-';
        s[depth - 1][offset + left + width / 2] = '+';
    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width / 2 + i] = '-';
        s[depth - 1][offset + left + width / 2] = '+';
    }
 
    return left + width + right;
}
 
void print_t(TreeNode *tree) {
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");
 
    _print_t(tree, 0, 0, 0, s);
 
    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}



//Graph  


typedef struct Edge {
    int from;
    int to;
    struct Edge* next;
    int weight;
} Edge;


typedef struct Graph {
    Edge* edges;
    int numVertices;
} Graph;


void initializeGraph(Graph* g, int numVertices) {
    g->edges = NULL;
    g->numVertices = numVertices;
}


Edge* newEdge(int from, int to, int weight) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->from = from;
    edge->to = to;
    edge->weight = weight;   
    edge->next = NULL;
    return edge;
}

void addEdge(Graph* g, int from, int to, int weight) {
    Edge* edge = newEdge(from, to, weight);
    edge->next = g->edges;
    g->edges = edge;
}


void generateGraphviz(Graph* g, char* graphStr) {
    Edge* current = g->edges;
    strcat(graphStr, "digraph G {\n"); 

  
    strcat(graphStr, "    label=\"Cargo Service Locations Map\";\n");
    strcat(graphStr, "    labelloc=top;\n");
    strcat(graphStr, "    fontname=\"Arial\";\n");
    strcat(graphStr, "    fontsize=24;\n");
    strcat(graphStr, "    fontweight=bold;\n");

    while (current) {
        char edge[200];
      
        sprintf(edge, "    \"%s\" -> \"%s\" [label=\"%d km\"];\n",
                locationNames[current->from],
                locationNames[current->to],
                current->weight);
        strcat(graphStr, edge);
        current = current->next;
    }

    strcat(graphStr, "}\n");
}


void urlencode(const char* src, char* dest) {
    char* p = dest;
    while (*src) {
        if (isalnum(*src) || *src == '-' || *src == '_' || *src == '.' || *src == '~') {
            *p++ = *src;
        } else {
            sprintf(p, "%%%02X", (unsigned char)*src);
            p += 3;
        }
        src++;
    }
    *p = '\0';
}


size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}


void createGraphImage(Graph* g) {
    CURL* curl;
    CURLcode res;
    FILE* fp;
    const char* outfilename = "D:/C Projects/C-CargoDSManager/Map images/Locations_Map.png";

  
    char graphvizStr[2000] = "";
    generateGraphviz(g, graphvizStr);
    
   
    char encodedGraphviz[4000];
    urlencode(graphvizStr, encodedGraphviz);

   
    char url[5000] = "https://quickchart.io/graphviz?format=png&graph=";
    strcat(url, encodedGraphviz);

  
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename, "wb");

      
        if (fp == NULL) {
            perror("Error opening file");
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Graph image created as '%s'\n", outfilename);
        }

        fclose(fp);
        curl_easy_cleanup(curl);
        ShellExecute(NULL, "open", outfilename, NULL, NULL, SW_SHOW);
    }
}

int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}
void generateGraphvizWithPath(Graph* g, char* graphStr, int parent[], int src, int dest, int totalDistance, char locationNames[][20]) {
   
    sprintf(graphStr, "digraph G {\n");
   
    char labelStr[200];
    sprintf(labelStr, "label=\"Shortest path between %s and %s (total distance %d km)\";\n", locationNames[src], locationNames[dest], totalDistance);
    strcat(graphStr, labelStr);

  
    strcat(graphStr, "labelloc=\"t\";\nfontsize=14;\n");

    Edge* current = g->edges;
    while (current) {
        char edge[150];
        int isPathEdge = 0;

        
        int v = dest;
        while (v != src && v != -1) {
            if (parent[v] == current->from && v == current->to) {
                isPathEdge = 1;
                break;
            }
            v = parent[v];
        }

  
        if (isPathEdge) {
            sprintf(edge, "    \"%s\" -> \"%s\" [label=\"%d km\", color=red, penwidth=2.0];\n", 
                    locationNames[current->from], locationNames[current->to], current->weight);
        } else {
            sprintf(edge, "    \"%s\" -> \"%s\" [label=\"%d km\"];\n", 
                    locationNames[current->from], locationNames[current->to], current->weight);
        }
        strcat(graphStr, edge);
        current = current->next;
    }

  
    strcat(graphStr, "}\n");
}



void printShortestPath(int src, int dest, int* parent) {
    if (dest == -1) {
        printf("No path from %s.\n", locationNames[src]);
        return;
    }


    if (dest == src) {
        printf("%s", locationNames[src]);
        return;
    }


    printShortestPath(src, parent[dest], parent);
    printf(" -> %s", locationNames[dest]);
}

void dijkstraAndVisualize(Graph* g, int src, int dest) {
    int V = g->numVertices;
    int dist[V];
    int sptSet[V];
    int parent[V];


    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = 1;

        Edge* edge = g->edges;
        while (edge != NULL) {
            if (edge->from == u) {
                int v = edge->to;
                if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + edge->weight < dist[v]) {
                    dist[v] = dist[u] + edge->weight;
                    parent[v] = u;
                }
            }
            edge = edge->next;
        }
    }

    if (dist[dest] == INT_MAX) {
        printf("No path exists between %s and %s.\n", locationNames[src], locationNames[dest]);
        return;
    }

   
    printf("Shortest path from %s to %s: ", locationNames[src], locationNames[dest]);
    printShortestPath(src, dest, parent);
    printf("\nTotal distance between the two service locations: %d\n", dist[dest]);

  
    char graphvizStr[1000];
    generateGraphvizWithPath(g, graphvizStr, parent, src, dest, dist[dest], locationNames);


    char encodedGraphviz[2000];
    urlencode(graphvizStr, encodedGraphviz);

    char url[3000] = "https://quickchart.io/graphviz?format=png&graph=";
    strcat(url, encodedGraphviz);

    CURL* curl;
    CURLcode res;
    FILE* fp;
    const char* outfilename = "D:/C Projects/C-CargoDSmanager/Map images/shortest_path.png";

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename, "wb");
        if (fp == NULL) {
            perror("Error opening file");
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        fclose(fp);
        curl_easy_cleanup(curl);
        printf("Graph image with shortest path created as '%s'\n", outfilename);

        ShellExecute(NULL, "open", outfilename, NULL, NULL, SW_SHOW);
    }
}


int main() {
    Stack* cargoStack = NULL;
    TreeNode* cargoBST = NULL;
    Graph g;
    initializeGraph(&g, MAX_VERTICES);



addEdge(&g, 0, 1, 15);  
addEdge(&g, 1, 2, 10);  
addEdge(&g, 2, 3, 14); 
addEdge(&g, 3, 4, 6);   
addEdge(&g, 4, 5, 11); 
addEdge(&g, 5, 6, 7);   
addEdge(&g, 6, 7, 13); 
addEdge(&g, 7, 8, 8);  
addEdge(&g, 8, 0, 20);  


addEdge(&g, 1, 0, 15);  
addEdge(&g, 2, 1, 10);  
addEdge(&g, 3, 2, 14);  
addEdge(&g, 4, 3, 6);   
addEdge(&g, 5, 4, 11);  
addEdge(&g, 6, 5, 7);   
addEdge(&g, 7, 6, 13);  
addEdge(&g, 8, 7, 8);  
addEdge(&g, 0, 8, 20);  



   
    cargoBST = insertBST(cargoBST, 50, 10.5);
    cargoBST = insertBST(cargoBST, 30, 12.3);
    cargoBST = insertBST(cargoBST, 70, 15.0);
    cargoBST = insertBST(cargoBST, 20, 8.5);
    cargoBST = insertBST(cargoBST, 40, 9.0);
    cargoBST = insertBST(cargoBST, 60, 14.0);
    cargoBST = insertBST(cargoBST, 80, 16.2);
    cargoBST = insertBST(cargoBST, 10, 7.0);
    cargoBST = insertBST(cargoBST, 25, 8.0);
    cargoBST = insertBST(cargoBST, 35, 9.5);
    cargoBST = insertBST(cargoBST, 45, 10.0);
    cargoBST = insertBST(cargoBST, 55, 13.0);
    cargoBST = insertBST(cargoBST, 65, 14.5);
    cargoBST = insertBST(cargoBST, 75, 15.5);
    cargoBST = insertBST(cargoBST, 85, 17.0);

int y;
printf("Proceed with existing Map(0) or create a new one(1)? \n");
scanf("%d",&y);
if (y == 1) {
      
        initializeGraph(&g, MAX_VERTICES);
        printf("Proceed now with adding new routes and locations \n");
    }

	
    int choice;
    do {
    	printf("\t\t----------CARGO SERVICE MANAGEMENT SYSTEM----------");
        printf("\nMenu:\n");
        printf("1. Push CargoBox to Stack\n");
        printf("2. Pop CargoBox from Stack\n");
        printf("3.Peek the recently stocked CargoBox (top CargoBox) from stack\n");
        printf("4. Display All CargoBox Stack\n");
        printf("5. Insert Cargo id  to BST\n");
        printf("6.Delete a Cargo in BST\n");
        printf("7.Search a Cargo in BST\n");
        printf("8. Display BST(inorder traversal way.)\n");
        printf("9. Display BST(Actual tree outlook)\n");
        printf("10. Add a route between two service locations (Add an edge to the graph) \n");
        printf("11. Display all the routes.(Display all the graph edges)\n");
        printf("12.View the Working Locations Map (Create Graph  Image)\n");
        printf("13.Find shortest path to between two service locations (using Dijkstras algorithm  )\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        int id,from,to, priority,n,w,z,f,t;
        char origin[100], dest[100];
        float weight;

        switch (choice) {
            case 1:
            	printf("Available Locations:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("%d. %s\n", i , locationNames[i]);
    }
                printf("Enter Cargo ID to push to stack: ");
                scanf("%d", &id);
                printf("Enter weight to push to stack: ");
                scanf("%f", &weight);
                printf("Enter from location to push to stack: ");
                scanf("%d", &f);
                printf("Enter to location to push to stack: ");
                scanf("%d", &t);
                
                
                push(&cargoStack, id,weight,f,t);
                break;
            case 2:
                id = pop(&cargoStack);
                if (id != -1) {
                    printf("Popped Cargo ID: %d\n", id);
                }
                break;
            case 3:
            	printf("The recently stocked CargoBox (top CargoBox) from stack is Cargo id : %d \n",peek(cargoStack));
            	break;
            case 4:
                displayStack(cargoStack);
                break;
            
            case 5:
                printf("Enter Cargo ID and Weight to insert into BST: ");
                scanf("%d %f", &id, &weight);
                cargoBST = insertBST(cargoBST, id, weight);
                break;
            case 6:
            	printf("Enter Cargo ID to delete from  BST: ");
            	scanf("%d", &id);
                cargoBST = deleteBST(cargoBST, id);
                break;
            case 7 : 
            	printf("Enter the Cargo id to search and get its weight :\n");
            	scanf("%d", &id);
   				 TreeNode* result = searchBST(cargoBST,id);
    			printSearchResult(result);
    			break;
            case 8:
                displayBST(cargoBST);
                break;
            case 9 :
            	printf("The Binary Search tree with id along with corresponding weights :\n");
            	print_t(cargoBST);
            	break;
            
            case 10:
            	printf("Available Locations:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("%d. %s\n", i , locationNames[i]);
    }
                printf("Enter from and to service location code (denoted in unique numbers assigned ) , and distance (in KMs rounding off to nearest integer ) between the locations: \n");
                scanf("%d %d %d", &from, &to,&w );
                addEdge(&g, from, to, w);
                break;
            case 11:
                printf("Graph Edges:\n");
                Edge* e = g.edges;
                while (e) {
                    printf("%d -> %d : %d\n", e->from, e->to,e->weight);
                    e = e->next;
                }
                break;
            case 12:
                createGraphImage(&g);
                break;
            case 13 :
            		printf("Available Locations:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("%d. %s\n", i , locationNames[i]);
    }
            	printf("Enter the starting location and destination location code :\n");
            	scanf("%d %d",&n,&z);
            	
            	dijkstraAndVisualize(&g, n,z);
            	break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
