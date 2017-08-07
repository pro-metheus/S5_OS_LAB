#include"scheduling_algorithms.h"
#include<stdio.h>
void main(){
	//here lies the main fuction....
	printf("1 create task, 2 print tasks, 3 fcfs, 4 sjf 5 priority algo 6round robin 7quit");
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
		case 2:view_tasks(); //verified
			break;
		case 3:fcfs();       //verified
			break;
		case 4: sjf();      //verified
			break;
		case 5: priority();  //verified
			break;
		case 6: round_robin(); //verified
			break;
		case 7:clear_memory();
		exit(0);
	}
	
	
	
	
	
	
	
}//while
}//main
