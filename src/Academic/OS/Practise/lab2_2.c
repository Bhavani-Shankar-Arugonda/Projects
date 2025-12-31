#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PROCESSES 100

typedef struct{
    int pid;
    int at;
    int bt;
    int rem_bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int start_time;
}Process;

void reset_processes(Process dest[], Process src[], int k) {
    for (int i = 0; i < k; i++) {
        dest[i] = src[i];       
    }
}

void sort_by_arrival(Process p[],int k)
{
    Process temp;
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < k - 1 - i; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfs(Process p[], int k) {
    sort_by_arrival(p, k);
    
    int current_time = 0;
    
    for (int i = 0; i < k; i++) {
        // If CPU is idle, jump to arrival time
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }
        
        // FCFS is non-preemptive: Start Time is current time
        p[i].start_time = current_time;
        p[i].rt = p[i].start_time - p[i].at;
        
        // Execute
        current_time += p[i].bt;
        p[i].ct = current_time;
        
        // Metrics
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    
    print_metrics(p, k, "FCFS");
}

void sjf(Process p[], int k){
    int completed=0;
    int current_time=0;
    bool is_completed[MAX_PROCESSES]={false};

    sort_by_arrival(p,k);

    while(completed<k)
    {
        int idx=-1;
        int min_bt=100000;

        for(int i=0;i<k;i++)
        {
            if(p[i].at<current_time && is_completed[i]==false)
            {
                if(p[i].bt<min_bt)
                {
                    min_bt=p[i].bt;
                    idx=i;
                }
            }
        }

        if(idx!=-1)
        {
            p[idx].start_time=current_time;
            p[idx].rt=p[idx].start_time-p[idx].at;

            current_time+=p[idx].bt;

            p[idx].ct=current_time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            is_completed[idx] = true;
            completed++;
        }
        else{
            current_time++;
        }
    }
    print_metrics(p, k, "SJF (Non-Preemptive)");
}

void round_robin(Process p[], int k, int time_quantum) {
    // Queue implementation
    int q[1000];
    int front = 0, rear = 0;
    bool in_queue[MAX_PROCESSES] = {false};
    
    // Sort by arrival first to enqueue correctly
    sort_by_arrival(p, k);
    
    int current_time = 0;
    int completed = 0;
    
    // Push first process(es)
    if (k > 0) {
        // Handle idle start if first process arrives late
        current_time = p[0].at;
    }

    // Enqueue processes that have arrived at start
    for(int i=0; i<k; i++) {
        if(p[i].at <= current_time) {
            q[rear++] = i;
            in_queue[i] = true;
        }
    }
    
    while (completed < k) {
        if (front == rear) {
            // Queue is empty. If processes left, jump time.
            bool found_future = false;
            for(int i=0; i<k; i++) {
                if(!in_queue[i] && p[i].rem_bt > 0) {
                    current_time = p[i].at;
                    q[rear++] = i;
                    in_queue[i] = true;
                    found_future = true;
                    break;
                }
            }
            if (!found_future) break; // Should not happen if logic is correct
        }
        
        int idx = q[front++]; // Dequeue
        
        // Record response time if first time processing
        if (p[idx].start_time == -1) {
            p[idx].start_time = current_time;
            p[idx].rt = current_time - p[idx].at;
        }
        
        // Execute for Time Quantum or Remaining Time
        int exec_time = (p[idx].rem_bt > time_quantum) ? time_quantum : p[idx].rem_bt;
        
        p[idx].rem_bt -= exec_time;
        current_time += exec_time;
        
        // Check for new arrivals during this execution
        for (int i = 0; i < k; i++) {
            if (p[i].at > p[idx].at && // Don't re-check self or past
                p[i].at <= current_time && 
                !in_queue[i] && 
                p[i].rem_bt > 0) {
                q[rear++] = i;
                in_queue[i] = true;
            }
        }
        
        // If process not finished, enqueue again
        if (p[idx].rem_bt > 0) {
            q[rear++] = idx;
        } else {
            // Process finished
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }
    
    char buffer[50];
    sprintf(buffer, "Round Robin (TQ=%d)", time_quantum);
    print_metrics(p, k, buffer);
}

int main() {
    int k;
    srand(time(0)); 

    printf("Enter number of processes (k): ");
    scanf("%d", &k);
    
    // Master list of processes
    Process original[MAX_PROCESSES];
    Process copy[MAX_PROCESSES];
    
    printf("Generating Random Data...\n");
    for (int i = 0; i < k; i++) {
        original[i].pid = i + 1;
        original[i].at = rand() % 11;      // Random arrival 0-10 [cite: 85]
        original[i].bt = rand() % 101;     // Random burst 0-100 [cite: 85]
        // Ensure BT is at least 1 for valid simulation
        if(original[i].bt == 0) original[i].bt = 1;
        
        original[i].rem_bt = original[i].bt;
        original[i].start_time = -1;
    }
    
    // Display Generated Data
    printf("\nGenerated Processes:\nPID\tAT\tBT\n");
    for(int i=0; i<k; i++) {
        printf("%d\t%d\t%d\n", original[i].pid, original[i].at, original[i].bt);
    }

    // 1. Run FCFS
    reset_processes(copy, original, k);
    fcfs(copy, k);
    
    // 2. Run SJF
    reset_processes(copy, original, k);
    sjf(copy, k);
    
    // 3. Run RR with different TQ [cite: 86]
    int tqs[] = {5, 10, 15, 20, 25};
    for(int i=0; i<5; i++) {
        reset_processes(copy, original, k);
        round_robin(copy, k, tqs[i]);
    }
    
    return 0;
}
