#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void   no_of_inputs(FILE *file);
void   no_of_outputs(FILE *file);
void   check(FILE *file);
struct signal *addSignal();
void   display(struct signal *head);
int    count_words(char *l);

int start = 0; char line[100];

struct signal
{
	int num;
	struct node *link;

}*head=0,*temp=0,*current=0;


void main()
{
	FILE *f,*temp;
	
	f=fopen("c17.bench","r");
	
	no_of_inputs(f);
	rewind(f);
	no_of_outputs(f);
	/*rewind(f);
	check(f);*/
	fclose ( f);

}


void no_of_inputs(FILE *file)
{
	
	char gate[1];
	struct signal *inputs;
	int count = 0;
	
	while(fgets(line,sizeof(line),file) != NULL) 
    {
        if(line[0] == 'I')
		{
			fputs(line,stdout );
			count++;
			inputs = addSignal();
			
			
		}
    }
	display(head);
	head = 0; //Resetting head.
	
	printf("\nPrimary inputs = %d\n",count);
      

}


void no_of_outputs(FILE *file)
{
	
	struct signal *outputs;
	//char line[100];
	int count = 0;
	
	while(fgets(line,sizeof(line),file) != NULL) 
    {
        if(line[0] == 'O')
		{
			fputs(line,stdout );
			count++;
			outputs = addSignal();
			
		}
    }
	display(head);
	printf("\nPrimary outputs = %d\n",count);
      

}


/*void check(FILE *file)
{
	char check[80],line[100];
	int flag = 0;
	
	while(fgets(line,sizeof(line),file) != NULL) 
    {
        if(line[0] == 'I' && flag == 0)
		{
			gate[0] = line[6];
			gate[1] = line[7];
			gate[2] = '\0';
			flag = 1;
			continue;
		}
		if(flag == 1 && count_words(line) > 1){
			fputs(line,stdout );
			for(int i = 0;i < strlen(line)-strlen(gate); i++) //Check for substring gate[].
			{
				if(line[i] == '(')
				{
					//for(int j = 0; j < strlen(gate); j++)
						if(line[i+2] == gate[1])
							break;
				}
			}
			
		}
    }
	
}*/


int count_words(char *l)
{
	int count = 0;
	for(int i = 0;i < strlen(l); i++)
	{
		if(l[i] == ' ')
			count++;
		
	}
	return count+1;
}


struct signal * addSignal()
{
	char *n;
	temp = (int *)malloc(sizeof(struct signal));
	if(temp == NULL)                     
	{
		printf("Error! memory not allocated.");
	}
	else
	{
		if(line[0] == 'I')
			temp -> num = line[7]-48;
		else
		{
			temp -> num = getGateID();
			
		}
		temp -> link = NULL;
		if(head == NULL)
		{
			head = current = temp;
		}
		else
		{
			current -> link = temp;
			current = temp;
		}
			
	}
	return head;
}


void display(struct signal *head)
{

 printf("The primary inputs : \n");
 current = head;

 while(current != NULL)
   {
		printf("%d--->",current -> num);
		current = current -> link;
   }
  
}


int getGateID()
{	
	char *digit;
	int len = strlen(line);
	int index = 0;
	//printf("%s",str);
	for(int i = 0; i < len ;i++)
	{
		if(line[i]>='0' && line[i]<='9')
		{ 
			digit[index] = line[i] ;
			++index;
		}
	}
	return atoi(digit);
}
