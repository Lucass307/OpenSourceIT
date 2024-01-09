#include "unity.h"


// Exemple de déclaration pour SDL_Init
int SDL_Init(int flags);

// Exemple de déclaration pour SDL_SetVideoMode
SDL_Surface* SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags);


// Inclure le fichier source du programme principal (main.c)
#include "main.c"

// Définir les fonctions externes simulées (mocks)
int SDL_Init(int flags) {
    // Simuler le comportement de SDL_Init
    return 0;  // Par exemple, toujours renvoyer 0 pour simuler une initialisation réussie
}

SDL_Surface* SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags) {
    // Simuler le comportement de SDL_SetVideoMode
    return (SDL_Surface*)malloc(sizeof(SDL_Surface));  // Par exemple, allouer dynamiquement une surface factice
}


// Fonction de configuration avant les tests
void setUp(void) {
    // Initialisation, le cas échéant
}

// Fonction de nettoyage après les tests
void tearDown(void) {
    // Libération de ressources, le cas échéant
}

// Fonction de test pour le programme principal
void test_main(void) {
    // Appel de la fonction principale à tester
    main(0, NULL);

}

// Programme principal pour exécuter les tests
int main(void) {
    UNITY_BEGIN();

    // Ajout des tests
    RUN_TEST(test_main);

    return UNITY_END();
}
