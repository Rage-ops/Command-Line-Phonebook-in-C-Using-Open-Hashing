## Open Hashing (Separate Chaining)
It is a collison resolution technique.

To handle the collision:
  * Keys are stored in linked lists attached to cells of a hash table.

## Functions:

* <strong>bool hash_init(Node *t[])</strong> : Initializes each head of linked list in the hash table to NULL.
* <strong>unsigned int hash(char *word)</strong> : Hash function which takes a string as argument and returns hash_key.
* <strong>bool hash_check(int index)</strong> : Checks whether an index is a valid hash_key or not.
* <strong>unsigned int search(char *Name)</strong> : Checks whether a contact exists in the hash table or not.
* <strong>bool load(char *name, unsigned long long int num)</strong> : Accepts contact name and phone number as arguments and loads it into the hash table.
* <strong>bool insert()</strong> : Reads contact name and phone number from user and invokes load() function.
* <strong>bool delete (char *name)</strong> : Accepts contact name as argument and deletes it from the hash table.
* <strong>unsigned long int count(void)</strong> : Returns total number of contacts.
* <strong>bool unload(Node *t[])</strong> : Frees hash table.
* <strong>void display()</strong> : Displays hash table.
