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
    strcpy(s->file_name, fName);
    if (s->debug_mode)
        printf("Debug: file name set to '%s'\n", fName);
        
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
    printf("not implemented yet\n");
}
void MemoryDisplay(state* s){
    printf("not implemented yet\n");
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