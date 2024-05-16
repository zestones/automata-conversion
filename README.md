# Automaton Conversion (AFN to AFD)

This project provides a C implementation for converting a Nondeterministic Finite Automaton (AFN) into a Deterministic Finite Automaton (AFD).
The project includes various functionalities such as defining states and alphabets, adding transitions, and checking if a word is accepted by the automaton.

## How to use

To use the project, you need to include the `afn.h` and `afd.h` headers in your code. The `afn.h` header provides the necessary functions to create and manipulate a Nondeterministic Finite Automaton, while the `afd.h` header provides the necessary functions to compute the Deterministic Finite Automaton.

Here is an example of how to use the project:

```c
#include <stdio.h>
#include "afn.h"
#include "afd.h"

int main() {
    AFN automate = creer_afn();         // Create a new empty AFN

    Etat etats[] = {1, 2, 3};           // Define the states
    definir_etats(&automate, etats, 3); // Add the states to the AFN

    char *alphabets = "ab";             // Define the alphabets and Add the alphabets to the AFN
    definir_alphabets(&automate, alphabets, 2);

    // Define the initial and final states
    ajouter_etat_initial(&automate, 1);
    ajouter_etat_final(&automate, 3);

    // Add transitions
    ajouter_transition(&automate, 1, 'a', 1);
    ajouter_transition(&automate, 1, 'b', 1);
    ajouter_transition(&automate, 1, 'a', 2);
    ajouter_transition(&automate, 2, 'b', 3);

    afficher_afn(automate_simple_ab);           // Display the AFN
    afd = determiniser(automate_simple_ab);     // Convert the AFN to AFD
    afficher_table_transition(afd.table, automate_simple_ab.alphabets); // Display the transition table
    afficher_afd(afd); // Display the AFD

    // Check if the word is accepted by the AFD
    mot = "a";
    est_accepte = est_mot_accepte(afd.afd, mot);
    fprintf(stdout, "> Le mot \"%s\" est : %s \n", mot, est_accepte ? "Accepte" : "Non Accepte");


    return 0;
}
```

## Testing

To test the project, you can run the following command:

```bash
make && ./main
```

This will compile the project and run the main program, which computes the Deterministic Finite Automaton for a given Nondeterministic Finite Automaton and checks if a word is accepted by the automaton.
