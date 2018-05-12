void destroy(struct info * head)
{
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
}

struct info * insert_at_end(struct info * head, int x)
{
    struct info * temp = head;
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    //struct info * temp1 = (struct info *)malloc(sizeof(struct info));
    newInfo -> data = x;
    newInfo -> myNodeData.next = NULL;
    if(head == NULL) 
    {
 		head = newInfo;
 		return;
 	}
 	else{
	while(temp -> myNodeData.next != NULL)
	{
	    temp = temp -> myNodeData.next;
	}
	
	newInfo -> myNodeData.prev = temp;
	temp -> myNodeData.next = newInfo;
	newInfo -> myNodeData.next = NULL;
	return head;
 	}
}

struct info * insert_at_beginning(struct info * head, int x)
{
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    newInfo -> data = x;
    newInfo -> myNodeData.prev = NULL;
    newInfo -> myNodeData.next = NULL;
    if(head == NULL) 
    {
		head = newInfo;
		return;
	}
	else
	{
	//head -> myNodeData.prev = newInfo; 
	newInfo -> myNodeData.next = head; 
	//head -> myNodeData.next = NULL;
	head = newInfo;
	}
	return head;
}

struct info * insert_at_position(struct info * head, int data, int position)
{
    int i;
    struct info * newNode, * temp;
    newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        printf("Unable to allocate memory.");
    }
    else if(position == 1)
    {
        insert_at_beginning(head, data);
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

            printf("data inmserted\n");
        }
        else
        {
            printf("data not inserted\n");
        }
    }
    return head;
}

struct info * delete_at_beginning(struct info * head)
{
    if(head == NULL)
    {
        printf("Unable to delete node");
    }
    else
    {
        struct info * temp;
        temp = head;
        head = head -> myNodeData.next;
        head -> myNodeData.prev = NULL;
        free(temp);
    }
    return head;
}

struct info * delete_at_end(struct info * head)
{
    struct info * temp = head;
    struct info * newInfo = (struct info *)malloc(sizeof(struct info));
    if(head == NULL) 
    {
		head = newInfo;
		return;
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
	return head;
}

struct info * delete_from_position(struct info * head, int position)
{
    int i;
    struct info * newNode, * temp;
    newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        printf("Unable to delete.");
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
    return head;
}

void Print(struct info * head)
{
	struct info * temp = head;
	printf("list is: ");
	while(temp != NULL) 
	{
		printf("%d ",temp->data);
		temp = temp->myNodeData.next;
    }
	printf("\n");
}

int size(struct info * head)
{
    int count;
    struct info * temp = head;
    while(temp != NULL)
    {
        temp = temp -> myNodeData.next;
        count++;
    }
    return count;
}
