#include <stdio.h>
#include <stdint.h>

#define Page_Size 4096
#define Table_Entry_Size 1024

uint32_t Page_Directory_Base_Address = 0x00401000;
uint32_t Page_Directory[Table_Entry_Size];
uint32_t Page_Table[Table_Entry_Size][Table_Entry_Size];

void Table_Entries() {
    Page_Directory[0x001] = 0x00105;
    Page_Directory[0x002] = 0x00106;
    Page_Directory[0x010] = 0x00105;
    Page_Directory[0x1A3] = 0x0020A;

    Page_Table[0x00105][0x20F] = 0x0035B;
    Page_Table[0x0020A][0x03C] = 0x0041F;
}

void get_physical_address(uint32_t logical_address) {
    uint16_t pd_index = logical_address >> 22;
    uint16_t pt_index = (logical_address >> 12) & 0x3FF;
    uint16_t offset = logical_address & 0xFFF;

    uint32_t pt_frame = Page_Directory[pd_index];
    uint32_t pt_base = pt_frame * Page_Size;
    uint32_t page_frame = Page_Table[pt_frame][pt_index];
    uint32_t physical_address = (page_frame * Page_Size) + offset;

    printf("Logical Address: 0x%08X\n", logical_address);
    printf("PD Index: 0x%03X, PT Index: 0x%03X, Offset: 0x%03X\n", pd_index, pt_index, offset);
    printf("Page Table Frame: 0x%05X, Base Address: 0x%08X\n", pt_frame, pt_base);
    printf("Physical Address: 0x%08X\n\n", physical_address);
}

int main() {
    Table_Entries();
    uint32_t logical_address_1 = 0x00420FABC;
    uint32_t logical_address_2 = 0x068C03C12;
    get_physical_address(logical_address_1);
    get_physical_address(logical_address_2);
    return 0;
}