#include <stdio.h>
#include <stdlib.h>
#include<string.h>

/*Following is the code to create DNA molecules using linked lists when the nucleotides
 of a  strand is given as input.The code slao has the functions to split dna molecule,delete/insert 
 nucleotides to the dna molecule and print the dna molecules.*/ 




struct dna_molecule**headx;//Global head pointer to the linkedlist that stores the head pointers to the molecules  

struct node//Defining data type for the nodes that acts as nucleotides
{
    char val;
    struct node *next;
    struct node *cross;
};


struct dna_molecule//Defining data type for the nodes that stores the head pointers to the dna molecules
{
    struct node ** ptr;
    struct dna_molecule*next;
    struct dna_molecule*previous;
    
};

void save_to_dna_molecule(struct node** head)//Function to save the head pointer to a dna molecule
{

    struct dna_molecule * new_node = NULL;
    new_node = (struct dna_molecule *)malloc(sizeof(struct dna_molecule));
    if (new_node == NULL)
    {
        printf("Failed to insert element. Out of memory");
    }

    struct dna_molecule* temp;
    
    if (*headx==NULL)
    {
    new_node->ptr=head;
    *headx = new_node;
    return;
    }
    else{
    temp = *headx;
    new_node->ptr =  head;
    while(temp->next!=NULL)
    {
     temp=temp->next; 
    }
    temp->next=new_node;
    }
};


struct node** get_dna_molecule(int id)//Function to retrieve the head pointer to a dna molecule 
{ 
  int i;
  struct dna_molecule* temp;
  temp = *headx;
  struct node**head;

  while (i<(id-1))
  {
      temp=temp->next;
      i++;
  }
  
  if (temp!=NULL)
  {
    head = temp->ptr;
  }
  else
  {
      return NULL;
  }
  
  
  
  return head;

}


int get_length(struct node* temp1)//Function to count the number of nucleotides that are given as input 
{
    int length=0;
    while(temp1!=NULL)
    {
        temp1 = temp1->next;
        length++;
    }
    return length;
}

void print_list(struct node **head)//Function to print the dna moecules 
{   
    int i;
    struct node* temp1 = *head;
    int count = get_length(temp1);
    while(temp1!=NULL)//While loop to print the first chain 
    {
        if( temp1->next!=NULL)
        {

        printf("%c-", temp1->val);
        temp1 = temp1->next;
        }
        else
        {

         printf("%c\n", temp1->val);
          temp1 = temp1->next;
        }
    }
    for(i = count-1; i>=0;i--)
    {
        printf("| ");
    }
    printf("\n");
    struct node* temp2 = *head;
    while(temp2!=NULL)//While loop to print the second chain
    {

        printf("%c", temp2->cross->val);
        if( temp2->next!=NULL)
        {
            printf("-");
        temp2 = temp2->next;
        }
        else
        {

         printf("\n");
          temp2 = temp2->next;
        }

    }


}


void create_chain(struct node** head,char value)//Function to create a dna chain(strand)
{
    struct node * new_node = NULL;

    new_node = (struct node *)malloc(sizeof(struct node));

    if (new_node == NULL)
    {
        printf("Failed to insert element. Out of memory");
    }

    new_node->val = value;
    if(head == NULL){
        
        printf("Head is null");
     return;
    }
    new_node->next = *head;
    *head = new_node;
}


char create_compl(char val )//Function to obtain the complementary nucleotide
    {

    if (val == 'A')
      return 'G';
    else if (val == 'G')
      return 'A';
    else if (val == 'T')
      return 'C';
    else  
     return 'T';

    }

void link_chain(struct node** head1,struct node** head2)//Function to link two dna strands that are complementary to each other
{

    struct node* temp1 = *head1;
    struct node* temp2 = *head2;
    temp1->cross=temp2;
    temp2->cross=temp1;
}

struct node*fill_chain(struct node* temp1)//Function to create a complementary chain from a parent chain recursively  
{   
    if(temp1==NULL)
    {
        return NULL;
    }
    struct node * new_node = NULL;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->val = create_compl(temp1->val);
    new_node->next = fill_chain(temp1->next);//New node are created recursively
    temp1->cross=new_node;
    new_node->cross=temp1;
    return new_node; 
}

void split(struct node** head,int i,int count)//Function to split the dna molecule and create a child dna

   { 
    struct node* temp1 = *head;
    struct node* temp2 = (*head)->cross;
    fill_chain(temp1);
    fill_chain(temp2);
    save_to_dna_molecule(&(temp2->cross));
    printf("\n");
    }

