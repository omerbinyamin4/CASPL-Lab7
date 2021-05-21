#define  NAME_LEN  128
#define  BUF_SZ    10000



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


typedef struct {
  char debug_mode;
  char file_name[NAME_LEN];
  int unit_size;
  unsigned char mem_buf[BUF_SZ];
  size_t mem_count;
  /*
   .
   .
   Any additional fields you deem necessary
  */
} state;

struct fun_desc{
    char *name;
    void (*fun)(state*);
};
char* unit_to_format(int unit, int isDec) {
    static char* formats_d[] = {"%hhd\n", "%hd\n", "No such unit", "%d\n"};
    static char* formats_x[] = {"%#hhx\n", "%#hx\n", "No such unit", "%#x\n"};
    if (isDec) return formats_d[unit-1];
    else return formats_x[unit-1];
}
void print_units(FILE* output, char* buffer, int count, int decFormat, state *s) {
    char* end = buffer + (s->unit_size)*count;
    while (buffer < end) {
        //print ints
        int var = *((int*)(buffer));
        fprintf(output, unit_to_format(s->unit_size, decFormat), var);
        buffer += (s->unit_size);
    }
}
void ToggleDebugMode(state* s){
    if (s->debug_mode){
        s->debug_mode = 0;
        printf("Debug flag now off\n");
    }
    else {
        s->debug_mode = 1;
        printf("Debug flag now on\n");
    }
}
void SetFileName(state* s){
    
    char fName[128];
    printf("Enter file name:\n");
    fgets(fName, 128, stdin);
    sscanf(fName, "%s", s->file_name);
    if (s->debug_mode)
        printf("Debug: file name set to '%s'\n", s->file_name);
        
}
void SetUnitSize(state* s){
    char input_size[50];
    int size;
    printf("Enter size:\n");
    fgets(input_size, 50, stdin);
    sscanf(input_size, "%d", &size);
    if (size == 1 || size == 2 || size == 4){
        s->unit_size = size;
        if (s->debug_mode)
            printf("Debug: set size to %d\n", size);
    }
    else printf("Error: invalid number\n");    
}
void LoadIntoMemory(state* s){
    char buffer[BUF_SZ];
    int input_location, input_length;
    FILE* file;
    if (strcmp(s->file_name, "") == 0) {
        printf("Invalid file name: name cannot be empty\n");
        return;
    }
    file = fopen(s->file_name, "r");
    if (file == NULL) {
        perror("Unable to open file: ");
        return;
    }
    printf("Please enter <location> <length>\n");
    fgets(buffer, BUF_SZ+9, stdin);
    sscanf(buffer, "%x %d", &input_location, &input_length);
    if (s->debug_mode)
        printf("File name: %s, location: %x, length %d\n", s->file_name, input_location, input_length);
    fseek(file, input_location, SEEK_SET);
    fread(s->mem_buf, s->unit_size, input_length, file);
    fclose(file);
    printf("Loaded %d units into memory\n", input_length);
}
void MemoryDisplay(state* s){
    char buffer[100];
    int units;
    int addr;
    int i;
    int j;
    printf("Enter address and length:\n");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%x %d", &addr, &units);
    printf("Hexadecimal\n===========\n");
    print_units(stdout, buffer + addr, units, 0, s);
    printf("\nDecimal\n=======\n");
    print_units(stdout, buffer + addr, units, 1, s);

    }
void SaveIntoFile(state* s){
    printf("not implemented yet\n");
}
void MemoryModify(state* s){
    printf("not implemented yet\n");
}
void Quit(state* s){
    if (s->debug_mode)
        printf("Debug: quitting\n");
    exit(0);
}


int main(int argc, char **argv) {
    struct fun_desc menu[9] = { {"Toggle Debug Mode", ToggleDebugMode},
                                {"Set File Name", SetFileName},
                                {"Set Unit Size", SetUnitSize},
                                {"Load Into Memory", LoadIntoMemory},
                                {"Memory Display", MemoryDisplay},
                                {"Save Into File", SaveIntoFile},
                                {"Memory Modify", MemoryModify},
                                {"Quit", Quit},
                                {NULL, NULL}
                                };

    char func_num[50];
    int op;
    int i;
    int bound;
    bound = sizeof(menu)/sizeof(struct fun_desc) - 1;
    state *s = (state*)malloc(sizeof(state));
    s->debug_mode = 0;

    while (1){
        op = -1;
        printf("choose action:\n");
        for (i=0; i < (sizeof(menu)/sizeof(struct fun_desc))-1; i++){
            printf("%i)-%s\n", i+1, (menu+i)->name);
        }
        printf("Option: ");
        fgets(func_num, 50, stdin);
        sscanf(func_num, "%d", &op);
            if (op < 1 || op > bound){
                printf("Not within bounds\n");
                exit(0);
            }
            else{
                (menu[func_num[0] - 49].fun)(s);
                printf("DONE.\n\n");
            }
        
    }
    
}