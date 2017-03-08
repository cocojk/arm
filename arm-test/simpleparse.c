#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

 namespace std;


struct inst {
    struct inst* next,  *prev;
    int assembly;
    int count;
};

int totalNum;
int differentNum;
char buffer [1000];
struct inst* head = NULL;

void INIT_LIST_HEAD (struct inst* list)
{
    list->next = list;
    list->prev = list;
}

void __list_add (struct inst* new, struct inst* prev, struct inst* next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}


void list_add (struct inst* new, struct inst* head)
{
        __list_add (new, head, head->next);
}




void _register_instrcution (int assembly)
{
    #ifdef DEBUG
        printf("%x\n",assembly);
    #endif

    if (head == NULL)
    {
        differentNum++;
        head = (struct inst*) malloc (sizeof(struct inst));
        head->assembly = assembly;
        head->count = 1;
        INIT_LIST_HEAD(head);
        return;
    }

    
    struct inst* current = head;
    
    int index;
    while (1)
    {
        
        if (current->assembly == assembly)
        {
            current-> count ++;
            break;
        }

        current = current->next;

        if (current == head)
        {
            differentNum++;
            current = (struct inst*) malloc (sizeof(struct inst));
            current->assembly = assembly;
            current->count = 1;
            list_add (current,head);            

            break;
        }
    }
}
        
void register_instruction (int index)
{
    
   
    int assembly = 0;
    char temp;
    int i;
    totalNum++;

    for (i = 0; i < 8; i++)
    {
        temp = buffer[index+i-7];
        if ( (temp >= '0' && temp <= '9'))
            assembly = assembly*16 + (temp-48);
        else 
            assembly = assembly*16 + (temp-87); 

    }


    _register_instrcution (assembly);

}


int parse (void)
{

        if (fgets(buffer,1000,stdin) == NULL)
            return 0;

        if (buffer[0] == '\n')
        {
            if (fgets(buffer,1000,stdin) == NULL)
                return 0;
            return 1;
        }
    
        int count = 0;
        int i;
        for (i = 0; buffer[i] != '\n'; i++)
        {
            if ( (buffer[i] >= '0' && buffer[i] <= '9') ||  (buffer[i] >= 'a' && buffer[i] <= 'f' ))
                count ++;
            else 
                count = 0;

            if (count == 8)
            {  
                if ( buffer[i+1] != ':' )
                {    register_instruction(i);
                    return 1;
                }
                count = 0;
            }
        }

        return 1;


}

void showResult (void)
{
    struct inst* current = head;
    
    int* buffer = (int*) malloc(sizeof(int)*differentNum);

    printf("%x : %d\n",current->assembly,current->count);
    
    current = current->next;
    while (current != head)
    {
        printf("%x : %d\n",current->assembly,current->count);
        current = current->next;
    }
    printf("total num : %d differentNum : %d\n",totalNum,differentNum);
}

    
int main (void)
{
    int i;
    printf("start \n");
    
    for (i = 0; i < 7; i++)
        fgets(buffer,1000,stdin);

    while(1)
    {
        if (!parse())
            break;
    }
    
    showResult();
    return 0;
}

