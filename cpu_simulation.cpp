#include <iostream>
#include<string.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <queue>
#include <ctime>
using namespace std;
  
class process {
public:
   string pr_name; //process name
   int pr_index; //process index number
   string state; // i.e. Ready, Running, Waiting and Terminated.
   int time[3];// Arrival Time as in hour number, minute number, second number
   string *inst; //List of instructions.
   int inst_size; //total number of instructions, needed for burst time calculation
   string que; //Current Queue (Ready queue: FCFS-1, FCFS-2 or SJF. Waiting Queue: HardDisk, Network or Device (Peripheral Device) 
   process *next;//pointer to next process node
   process *prev;//pointer to previous process node
};

//creating multi level feed back ques
queue<process*> FCFS1,FCFS2,SJF; //ready ques
queue<process*> HardDisk, Network, Device; //waiting ques
int exectued_processes=0;
  
void append(process** head_ref, string pr_name, int pr_index, string state, string *inst, int no_inst, string que)
{
    // allocate node 
    process* new_process = new process();
    // put in node data 
    new_process->pr_name = pr_name;
    new_process->pr_index = pr_index;
    new_process->state = state;
    new_process->inst = inst;
    new_process->inst_size=no_inst;
    new_process->que = que;
    //calculating current time for process creation/arrival
    sleep(1); //so	creation/arrival for each process can be different
    time_t now = time(0);
	tm *ltm = localtime(&now);
    new_process->time[0] = 5+ltm->tm_hour;
    new_process->time[1] = 30+ltm->tm_min;
    new_process->time[2] = ltm->tm_sec;
    
    //making next node ptr NULL
    new_process->next = NULL;
 
    // making new node as head If doubble Linked List  empty
    if (*head_ref == NULL) {
        new_process->prev = NULL;
        *head_ref = new_process;
        FCFS1.push(new_process);
        return;
    }
    process* last = *head_ref; 
    // Else traverse till the last node 
    while (last->next != NULL)
        last = last->next;
 
    last->next = new_process;
    //setting last node as previous of new node 
    new_process->prev = last;
    FCFS1.push(new_process); //entering every newly made process in FCFS1 que at start 
    return;
}

void printList(process* node)
{
    process* last;
    cout << "\nDispaying doubble link list of all processes";
    while (node != NULL) {
    	cout<<"\n------------------------------------------------------------------------";
        cout <<"\nProcess index: "<<node->pr_index<<"\nProcess name: "<< node->pr_name;
		cout<<"\nProcess creation time: "<<node->time[0]<<":"<<node->time[1]<<":"<<node->time[2];
		cout<<"\nProcess state: "<< node->state<<"\nProcess que: "<<node->que<<" ";
		cout<<"\nNumber of instructions allocated to current process are: "<<node->inst_size<<", and the instructions are: ";
		for(int i=0;i<node->inst_size;i++)
		{
			cout<<node->inst[i]<<", ";
		}
        last = node;
        node = node->next;
        cout<<"\n------------------------------------------------------------------------";
    }
 
}

