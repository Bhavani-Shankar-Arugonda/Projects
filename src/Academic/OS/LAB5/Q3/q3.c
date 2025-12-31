#include <stdio.h>
#include <stdint.h>

#define NUM_SEGMENTS 5

typedef struct {
    uint32_t base_address;
    uint32_t limit;
} Segment_Entry;

Segment_Entry Segment_Table[NUM_SEGMENTS];

void init_segment_table() {
    Segment_Table[0].base_address = 219;
    Segment_Table[0].limit = 600;
    Segment_Table[1].base_address = 2300;
    Segment_Table[1].limit = 14;
    Segment_Table[2].base_address = 90;
    Segment_Table[2].limit = 100;
    Segment_Table[3].base_address = 1327;
    Segment_Table[3].limit = 580;
    Segment_Table[4].base_address = 1952;
    Segment_Table[4].limit = 96;
}

void get_physical_address(uint32_t segment, uint32_t offset) {
    if (segment >= NUM_SEGMENTS || offset >= Segment_Table[segment].limit) {
        printf("Logical Address: (Segment %u, Offset %u) -> Segmentation Fault\n\n", segment, offset);
    } else {
        uint32_t physical_address = Segment_Table[segment].base_address + offset;
        printf("Logical Address: (Segment %u, Offset %u) -> Physical Address: %u\n\n", segment, offset, physical_address);
    }
}

int main() {
    init_segment_table();
    get_physical_address(0, 430);
    get_physical_address(1, 10);
    get_physical_address(2, 101);
    get_physical_address(3, 500);
    get_physical_address(4, 100);
    return 0;
}