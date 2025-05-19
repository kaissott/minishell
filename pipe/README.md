# Pipex

Le projet Pipex de base consiste à recréer le fonctionnement du pipe (|) sous Unix en permettant d’exécuter deux commandes en les chaînant. Il simule le comportement suivant :
```sh
< infile cmd1 | cmd2 > outfile
```

# Pipex Bonus

Pipex Bonus est une version améliorée du projet Pipex, un exercice typique de l'école 42 qui consiste à recréer le fonctionnement du pipe en ligne de commande sous Unix.

## Description

Ce programme permet d'exécuter une série de commandes en les chaînant à l'aide de pipes, en gérant correctement les entrées et sorties standard. Il inclut la gestion de "here_doc" pour les entrées interactives.

## Fonctionnalités
- Exécution de plusieurs commandes en pipeline.
- Gestion des fichiers d'entrée et de sortie.
- Support du mode "here_doc".
- Gestion des erreurs et des processus enfants.

## Utilisation

Exécution avec des fichiers :
```sh
./pipex infile "cmd1" "cmd2" ... "cmdN" outfile
```

Exécution avec here_doc :
```sh
./pipex here_doc LIMITER "cmd1" "cmd2" ... "cmdN" outfile
```

### Exemples

Exécution standard :
```sh
./pipex input.txt "ls -l" "grep .c" output.txt
```

Utilisation de here_doc :
```sh
./pipex here_doc END "cat" "wc -l" output.txt
```

## Détails des fichiers

- `main.c` : Gère l'exécution principale du programme, la création des processus et l'attente des enfants.
- `open.c` : Gère l'ouverture des fichiers et la gestion du here_doc.
- `ft_split_slash_bonus.c` : Implémente une version modifiée de ft_split qui ajoute un slash `"/"` à chaque sous-chaîne.
- `error_bonus.c`  : Contient les fonctions de gestion des erreurs, telles que la vérification des arguments (check_args), la gestion des erreurs d'exécution (error_exec_b), et la libération de mémoire (free_tab).
- `strrchr_slash_bonus.c` : Implémente une fonction (strrchr_slash) qui recherche la présence d'un caractère spécifique (/) dans une chaîne et retourne 1 si trouvé, 0 sinon.

## Auteurs

- Karamire ([karamire@student.42.fr](mailto:karamire@student.42.fr))