void insert(struct node**head,char value,int p)//Function to insert to a dna molecule in a desired position,
                                              //Here p is the position where the new nucleotide is inserted 
{ 
    int i=0; 
    struct node* temp = *head;
    struct node* temp2 = (*head)->cross;
    struct node * new_node = NULL;
    struct node * new_node2 = NULL;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node2 = (struct node *)malloc(sizeof(struct node));
    new_node->val = value;
    new_node2->val = create_compl(value);
    new_node->cross = new_node2;
    new_node2->cross = new_node;

  if (p==1)
  {
    new_node->next=temp;
    new_node2->next=temp2;

    *head=new_node;
   
  }
  else
  {
    while(i<p-2)
    {
        temp=temp->next;
        temp2=temp2->next;
        i++;
    }  

    new_node->next=temp->next;
    new_node2->next=temp2->next;
    temp->next=new_node;
    temp2->next=new_node2;

  }
 
  }

void delete(struct node**head,int p)//Function to delete a nucleotide at a certain position p
{ 
    int i=0; 
    struct node* temp = *head;
    struct node* temp2 = (*head)->cross;
    
  if (p==1)
  {
    temp=temp->next;
    temp2=temp2->next;
    free(*head);
    free((*head)->cross);
    *head=temp;
   
  }
  else
  {
    while(i<p-2)
    {
        temp=temp->next;
        temp2=temp2->next;
        i++;
    }  

    struct node* delete1 = temp->next;
    struct node* delete2 = temp2->next;
    temp->next=temp->next->next;
    temp2->next=temp2->next->next;
    free(delete1);
    free(delete2);

  }

  
  }

void print_menu(void)
{  
printf("  Menu:\n");    
printf("1.Create molecule \n");
printf("2.Insert\n");
printf("3.Delete\n");
printf("4.Split\n");
printf("5.Print molecule\n");
printf("6.Print all DNA molecules\n");

printf("6.Quit\n\n");
}

void main()
{
    struct node** head; 
    struct node** head2;    
    int count, i;
    headx = (struct dna_molecule **)malloc(sizeof(struct dna_molecule*));
    char val[300];//Array defined to store the nucleotides given as input 
    char valc[300];//Array defined to store the complementary nucleotides 
    int x;
    int id;
    int a=0;
    int p;
    int pr=0;
    print_menu();
    char nucleotide;

    struct node* temp;
    struct node* temp2;
    struct node**headpall;
    struct dna_molecule*dnamol_temp;
    do
    {    
        scanf("%d",&x);

        switch(x)
        {

            case 1:      
                printf("Enter the first chain of the DNA mlecule\n");
                printf("\n");
                scanf("%s", val);
                printf("\n");
                count = strlen(val);

                head = (struct node **)malloc(sizeof(struct node*));
                head2 = (struct node **)malloc(sizeof(struct node*));

                for (i = 0; i < count; i++)
                {
                    valc[i]= create_compl(val[i]) ;
                }

                for (i = count-1; i >=0; i--)
                {
                    create_chain(head,val[i]);
                    create_chain(head2,valc[i]);
                    link_chain(head,head2);           
                }       
                save_to_dna_molecule(head);//The head pointer to the dna molecule thathas been created is saved to a linkedlist
                a++;       
                printf("A molecule is created with molecule id %d \n", a );
                printf("\n");
                break;
                
            case 2:
                printf("Enter the molecule id\n");
                scanf("%d",&id);  
                printf("Enter the position\n");
                scanf("%d",&p);
                printf("Enter the nuclueotide\n");
                scanf(" %c", &nucleotide);
                struct node**headi= get_dna_molecule(id);//The head pointer to the dna molecule is returned when the molecule id is given as input
                insert(headi, nucleotide, p);
                break;
            case 3:
                printf("Enter the molecule id\n");
                scanf("%d",&id);  
                printf("Enter the position\n");
                scanf("%d",&p);
                struct node**headd= get_dna_molecule(id);
                delete(headd,p);
                break;
                
            case 4:
                printf("Enter the molecule id\n");
                scanf("%d",&id);      
                struct node**heads= get_dna_molecule(id);          
                split(heads,i,count); 
                a++; 
                printf("The molecule has been splitted and a new molecule with id %d is created\n",a);  
                break;
            case 5:
                printf("Enter the molecule id\n");
                scanf("%d",&id);
                struct node**headp= get_dna_molecule(id);          
                print_list(headp);
                printf("\n");
                break;
            case 6:
                dnamol_temp = *headx;
                while(dnamol_temp!=NULL)//While loop to print all the dna molecules 
                {      
                headpall = dnamol_temp->ptr;                                
                dnamol_temp = dnamol_temp->next;//Traversing through the linkedlist that stores allthe head pointers to various dna molecules          
                print_list(headpall);
                printf("\n");
                }
                break;    

        }

    } while (x!=7);
