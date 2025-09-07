typedef struct Node {
    void* data;
    struct Node* next;   
} Node;


typedef struct LinkedList
{
    Node* head;
} LinkedList;
