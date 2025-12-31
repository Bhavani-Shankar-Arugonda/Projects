#include <stdio.h>
#include <stdbool.h>

#define MAX_REF 100
#define MAX_FRAMES 10

// Function to print the current state of frames
void printFrames(int frames[], int n, bool page_fault) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    if (page_fault)
        printf("\t-> PF"); // Indicator for Page Fault
    else
        printf("\t-> Hit");
    printf("\n");
}

// Check if a page exists in the frames (Hit)
bool isHit(int page, int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

// --- 1. FIFO Policy ---
void runFIFO(int ref[], int len, int k) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < k; i++) frames[i] = -1; // Initialize frames

    int faults = 0;
    int index = 0; // Points to the "oldest" page to replace

    printf("\n--- FIFO Trace ---\n");
    for (int i = 0; i < len; i++) {
        printf("Page %d: ", ref[i]);
        
        if (!isHit(ref[i], frames, k)) {
            // Page Fault
            frames[index] = ref[i];
            index = (index + 1) % k; // Circular increment
            faults++;
            printFrames(frames, k, true);
        } else {
            printFrames(frames, k, false);
        }
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}

// --- 2. LRU Policy ---
void runLRU(int ref[], int len, int k) {
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES]; // Tracks the "time" each frame was last used
    
    for (int i = 0; i < k; i++) frames[i] = -1;

    int faults = 0;
    int time = 0;

    printf("\n--- LRU Trace ---\n");
    for (int i = 0; i < len; i++) {
        printf("Page %d: ", ref[i]);
        time++;

        // 1. Check for Hit
        bool hit = false;
        for (int j = 0; j < k; j++) {
            if (frames[j] == ref[i]) {
                last_used[j] = time; // Update usage time
                hit = true;
                break;
            }
        }

        if (hit) {
            printFrames(frames, k, false);
        } else {
            // 2. Page Fault
            faults++;
            int replace_idx = -1;
            
            // Check if there is empty space
            for (int j = 0; j < k; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            // If no empty space, find Least Recently Used
            if (replace_idx == -1) {
                int min_time = 1000000;
                for (int j = 0; j < k; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        replace_idx = j;
                    }
                }
            }

            frames[replace_idx] = ref[i];
            last_used[replace_idx] = time;
            printFrames(frames, k, true);
        }
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}

// --- 3. Optimal Policy ---
void runOPT(int ref[], int len, int k) {
    int frames[MAX_FRAMES];
    for (int i = 0; i < k; i++) frames[i] = -1;

    int faults = 0;

    printf("\n--- OPTIMAL Trace ---\n");
    for (int i = 0; i < len; i++) {
        printf("Page %d: ", ref[i]);

        if (isHit(ref[i], frames, k)) {
            printFrames(frames, k, false);
        } else {
            // Page Fault
            faults++;
            int replace_idx = -1;

            // Check for empty space first
            for (int j = 0; j < k; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            // If full, look ahead to find the page used farthest in future
            if (replace_idx == -1) {
                int farthest = -1;
                
                for (int j = 0; j < k; j++) {
                    int next_use = -1;
                    // Scan future reference string
                    for (int m = i + 1; m < len; m++) {
                        if (frames[j] == ref[m]) {
                            next_use = m;
                            break;
                        }
                    }

                    // If a page is never used again, it's the perfect victim
                    if (next_use == -1) {
                        replace_idx = j;
                        break; 
                    }

                    // Otherwise, find the one with the largest next_use index
                    if (next_use > farthest) {
                        farthest = next_use;
                        replace_idx = j;
                    }
                }
            }
            
            frames[replace_idx] = ref[i];
            printFrames(frames, k, true);
        }
    }
    printf("Total Page Faults (OPTIMAL): %d\n", faults);
}

int main() {
    int k, len;
    int ref[MAX_REF];

    // 1. Get Inputs
    printf("Enter number of frames (k): ");
    scanf("%d", &k);

    printf("Enter length of reference string: ");
    scanf("%d", &len);

    printf("Enter reference string (space separated): ");
    for (int i = 0; i < len; i++) {
        scanf("%d", &ref[i]);
    }

    // 2. Run Simulations
    runFIFO(ref, len, k);
    runLRU(ref, len, k);
    runOPT(ref, len, k);

    return 0;
}