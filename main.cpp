// kad_video.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdlib.h>

using namespace std;


struct list_item{
private: int Key;
    char *Value;

public:
    list_item(int k, char *v)
    {
        Key = k;
        Value = v;
    }
    int key(){
        return Key;
    }

    char *value(){
        return Value;
    }

};

template <class Item, typename Key>
class ST{
private:
    Item *nullItem;

    struct node {
        Item *item; node* next;
        node(Item *x, node* t){
            item = x; next = t;
        }
    };
    typedef node *link;
    int N,M;
    link *heads;
    Item *searchR(link t, Key v)
    {
        if (!t) return NULL;
        if (t->item->key() == v) return t->item;
        return searchR(t->next, v);
    }

    Item *printR(link t)
    {
        if (t == NULL) return NULL;
        cout << t->item->key() << " ; " << t->item->value() << "\n";
        return printR(t->next);
    }

    //inline int hash (Key key, int M){
    //    return ((unsigned)key)/100;
    //}

    inline int hash (Key key, int M){
        return ((unsigned)key)%M;
    }
public:
    ST(int maxN){
        N = 0; M=maxN/5;
        heads = new link[M];
        for (int i=0; i<M;i++) heads[i]=NULL;
    }

    int count(){ return N; }

    Item *search(Key v){
       return searchR(heads[hash(v,M)], v);
    }

    void print(){
        for (int i=0; i<M; i++) {
            cout << "heads[" <<i <<"]:\n";
            printR(heads[i]);
        }
    }
    void insert(Item *x){
        int i = hash(x->key(),M);
        heads[i] = new node(x, heads[i]);
        N++;
    }
};


int main(int argc, char* argv[])
{
    ST <list_item,int> my_list(100);
    list_item *new_item;

    for (int i=0;i<100;i++){
    new_item =new list_item(i*11,"abcd");
    my_list.insert(new_item);
    }

    my_list.print();

    list_item *found=my_list.search(418);
    if (found)  cout << found->value() << "\n";
    else cout << "nothing\n";

    return 0;
}
