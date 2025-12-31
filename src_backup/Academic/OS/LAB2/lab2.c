#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Process{
    int process_num;
    int arrival_time;
    int cpu_cycle_time;
    int completion_time;
    int wait_time;
    int response_time;
    int num_assignment;
    int original_cpu_time;
    struct Process *next;
}Process;

typedef struct ready_queue{
    Process *node;
    struct ready_queue *next;
}ready_queue;


//for fcfs
//returns pointer to min 
Process* getmin_arrival_time(Process* process_head)
{
    Process *temp=process_head;
    Process *min=process_head;
    if(temp==NULL)
    {
        return NULL;
    }
    else if(temp->next==NULL)
    {
        return process_head;
    }
    int min_val=temp->arrival_time;
    while(temp!=NULL)
    {
        if(temp->arrival_time<min_val)
        {
            min_val = temp->arrival_time;
            min=temp;
        }
        temp=temp->next;
    }

    return min;
}

void FCFS(int k, Process* process_head)
{
    //creating a queue
    ready_queue *front=NULL;
    ready_queue *rear=NULL;

    //enquing queue based on minimum arrival time
    for(int i=0;i<k;i++){
        Process* min=getmin_arrival_time(process_head);
        if(process_head==min)
        {
            process_head=process_head->next; 
        }
        else{
            Process *curr = process_head;
            while(curr != NULL && curr->next != min)
            {
                curr=curr->next;
            }
            if(curr != NULL)
            {
                curr->next=min->next;
            }
        }

        ready_queue* Node=(ready_queue*)malloc(sizeof(ready_queue));
        if(Node==NULL)
        {
            printf("Error creatinf ready queue!!");
            return;
        }
        Node->node=min;
        Node->next=NULL;

        if(front==NULL)
            {
                front=Node;
                rear=Node;
            }
            else{
                rear->next=Node;
                rear=Node;
            }
    }

    //finding completion times and waiting times
    ready_queue* temp_node=front;
    temp_node->node->wait_time=0;
    temp_node->node->completion_time=temp_node->node->arrival_time+temp_node->node->cpu_cycle_time;
    int prev_node_completion_time=temp_node->node->completion_time;
    temp_node=temp_node->next;
    while(temp_node!=NULL)
    {
        //completion times
        if(temp_node->node->arrival_time>prev_node_completion_time)
        {
           temp_node->node->completion_time=temp_node->node->arrival_time+temp_node->node->cpu_cycle_time; 
        }
        else{
            temp_node->node->completion_time=prev_node_completion_time+temp_node->node->cpu_cycle_time;
        }

        //waiting times
        if((prev_node_completion_time-temp_node->node->arrival_time)>=0)
        {
            temp_node->node->wait_time=prev_node_completion_time-temp_node->node->arrival_time;
        }

        prev_node_completion_time=temp_node->node->completion_time;
        temp_node=temp_node->next;
    }

    //printing outputs
    printf("\n--- FCFS Results ---\n");
    int avg_tat=0;
    temp_node=front;
    for(int i=0; i<k;i++)
    {
        avg_tat=avg_tat+temp_node->node->completion_time-temp_node->node->arrival_time;
        printf("TAT For Process Number %d with arrival and cpu time as (%d,%d) : %d\n",temp_node->node->process_num,temp_node->node->arrival_time,temp_node->node->cpu_cycle_time,temp_node->node->completion_time-temp_node->node->arrival_time);
        printf("waiting time and response time for above process is %d\n\n",temp_node->node->wait_time);
        temp_node=temp_node->next;
    }

    printf("\nAverage TAT for %d Processes : %0.4f\n",k,(float)avg_tat/k);

    //clearing memories
    temp_node = front;
    while(temp_node != NULL) {
        ready_queue* to_free = temp_node;
        temp_node = temp_node->next;
        free(to_free->node);
        free(to_free);
    }
}


//for sjf
//returns based on min cpu time an keeping arrival time in check
Process* getmin_cpu_time(Process* process_head, int current_time)
{
    Process *temp = process_head;
    Process *min = NULL;

    while (temp != NULL)
    {
        if (temp->arrival_time <= current_time) 
        {
            if (min == NULL || temp->cpu_cycle_time < min->cpu_cycle_time)
            {
                min = temp;
            }
        }
        temp = temp->next;
    }

    return min; 
}

