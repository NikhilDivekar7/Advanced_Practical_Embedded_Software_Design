#include <stdio.h>
#include <stdlib.h>
#include "cmockLinkedList.h"

int destroy(struct info * head)
{
    enum my_enum status;
    if(head == NULL)
    return status = NULL_Pointer_passed;
    
	struct info * newInfo = head;
	struct info * temp;
	while(newInfo->myNodeData.next != NULL)
	{
		newInfo = newInfo->myNodeData.next;
		temp = newInfo->myNodeData.prev;
		free(newInfo);
		newInfo = temp;
	}
	head = NULL;
	return status = Destroyed;
}

int insert_at_end(struct info * head, int x)
{
    enum my_enum status;
    
    struct info * temp = head;
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    //struct info * temp1 = (struct info *)malloc(sizeof(struct info));
    newInfo -> data = x;
    newInfo -> myNodeData.next = NULL;
    if(head == NULL) 
    {
 		head = newInfo;
 		return status = NULL_Pointer_passed;
 	}
 	else{
	while(temp -> myNodeData.next != NULL)
	{
	    temp = temp -> myNodeData.next; // Go To last Node
	}
	
	newInfo -> myNodeData.next = NULL;
	newInfo -> myNodeData.prev = temp;
	temp -> myNodeData.next = newInfo;
	return status = inserted_at_end;
 	}
}

int insert_at_beginning(struct info * head, int x)
{
    enum my_enum status;
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    newInfo -> data = x;
    newInfo -> myNodeData.prev = NULL;
    newInfo -> myNodeData.next = NULL;
    if(head == NULL) 
    {
		head = newInfo;
		return status = NULL_Pointer_passed;
	}
	else
	{
	//head -> myNodeData.prev = newInfo;
	newInfo -> myNodeData.next = head; 
	//head -> myNodeData.next = NULL;
	head = newInfo;
	}
	return status = inserted_at_beginning;
}

int insertNode_at_position(struct info * head, int data, int position)
{
    int i;
    enum my_enum status;
    struct info * newNode, * temp;
    newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        printf("Unable to allocate memory.");
        return status = NULL_Pointer_passed;
    }
    else if(position == 1)
    {
        insert_at_beginning(head, data);
        return status = inserted_at_beginning;
    }
     else
    {
        newNode -> data = data; // Link data part
        newNode -> myNodeData.next = NULL;
        temp = head;

        for(i=1; i<position-1; i++)
        {
            temp = temp ->myNodeData.next;
            if(temp == NULL)
                break;
        }

        if(temp != NULL)
        {
            newNode->myNodeData.next = temp->myNodeData.next; 
            temp->myNodeData.next = newNode;
            printf("Data inserted\n");
        }
        else
        {
            printf("Data not inserted\n");
        }
    }
    return status = inserted_in_middle;
}

int delete_at_beginning(struct info * head)
{
    enum my_enum status;
    if(head == NULL)
    {
        printf("Unable to delete");
        return status = NULL_Pointer_passed;
    }
    else
    {
        struct info * temp;
        temp = head;
        head = head -> myNodeData.next;
        head -> myNodeData.prev = NULL;
        free(temp);
    }
    return status = deleted_at_beginning;
}

int delete_at_end(struct info * head)
{
    enum my_enum status;
    struct info * temp = head;
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    if(head == NULL) 
    {
		head = newInfo;
		return status = NULL_Pointer_passed;
	}
	while(temp -> myNodeData.next != NULL)
	{
	    temp = temp -> myNodeData.next; // Go To last Node
	}
	//newInfo = temp;
	//temp -> myNodeData.next = NULL;
	//temp -> myNodeData.prev = temp;
	newInfo = temp-> myNodeData.prev;
	newInfo -> myNodeData.next = NULL;
	free(temp);
	return status = deleted_at_end;
}

int delete_from_position(struct info * head, int position)
{
    enum my_enum status;
    int i;
    struct info * newNode, * temp;
    newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        return status = NULL_Pointer_passed;
    }
    else
    {
        temp = head;
        newNode = head;
        if(position == 1)
        {
            head = head -> myNodeData.next;
            free(temp);
        }
        else
        {
            for(i=1; i <= position; i++)
            {
                temp = temp -> myNodeData.next;
            }
            
            for(i=1; i < position-1; i++)
            {
                newNode = newNode -> myNodeData.next;
            }
            
            //printf("%d", *newNode->myNodeData.next);
            //temp = temp -> myNodeData.next;
            newNode -> myNodeData.next = temp;
            temp -> myNodeData.prev = newNode;
        }
    }
    return status = deleted_in_middle;
}

void Print(struct info * head)
{
    enum my_enum status;
	struct info * temp = head;
	printf("List is: ");
	while(temp != NULL) 
	{
		printf("%d ",temp->data);
		temp = temp->myNodeData.next;
    }
	printf("\n");
}

int size(struct info * head)
{
    enum my_enum status;
    int count;
    struct info * temp = head;
    while(temp != NULL)
    {
        temp = temp -> myNodeData.next;
        count++;
    }
    return status = got_size;
}