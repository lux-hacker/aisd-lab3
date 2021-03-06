#include "Table.h"

void add(Table* table, Item* item){
    // Add to KeySpace1
    KeySpace1* node = (KeySpace1*) malloc(sizeof(KeySpace1));
    node->key = (char*) calloc(strlen(item->key1) + 1, sizeof(char));
    strcpy(node->key, item->key1);
    node->data = item;
    node->next = table->keySpace1;
    table->keySpace1 = node;

    // Add to KeySpace2
    int hashKey = hash(item->key2, table->size2);
    if(table->keySpace2[hashKey].data == NULL){
        table->keySpace2[hashKey].data = item;
        table->keySpace2[hashKey].key = (char*) calloc(strlen(item->key2) + 1, sizeof(char));
        strcpy(table->keySpace2[hashKey].key, item->key2);
        table->keySpace2[hashKey].release = 1;
    } else {
        if(strcmp(table->keySpace2[hashKey].key, item->key2) == 0){
            KeySpace2* buf = (KeySpace2*) malloc(sizeof(KeySpace2));
            buf->next = table->keySpace2[hashKey].next;
            buf->release = table->keySpace2[hashKey].release;
            buf->data = table->keySpace2[hashKey].data;;
            buf->key = (char*) calloc(strlen(table->keySpace2[hashKey].key) + 1, sizeof(char));
            strcpy(buf->key, table->keySpace2[hashKey].key);
            free(table->keySpace2[hashKey].key);
            table->keySpace2[hashKey].next = buf;
            table->keySpace2[hashKey].key = (char*) calloc(strlen(item->key2) + 1, sizeof(char));
            strcpy(table->keySpace2[hashKey].key, item->key2);
            table->keySpace2[hashKey].data = item;
            table->keySpace2[hashKey].release = buf->release + 1;
        } else {
            KeySpace2* ks = table->keySpace2 + hashKey;
            while (ks->next != NULL && strcmp(ks->next->key, item->key2) != 0) ks = ks->next;
            KeySpace2 *elem = (KeySpace2 *) malloc(sizeof(KeySpace2));
            elem->data = item;
            if(ks->next == NULL){
                elem->release = 1;
            } else {
                elem->release = ks->next->release + 1;
            }
            elem->next = ks->next;
            ks->next = elem;
            elem->key = (char*) calloc(strlen(item->key2) + 1, sizeof(char));
            strcpy(elem->key, item->key2);
        }
    }
}