bool FCFS1_execution(process *pnode)
{
	int print=0;
	int index=0;
	for(int i=0;i<3;i++)	//FCFS1 will have an execution time slice of 3 as told
						   //here time slice 3 meaning taken as 3 instruction execution that is why loop of 3
	{
		if(pnode->inst[index]== "harddisk") 
		{
			HardDisk.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if(pnode->inst[index]== "network") 
		{
			Network.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if( pnode->inst[index]== "device")
		{
			Device.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if(pnode->inst[index]!= "executed")
		{
		 if(print==0)
		 {
		 	cout<<endl<<pnode->pr_name;	
		 	print=1;
		 }
		 cout<<"\nexecuting instruction "<<index+1<<" "<<pnode->inst[index];
		 pnode->inst[index]="executed"; //simulating cpu instruction execution by changing execution instructions to executed in instruction list
		}
		else
		{
			i--;
		}
		index++;
		if (index==(pnode->inst_size))
		{
			cout<<endl<<pnode->pr_name<<"'s all instructions executed\n";
			exectued_processes++;
			return 1; 		//if instruction executed index number equal to instruction list max index meaning all instructions executed
		}
	}
	FCFS2.push(pnode); //if after being executed from FCFS1 que if process instructions still left process added to FCFS2 que that has more time slice
	return 0;
}

bool FCFS2_execution(process *pnode)
{
	int index=0;
	int print=0;
	for(int i=0;i<6;i++)	//FCFS2 will have an execution time slice of 6 as told
						   //here time slice 6 meaning taken as 6 instruction execution that is why loop of 6
	{
		if(pnode->inst[index]== "harddisk") 
		{
			HardDisk.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if(pnode->inst[index]== "network") 
		{
			Network.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if( pnode->inst[index]== "device")
		{
			Device.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if(pnode->inst[index]!= "executed")
		{
		 if(print==0)
		 {
		 	cout<<endl<<pnode->pr_name;	
		 	print=1;
		 }
		 cout<<"\nexecuting instruction "<<index+1<<" "<<pnode->inst[index];
		 pnode->inst[index]="executed"; //simulating cpu instruction execution by changing execution instructions to executed in instruction list
		}
		else
		{
			i--;
		}
		index++;
		if (index==(pnode->inst_size))
		{
			cout<<endl<<pnode->pr_name<<"'s all instructions executed\n";
			exectued_processes++;
			return 1; 		//if instruction executed index number equal to instruction list max index meaning all instructions executed
		}
	}
	SJF.push(pnode); //if after being executed from FCFS2 que if process instructions still left process added to SJF que 
	return 0;
}

bool SJF_execution(process *pnode)
{
	int index=0;
	int print=0;
	for(int i=0;i<pnode->inst_size;i++) //SJF not having time slice rather executing smallest process till all its instructions left are done
	{
		if(pnode->inst[index]== "harddisk") 
		{
			HardDisk.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if(pnode->inst[index]== "network") 
		{
			Network.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if( pnode->inst[index]== "device")
		{
			Device.push(pnode);
			pnode->inst[index]="executed";
			return 1;
		}
		if(pnode->inst[index]!= "executed")
		{
		 if(print==0)
		 {
		 	cout<<endl<<pnode->pr_name;	
		 	print=1;
		 }
		 cout<<"\nexecuting instruction "<<index+1<<" "<<pnode->inst[index];
		 pnode->inst[index]="executed"; //simulating cpu instruction execution by changing execution instructions to executed in instruction list
		}
		else
		{
			i--;
		}
		index++;
		if (index==(pnode->inst_size))
		{
			cout<<endl<<pnode->pr_name<<"'s all instructions executed\n";
			exectued_processes++;
			return 1; 		//if instruction executed index number equal to instruction list max index meaning all instructions executed
		}
	}
	return 0;
}

void HardDisk_execution(process *pnode)
{
	cout<<"\nExecuting process "<<pnode->pr_name<<"'s HardDisk instruction";
	sleep(1); //simulating the wait of cpu for an operation being done by harddisk
	FCFS1.push(pnode); //after completion of operation being moved to highest priority que again
}

void Network_execution(process *pnode)
{
	cout<<"\nExecuting process "<<pnode->pr_name<<"'s Network instruction";
	sleep(1); //simulating the wait of cpu for an operation being done by network
	FCFS1.push(pnode); //after completion of operation being moved to highest priority que again
}

void Device_execution(process *pnode)
{
	cout<<"\nExecuting process "<<pnode->pr_name<<"'s Device I/O instruction";
	sleep(1); //simulating the wait of cpu for an I/O operation being done by a peripherial device
	FCFS1.push(pnode); //after completion of operation being moved to highest priority que again
}


void simulate_CPU(int no_of_processes)
{
	int round=0;
	while (exectued_processes!=no_of_processes)
	{
	round++;
	if(!FCFS1.empty())
	{
		cout<<"\n\nFCFS1 EXECUTION\n";
	
		while(!FCFS1.empty())
		{
			FCFS1_execution(FCFS1.front());
			FCFS1.pop();
		}
	}
	if((!FCFS2.empty()))
	{
		cout<<"\n\nFCFS2 EXECUTION\n";
	
		while(!FCFS2.empty())
		{
			FCFS2_execution(FCFS2.front());
			FCFS2.pop();
		}
	}
	if((!SJF.empty()))
	{
		cout<<"\n\nSJF EXECUTION\n";
	
		while(!SJF.empty())
		{
			SJF_execution(SJF.front());
			SJF.pop();
		}
	}
	if(!HardDisk.empty())
	{
	cout<<"\n\nHardDisk EXECUTION\n";
		while(!HardDisk.empty())
		{
			HardDisk_execution(HardDisk.front());
			HardDisk.pop();
		}
	}
	if(!Network.empty())
	{
	cout<<"\n\nNetwork EXECUTION\n";
		while(!Network.empty())
		{
			Network_execution(Network.front());
			Network.pop();
		}
	}
	if(!Device.empty())
	{
	cout<<"\n\nDevice EXECUTION\n";
	
		while(!Device.empty())
		{
			Device_execution(Device.front());
			Device.pop();
		}
	}
	cout<<"\n\nnumber of executed processes in scheduling round "<<round<<" are "<<exectued_processes<<endl;
	}
}
int main()
{
    /* Start with the empty list */
    process* head = NULL;
    cout<<"Creating 6 processes (in DLL) for our scheduling simulation:";
    string p1[8]={"compute","compute","compute","harddisk","compute","compute","network","compute"};
    append(&head, "addition code",0,"ready",p1,8,"FCFS1" );
    string p2[3]={"device","compute","compute"};
    append(&head, "input taking",1,"ready",p2,3,"FCFS1" );
    string p3[6]={"compute","compute","compute","harddisk","network","compute"};
    append(&head, "data access",2,"ready",p3,5,"FCFS1" );
    string p4[4]={"compute","compute","network","compute"};
    append(&head, "send message",3,"ready",p4,4,"FCFS1" );
    string p5[11]={"compute","compute","compute","compute","network","compute","compute","compute","compute","device","compute"};
    append(&head, "algebra solving",4,"ready",p5,11,"FCFS1" );
    string p6[15]={"compute","compute","compute","compute","compute","compute","compute","compute","compute","compute","compute","harddisk","compute","device","compute"};
    append(&head, "heavy computing",5,"ready",p6,15,"FCFS1");
	printList(head);
	cout<<"\nNow simulating the execution of all these processes by a cpu according to scheduling instructions given\n";
 	simulate_CPU(6);
    return 0;
}   
