#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <.h>

void afficher_valeur(void *donnee, char type)
{
    if (type == 'i')
        printf("%d\n", *(int *)donnee);
    else if (type == 'c')
        printf("%c\n", *(char *)donnee);
    else if (type == 'f')
        printf("%f\n", *(float *)donnee);
}

int main()
{
    int nombre = 42;
    char lettre = 'A';
    float decimal = 3.14;

    afficher_valeur(&nombre, 'i');  // Affiche 42
    afficher_valeur(&lettre, 'c');  // Affiche A
    afficher_valeur(&decimal, 'f'); // Affiche 3.14
}

/*
le void * permet ensuiite de caster dans le sens 
que l on veut 
fonction qui prends un void *;

void fonction(void *donnee,char type)
{
    printf("%d\n", *(int *)donnee);
    printf("%c\n", *(char *)donnee);
    printf("%f\n", *(float *)donnee);
}
*/