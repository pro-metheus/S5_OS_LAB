#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//config settings
#define NAME_LENGTH 10
//


struct task{
	int burst_time;
	char process_name[NAME_LENGTH];
	int priority;
	struct task* next;
}*head=NULL,*new_task,*cur_task;


struct shortq{
		int burst;
		struct task* link;
	};

//thats the fucking data structure we are gonna use
void spawn_task(char name[NAME_LENGTH],int burst, int priority){
	new_task=(struct task*)malloc(sizeof(struct task));
	new_task->burst_time=burst;
	//printf("%d",burst);
	new_task->priority=priority;
	strcpy(new_task->process_name,name);
	//printf("%d",new_task->burst_time);
	if(head==NULL){
		head=new_task;
		cur_task=new_task;
	}
	else{
		cur_task->next=new_task;
		cur_task=new_task;
	}

}//spawn_tasks ends here


void view_tasks(){
	cur_task=head;
	do{
		printf("%s has %d burst time \n",cur_task->process_name,cur_task->burst_time);
		cur_task=cur_task->next;
	}while(cur_task !=NULL);
}//view tasks ends here




void fcfs(){
	int waiting_time;
	int turn_around_time;
	int temp;
	int elapsed=0;
	cur_task=head;
	do{
	temp=cur_task->burst_time;
	printf("%s task waiting time= %d, turaround time= %d",cur_task->process_name,elapsed,elapsed+temp);
	elapsed+=temp;
	cur_task=cur_task->next;		
	}while(cur_task != NULL);
}


void sjf(){
	
	
	struct shortq list[10];
	
}


void main(){
	//here lies the main fuction....
	printf("1 create task, 2 print tasks, 3 quit");
	int op;
	while(1==1){
	scanf("%d",&op);
	switch(op){
		case 1:printf("enter task name");
			char name[NAME_LENGTH];
			scanf("%s",&name);
			printf("enter task burst time");
			int bt;
			scanf("%d",&bt);
			printf("enter task priority");
			int prio;
			scanf("%d",&prio);
			spawn_task(name,bt,prio);
			break;
		case 2:view_tasks();
			break;
		case 3:fcfs();
			break;
		case 4:exit(0);
	}
	
	
	
	
	
	
	
}//while
}//main
