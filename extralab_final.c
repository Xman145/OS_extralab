#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>



int main()
{
        struct termios tty,safetty;
        if (isatty(fileno(stdout)) == 0){
                fprintf(stderr,"stdout is not a terminal\n");
                exit(EXIT_FAILURE);
        }
        tcgetattr(fileno(stdout),&tty);
        safetty  =tty;
        tty.c_lflag &= ~ICANON; /* non canon */
        tty.c_lflag &= ~ISIG; /* no special symbols such as QUIT INTR  SUSP DSUSP*/
        tty.c_lflag &= ~ECHO; /*NO ECHO */
        tty.c_cc[VMIN] = 1; /* minimal number of symbols is one*/
        tcsetattr(fileno(stdout),TCSAFLUSH, &tty);
        setbuf(stdout,(char*)NULL);
        printf("What is your Russian phone number?\n");
        char character;
        for (int i = 0; i <11; i++)
        {
                read(fileno(stdin),&character,1);
                if ((character >= '0') && (character <= '9'))
                {
                        if (i == 0)
                        {
                                if ((character == '8') || (character == '7'))
                                {
                                        putchar('+');
                                        putchar('7');
                                        putchar(' ');
                                }
                                else
                                {
                                        tcsetattr(fileno(stdout),TCSANOW,&safetty);
                                        fprintf(stderr,"Incorrect format, I need a Russian phone number\n");
                                        exit(EXIT_FAILURE);
                                }
                        }
                        else
                        {
                                if (i == 1)
                                {
                                        putchar('(');
                                        putchar(character);
                                }
                                else
                                {
                                        if (i == 3)
                                        {
                                                putchar(character);
                                                putchar(')');
                                                putchar(' ');
                                        }
                                        else
                                        {
                                                if ((i == 6) || (i == 8))
                                                {
                                                        putchar(character);
                                                        putchar('-');
                                                }
                                                else
                                                {
                                                        if (i == 10)
                                                        {
                                                                putchar(character);
                                                                putchar('\n');
                                                        }
                                                        else
                                                        {
                                                                putchar(character);
                                                        }
                                                }
                                        }
                                }
                        }
                }
                else
                {
                        tcsetattr(fileno(stdout),TCSANOW,&safetty);
                        fprintf(stderr,"\nCharacter is not a number\n");
                        exit(EXIT_FAILURE);
                }
        }
        printf("That is your phone number\n");
        tcsetattr(fileno(stdout),TCSANOW,&safetty);
        exit(EXIT_SUCCESS);
}

