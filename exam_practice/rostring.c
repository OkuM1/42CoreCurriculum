#include <unistd.h>

void write_word(char *start, char *end)
{
    while (start <= end)
    {
        write(1, start, 1);
        start++;
    }
}

int main(int argc, char **argv)
{
    char *str;
    char *first_word_start;
    char *first_word_end;

    if (argc > 1)
    {
        str = argv[1]; // Initialize str to the input string
        int index = 0; // Index to keep track of the current position in the string
        while (str[index] != '\0' && (str[index] == ' ' || str[index] == '\t')) 
            index++;
        first_word_start = &str[index]; // Mark the start of the first word
        while (str[index] != '\0' && str[index] != ' ' && str[index] != '\t')
            index++;
        first_word_end = &str[index - 1]; // Adjust to mark the last character of the first word
        if (str[index]) 
        {
        while (str[index]) 
        {
            if (str[index] == ' ' || str[index] == '\t') 
            {
                while (str[index] == ' ' || str[index] == '\t')
                    index++;
                write(1, " ", 1);
            } 
            else 
            {
                write(1, &str[index], 1);
                index++;
            }
        }
            write(1, " ", 1);
        }
        write_word(first_word_start, first_word_end);
    }
    write(1, "\n", 1);
    return 0;
}