void SJF(int k,Process *process_head)
{
    //creating queue
    ready_queue *front=NULL;
    ready_queue *rear=NULL;

    //enquing and claculating ouputs required
    int current_time=0;
    int completed_processes=0;
    while(completed_processes<k){
        Process* min=getmin_cpu_time(process_head,current_time);

        if(min==NULL)
        {
            current_time++;
            continue;
        }

        if(process_head==min)
        {
            process_head=process_head->next; 
        }
        else{
            Process *curr = process_head;
            while(curr != NULL && curr->next != min)
            {
                curr=curr->next;
            }
            if(curr != NULL)
            {
                curr->next=min->next;
            }
        }

        ready_queue* Node=(ready_queue*)malloc(sizeof(ready_queue));
        if(Node==NULL)
        {
            printf("Error creating ready queue!!");
            return;
        }
        Node->node=min;
        Node->next=NULL;

        if(front==NULL)
        {
            front=Node;
            rear=Node;
        }
        else{
            rear->next=Node;
            rear=Node;
        }

        if(current_time<min->arrival_time)
        {
            current_time=min->arrival_time;
        }

        min->wait_time = current_time - min->arrival_time;
        min->response_time = min->wait_time;
        min->completion_time = current_time + min->cpu_cycle_time;
        
        current_time = min->completion_time;
        completed_processes++;
    }

    

    //printing outputs
    int avg_tat=0;
    ready_queue *temp_node=front;
    printf("\n--- SJF Results ---\n");
    for(int i=0; i<k;i++)
    {
        avg_tat=avg_tat+temp_node->node->completion_time-temp_node->node->arrival_time;
        printf("TAT For Process Number %d with arrival and cpu time as (%d,%d) : %d\n",temp_node->node->process_num,temp_node->node->arrival_time,temp_node->node->cpu_cycle_time,temp_node->node->completion_time-temp_node->node->arrival_time);
        printf("waiting time and response time for above process is %d\n\n",temp_node->node->wait_time);
        temp_node=temp_node->next;
    }

    printf("\nAverage TAT for %d Processes : %0.4f\n",k,(float)avg_tat/k);

    //clearing memory
    temp_node = front;
    while(temp_node != NULL) {
        ready_queue* to_free = temp_node;
        temp_node = temp_node->next;
        free(to_free->node);
        free(to_free);
    }
}

void RR(int k,Process* process_head, int quantum_time)
{
    int total_cpu_time=0;
    int current_time=0;
    //saorting based on arrival time
    ready_queue *front=NULL;
    ready_queue *rear=NULL;

    for(int i=0;i<k;i++){
        Process* min=getmin_arrival_time(process_head);
        if(process_head==min)
        {
            process_head=process_head->next; 
        }
        else{
            
            Process *curr = process_head;
            while(curr != NULL && curr->next != min)
            {
                curr=curr->next;
            }
            if(curr != NULL)
            {
                curr->next=min->next;
            }
        }
        total_cpu_time=total_cpu_time+min->cpu_cycle_time;

        ready_queue* Node=(ready_queue*)malloc(sizeof(ready_queue));
        if(Node==NULL)
        {
            printf("Error creatinf ready queue!!");
            return;
        }
        Node->node=min;
        Node->next=NULL;

        if(front==NULL)
            {
                front=Node;
                rear=Node;
            }
            else{
                rear->next=Node;
                rear=Node;
            }
    }

    //converting given linked list to circular queue
    rear->next=front;

    ready_queue *temp=front;
    current_time=temp->node->arrival_time;

    while(total_cpu_time>0)
    {
        if(temp->node->cpu_cycle_time>0 && temp->node->cpu_cycle_time<quantum_time)
        {
            int executed_time = temp->node->cpu_cycle_time; 
            current_time=current_time+temp->node->cpu_cycle_time;
            total_cpu_time=total_cpu_time-temp->node->cpu_cycle_time;
            temp->node->completion_time=current_time;
            temp->node->num_assignment++;
            if(temp->node->num_assignment==1)
            {
                temp->node->response_time=current_time-executed_time-temp->node->arrival_time;
            }
            temp->node->wait_time=temp->node->completion_time-temp->node->arrival_time-temp->node->original_cpu_time;
            temp->node->completion_time=current_time;
            
            temp->node->cpu_cycle_time=0;
            temp=temp->next;
            
        }
        else if(temp->node->cpu_cycle_time<=0)
        {
            temp=temp->next;
        }
        else{
            current_time=current_time+quantum_time;
            temp->node->cpu_cycle_time=temp->node->cpu_cycle_time-quantum_time;
            temp->node->num_assignment++;
            //for only the first assignment response time is calculated
            if(temp->node->num_assignment==1)
            {
                temp->node->response_time=current_time-quantum_time-temp->node->arrival_time;
            }
            temp=temp->next;
            total_cpu_time=total_cpu_time-quantum_time;
        }
    }

    //printing output
    int avg_tat=0;
    ready_queue *temp_node=front;
    printf("\n--- RR Results ---\n");
    for(int i=0; i<k;i++)
    {
        avg_tat=avg_tat+temp_node->node->completion_time-temp_node->node->arrival_time;
        printf("TAT For Process Number %d with arrival and cpu time as above : %d\n",temp_node->node->process_num,temp_node->node->completion_time-temp_node->node->arrival_time);
        printf("waiting time and response time for above process is %d and %d\n\n",temp_node->node->wait_time,temp_node->node->response_time);
        temp_node=temp_node->next;
    }

    printf("\nAverage TAT for %d Processes : %0.4f\n",k,(float)avg_tat/k);
    
    //clearing memory
    temp_node = front;
    for(int i = 0; i < k; i++) {
        ready_queue* to_free = temp_node;
        temp_node = temp_node->next;
        free(to_free->node);
        free(to_free);
    }
}

