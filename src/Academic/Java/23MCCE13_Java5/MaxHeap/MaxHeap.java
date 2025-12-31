public class MaxHeap {
    private int heap[];
    private int size = 0;
    private int maxsize;

    MaxHeap(int maxsize) {
        heap = new int[maxsize];
        this.maxsize = maxsize;
    }

    private int getLChild(int index) {
        return 2 * index + 1;
    }

    private int getRChild(int index) {
        return 2 * index + 2;
    }

    private void duplicate(int[] a) {
        for (int i = 0; i < maxsize; i++) {
            heap[i] = a[i];
        }
        size = maxsize;
    }

    private void heapify(int index) {
        int largest = index;
        int left = getLChild(index);
        int right = getRChild(index);

        if (left < size && heap[left] > heap[largest])  
            largest = left;

        if (right < size && heap[right] > heap[largest])  
            largest = right;

        if (largest != index) {
            int temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;

            heapify(largest);
        }
    }

    public void buildHeap(int[] a) {
        duplicate(a);
        for (int i = (size / 2) - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    public void insert(int element) {
        if (size == maxsize) {
            System.out.println("Heap is Full");
            return;
        }

        heap[size] = element;
        int current = size;
        size++;

        while (current > 0 && heap[(current - 1) / 2] < heap[current]) {
            int temp = heap[current];
            heap[current] = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = temp;
            current = (current - 1) / 2;
        }
    }

    public int delete() {
        if (size == 0) {
            System.out.println("Heap is empty");
            return -1;
        }

        int k = heap[0];
        heap[0] = heap[--size];
        heapify(0);
        return k;
    }

    public void displayHeap() {
        for (int i = 0; i < size; i++) {
            System.out.print(heap[i] + " ");
        }
        System.out.println();
    }
}
