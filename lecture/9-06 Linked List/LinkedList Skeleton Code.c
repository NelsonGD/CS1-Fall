
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
  int data;
  struct node* next;
}node;

node* create_node(item)
{
	node* item = malloc(sizeof(node));

	return item;
}

//this function takes an item and insert it in the linked list pointed by root.
//* Function returns a NULL Pointer which is the head of the list
node* insert_front(node* head, int item)
{
	// 1st: Create temporary node
	node * temp = create_node(item);

	// If you have nothing in the head, the head should be temp.
	if(head == NULL)
	{	
		head = temp; //! This will not change the original head
		// If you want to change the original head you need to return head.
		return head;
	}else{
		// temp needs to point to head for it to be in front
		temp->next = head;
		head = temp;
		return head;
	}


}

node* insert_sorted(node* root, int item)
{
  


}


//this function takes an item and insert it in the end of the linked list
node* insert_end(node* root, int item)
{
  
}






/*this function deletes the first occurrence of a given item from linked list.
it returns the updated/original root
*/
/* Function recieves an item, it wants to delete that item, and at the end returns head of the linked list*/
/* If you want to delete and item THAT IS THE HEAD then you need to change the head */
node* DelList(node* head, int item)
{
	// check if there's a linked list
	if(!head) // same as head == NULL
		return head;

	//? What if there was only one item in the least?

	// check if you have to delete the head of the linked list
	if(head->data == item)
	{
		node* temp = head; // Make a temp pointer to save address the temp, that way no mem leak happens
		head = head->next; // if you write this first then you lose the first item, this is a MEM LEAK
		free(temp);
		return head; // Return the new head, which was given to the item next to the head.
	}
	else // case when the head is not the item you want to delete
	{
		node* walker = head; // Item that will be traversing the list.

		//* You want to keep walking if there's an data to go to (not NULL) AND the data is not the one you want to delete
		while(walker->next != NULL && walker->next != item)
			walker = walker->next;
		
		// check if the item even exist in the list, by checking if the while loop went through all items.
		if(walker -> next == NULL) // if true it means that walker traversed to the end.
			return head;

		// You are going to access the item next to the one you want to delete.
		node* temp = walker->next; // holds the value you want to delete.
		walker -> next = walker -> next -> next; // holds value next to the one you want to delete.
		//* remember that WALKER is holding the value before the one you want to delete, and WALKER->NEXT holds the one after the item you want to delete.
		free(temp); // freeing the item you want to delete
		return head;

		//* This code works even if you want to delete the last item, it just makes walker->next = NULL which is fine.
	}
}

void display(node* t)
{
  printf("\nPrinting your linked list.......");

  while(t!=NULL)
  {
    printf("%d ", t->data);
    t= t->next;
  }

  printf("\n");	

}

int main()
{	
  //declare root apprpriately
  node* root = NULL; // Always initialize root to NULL when setting up a lit
	
	int ch,ele,v, del;
	while(1)
	{
		printf("\nMenu: 1. insert at the front, 2. insert at the end, 3. Delete, 5.  sorted insert 4. exit: ");
	    scanf("%d",&ch);
		if(ch==4)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if(ch==1)
		{
			printf("\nEnter data(an integer): ");
			scanf("%d",&ele);

      //call the funtion appropriately 
      display(root);	

		}
		if(ch==2)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d",&ele);

      //call the funtion appropriately 
      display(root);
			
		}
	  if(ch==3)
	  {
		  printf("\nEnter info which u want to DELETE: ");
		  scanf("%d",&del);
      ////call the funtion appropriately ______________________
      display(root);	  

		}

    if(ch==5)
		{
			printf("\nEnter data(an integer): ");
			scanf("%d",&ele);

     //call appropriately  
      display(root);	

		}
	}
  return 0;
}