int main(){

    srand(time(NULL));

    int k;
    printf("Enter the number of processe : ");
    scanf("%d",&k);
    printf("\n");

    int quantum_time;
    printf("Enter quantum time for RR algorithm : ");
    scanf("%d",&quantum_time);
    printf("\n");


    //creating 3 linked list for 3 operations
    int process_number1=1;
    int process_number2=1;
    int process_number3=1;

    
    Process *process_head1=NULL;
    Process *process_head2=NULL;
    Process *process_head3=NULL;

    Process *current1=NULL;
    Process *current2=NULL;
    Process *current3=NULL;

    //giving random values for arrival time and cpu cycle times for 3 linked lists(same for all)
    for(int i=0; i<k;i++)
    {
        Process *newnode1 = (Process*)malloc(sizeof(Process));
        Process *newnode2 = (Process*)malloc(sizeof(Process));
        Process *newnode3 = (Process*)malloc(sizeof(Process));
        
        if(newnode1==NULL || newnode2==NULL || newnode3==NULL)
        {
            printf("Process creation Error : Menonry not allocated!!");
            return 1;
        }
        
        newnode1->arrival_time=(rand()%11);
        newnode1->cpu_cycle_time=(rand()%101);
        newnode1->original_cpu_time=newnode1->cpu_cycle_time;
        newnode1->completion_time=0;
        newnode1->wait_time=0;
        newnode1->response_time=0;
        newnode1->process_num=process_number1++;
        newnode1->num_assignment=0;
        newnode1->next=NULL;

        newnode2->arrival_time=newnode1->arrival_time;
        newnode2->cpu_cycle_time=newnode1->cpu_cycle_time;
        newnode2->original_cpu_time=newnode2->cpu_cycle_time;
        newnode2->completion_time=0;
        newnode2->wait_time=0;
        newnode2->response_time=0;
        newnode2->process_num=process_number2++;
        newnode2->num_assignment=0;
        newnode2->next=NULL;

        newnode3->arrival_time=newnode1->arrival_time;
        newnode3->cpu_cycle_time=newnode1->cpu_cycle_time;
        newnode3->original_cpu_time=newnode3->cpu_cycle_time;
        newnode3->completion_time=0;
        newnode3->wait_time=0;
        newnode3->response_time=0;
        newnode3->process_num=process_number3++;
        newnode3->num_assignment=0;
        newnode3->next=NULL;

        if(process_head1==NULL)
        {
            process_head1=newnode1;
            current1=process_head1;
        }
        else{
            current1->next=newnode1;
            current1=newnode1;
        }

        if(process_head2==NULL)
        {
            process_head2=newnode2;
            current2=process_head2;
        }
        else{
            current2->next=newnode2;
            current2=newnode2;
        }

        if(process_head3==NULL)
        {
            process_head3=newnode3;
            current3=process_head3;
        }
        else{
            current3->next=newnode3;
            current3=newnode3;
        }
    }

    FCFS(k,process_head1);
    SJF(k,process_head2);
    RR(k,process_head3,quantum_time);
}