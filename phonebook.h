// Defining all Functions

#define LENGTH 45
#define HASH_TABLE_SIZE 26

typedef struct node
{
    char name[LENGTH + 1];
    unsigned long long int phno;
    struct node *next;
} Node;

Node *table[HASH_TABLE_SIZE];
unsigned long int contacts_inserted = 0;

bool hash_init(Node *t[])
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        t[i] = NULL; // Initializing every hash bucket to NULL
    }
    return true;
}

unsigned int hash(char *word)
{
    if (!isalpha(word[0]))
    {
        return HASH_TABLE_SIZE;
    }
    else
    {
        int ascii_value = (int)toupper(word[0]);
        return ascii_value = abs(65 - ascii_value);
    }
}

bool hash_check(int index)
{
    if (index >= HASH_TABLE_SIZE)
    {
        printf("\nInvalid Name: Entered name doesn't start with an alphabet\n");
        return false;
    }
    return true;
}

unsigned int search(char *Name)
{
    int index = hash(Name);
    if (!hash_check(index))
    {
        return -1; // If hashkey is invalid
    }
    for (Node *temp = table[index]; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->name, Name) == 0)
        {
            return 1; // If contact exists
        }
    }
    return 0; // If contact doesn't exist
}

bool load(char *name, long num)
{
    Node *nptr = malloc(sizeof(Node));
    if (nptr == NULL)
    {
        printf("Insufficient Memory : Can't allocate memory for new node\n");
        return false;
    }
    else
    {
        int index = hash(name);
        if (!hash_check(index))
        {
            return false;
        }
        strcpy(nptr->name, name);
        nptr->phno = num;
        nptr->next = table[index];
        table[index] = nptr;
        contacts_inserted++;
        return true;
    }
}

bool insert()
{
    char name[LENGTH + 1];
    unsigned long long int ph;
    printf("Name : ");
    scanf("%[^\n]%*c", name);
    printf("Phno : ");
    scanf("%llu", &ph);
    int res = search(name);
    if (res == 1) // If contact already exits return false
    {
        printf("Contact Name Already Exits in the table! Try Updating.");
        return false;
    }
    else if (res == 0)
    {
        if (!load(name, ph))
        {
            return false; // If not loaded - RETURN FALSE
        }
        return true;
    }
    return false;
}

bool delete (char *name)
{
    int index = hash(name);
    int res = search(name);
    if (res == 0 || res == -1)
    {
        return false;
    }
    if (strcmp(table[index]->name, name) == 0) // delete begin
    {
        Node *prev =  table[index];
        table[index] = table[index]->next;
        free(prev);
        contacts_inserted -= 1;
        return true;
    }
    else
    {
        Node *temp = table[index];
        Node *prev = NULL;
        while (temp != NULL)
        {
            if (strcmp(temp->name, name) == 0)
            {
                break;
            }
            prev = temp;
            temp = temp->next;
        }
        if (strcmp(temp->name, name) == 0)
        {
            prev->next = temp->next;
            free(temp);
            contacts_inserted -= 1;
            return true;
        }
    }
    return false;
}

unsigned long int count(void)
{
    return contacts_inserted;
}

bool unload(Node *t[])
{
    printf("\nUnloading Hash Table : \n.....\n.....\n\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        printf("Bucket %i: ", i);
        Node *temp = table[i];
        while (temp != NULL)
        {
            Node *prev = temp;
            temp = temp->next;
            printf("Node(%s, %llu) Freed\t", prev->name, prev->phno);
            free(prev);
        }
        printf("\n\n------------------------\n");
        printf("Bucket %i: FREED\n", i);
        printf("------------------------\n\n");
    }
    return true;
}

void display()
{
    printf("\nHash Table :\n....\n.....\n\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        printf("Bucket %i: ", i);
        if (table[i] == NULL)
        {
            printf("Empty");
        }
        else
        {
            for (Node *temp = table[i]; temp != NULL; temp = temp->next)
            {
                printf("(%s , %llu)", temp->name, temp->phno);
            }
        }
        printf("\n\n");
    }
}