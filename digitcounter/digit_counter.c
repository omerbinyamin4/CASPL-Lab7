
int digit_ctr(char* input) {
    int i = 0;
    int counter = 0;
    while (input[i] != 0){
        if ((input[i] > 47) && (input[i] < 58))
            counter++;
        i++;
    }
    return counter;
}

int main(int argc, char **argv) {
    return 0;
}