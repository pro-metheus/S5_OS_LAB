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
	
	
struct prioq{
	int prio;
	struct task* link;
};
	
int count=0;

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
	
	
	struct shortq list[count];
	cur_task=head;
	int i=0;
	while(cur_task!=NULL){
		list[i].burst=cur_task->burst_time;
		list[i].link=cur_task;
		i++;
		cur_task=cur_task->next;
	}  //fills the shortq...now sort it some fucking way im using bubble sort cause i dont give a shit about the fucking complexity 
	
	int j=0;
	i=0;
	for(i=0;i<count;i++){
		for(j=0;j<count;j++){
			if(list[i].burst<list[j].burst){
				struct shortq temp;
				temp.burst=list[j].burst;
				temp.link=list[j].link;
				list[j].burst=list[i].burst;
				list[j].link=list[i].link;
				list[i].burst=temp.burst;
				list[i].link=temp.link;
			}
		}
	}
	int elapsed=0;
	for(i=0;i<count;i++){
		
		int temp1;
		temp1=list[i].link->burst_time;
		printf("%s task waiting time= %d, turaround time= %d\n",list[i].link->process_name,elapsed,elapsed+temp1);
		elapsed+=temp1;
	}
	
	
}




void priority(){

struct prioq queue[count];
cur_task=head;
int i=0;
while(cur_task!=NULL){
	queue[i].prio=cur_task->priority;
	queue[i].link=cur_task;
	i++;
	cur_task=cur_task->next;
}//queue filed
int j;

for(i=0;i<count;i++){
		for(j=0;j<count;j++){
			if(queue[i].prio<queue[j].prio){
				struct prioq temp;
				temp.prio=queue[j].prio;
				temp.link=queue[j].link;
				queue[j].prio=queue[i].prio;
				queue[j].link=queue[i].link;
				queue[i].prio=temp.prio;
				queue[i].link=temp.link;
			}
		}
	}
	
	int elapsed=0;
	for(i=0;i<count;i++){
		
		int temp1;
		temp1=queue[i].link->burst_time;
		printf("%s task waiting time= %d, turaround time= %d\n",queue[i].link->process_name,elapsed,elapsed+temp1);
		elapsed+=temp1;
	}



}






void main(){
	//here lies the main fuction....
	printf("1 create task, 2 print tasks, 3 fcfs, 4 sjf 5 priority algo 6quit");
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
			count++;
			break;
		case 2:view_tasks();
			break;
		case 3:fcfs();
			break;
		case 4: sjf();
			break;
		case 5: priority();
			break;
		case 6:exit(0);
	}
	
	
	
	
	
	
	
}//while
}//main
