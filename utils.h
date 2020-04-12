#ifndef UTILS
#define UTILS


int letter2order(char letter)
{
    int order = letter;
    if (order > 90)
        order -= 32;
    return order - 65;
}
char order2letter(int order)
{
    char letter = order + 65;
    return letter;
}
char getBig(char letter)
{
    if (letter >= 'a' && letter <= 'z')
    {
        letter -= 32;
    }
    return letter;
}       


#endif