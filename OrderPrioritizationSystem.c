#include<stdio.h>
#include<stdlib.h>

struct Order
{
    char list[10][15];
    struct Order* next;
    int size;
};
struct Order* head;



void takeOrder()
{
    struct Order* ptr = (struct Order*)malloc(sizeof(struct Order));
    
    printf("\nNumber of items: ");
    scanf("%d", &ptr->size);

    for(int i=0 ; i<ptr->size ; i++)
    {
        printf("\n%d. ",i+1);
        scanf("%s",ptr->list[i]);
    }

    printf("Order has been added to %d position", addOrder(ptr));
}

int addOrder(struct Order* ptr)
{
    if(head==NULL)
    {
        head = ptr;
        ptr->next = NULL;
    }
    else if(head->next == NULL)
    {
        if(head->size < ptr->size)
        {
            head->next = ptr;
            ptr->next = NULL;
        }
        else
        {
            ptr->next = head;
            ptr = head; 
        }
    }
    else
    {
        struct Order* temp;
        temp = head;
        
        if(temp->size > ptr->size)
        {
            ptr->next = temp;
            head = ptr;   
        }
        else
        {
            while(temp->next!=NULL)
            {
                if(temp->next->size < ptr->size)
                {
                    temp = temp->next;
                }
                else if(temp->next->size == ptr->size)
                {
                    ptr->next = temp->next->next;
                    temp->next->next = ptr;
                }
                else
                {
                    ptr->next = temp->next;
                    temp->next = ptr;
                }

            }

        }

        
        
    }
    
    

}
