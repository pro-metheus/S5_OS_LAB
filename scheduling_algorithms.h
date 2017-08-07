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
}*head=NULL,*new_task,*cur_task,*prev;


struct shortq{
		int burst;
		struct task* link;
	};
	
	
struct prioq{
	int prio;
	struct task* link;
};
	
struct logger{
	int spent;
	int finished;
	int wait;
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
void clear_memory(){
	cur_task=head;
			while(cur_task!=NULL){
				prev=cur_task;
				free(prev);
				cur_task=cur_task->next;
			}
}

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


void round_robin(){
	int quanta;
	struct logger log[count];
	printf("enter the time quanta :");
	scanf("%d",&quanta);
	cur_task=head;
	int i=0;
	while(cur_task!=NULL){
		log[i].finished=0;
		log[i].link=cur_task;
		log[i].spent=0;
		log[i].wait=0;
		cur_task=cur_task->next;
		i++;
	}//inititalized
	int full=0; //signal for adding waiting time
	int done=0;
	while(done ==0){
		i=0;
		int needed;
		while(i<count){
			if(log[i].finished==0){
				
				needed=log[i].link->burst_time - log[i].spent;
			
				if(needed>=quanta){
					printf("task %s needs %d ",log[i].link->process_name,needed);
				
				log[i].spent+=quanta;
				int j=0;
				for(j=0;j<count;j++){
					if(i==j || log[j].finished==1){
						continue;
						printf("skipped");
					}
					else{
						log[j].wait+=quanta;
						printf("%d added waiting time--full",j);
					}
				}
				}
				
				else{
					printf("task %s needs %d ",log[i].link->process_name,needed);
					log[i].spent+=needed;
					int j=0;
				for(j=0;j<count;j++){
					if(i==j || log[j].finished==1){
						continue;
						printf("skipped");
					}
					else{
						log[j].wait=log[j].wait+needed;;
						printf("%d added waiting time",j);
					}
				}
					printf("task %s finished \n",log[i].link->process_name);
					log[i].finished=1;
					full=0;
					
				}

				
				}
					
			
			i++;
			
		}
		int lock=0;
		int j;
		for(j=0;j<count;j++){
			if(log[j].finished==1){
				lock=1;
				
			}
			else{
				lock=0;
				break;
			}
		}
		if(lock==1){
			done=1;
		}
			
	}
	for(i=0;i<count;i++){
		printf("task(%d / %d) %s waited for %d and has a turnarouund time of %d\n",log[i].spent,log[i].link->burst_time,log[i].link->process_name,log[i].wait,log[i].spent+(log[i].wait));
	}
}





