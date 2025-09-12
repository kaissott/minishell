## Minishell

Un mini-interpréteur de commandes POSIX, inspiré de bash, implémenté en C. Il gère la lecture interactive, le parsing (tokenisation, expansion, word splitting), l’exécution de commandes simples et en pipeline, la redirection, les here-docs, les variables d’environnement et plusieurs builtins.

## Sommaire

- Présentation
- Fonctionnalités
- Démonstration rapide
- Installation
- Compilation
- Utilisation
- Builtins supportés
- Redirections et pipes
- Variables d’environnement et expansion
- Gestion des erreurs et codes de retour
- Architecture
- Dépendances & compatibilité

## Présentation

`minishell` est une implémentation pédagogique d’un shell minimaliste conforme aux règles du projet 42. L’objectif est d’offrir une expérience proche de bash pour les comportements demandés, avec une architecture claire et un code robuste.

## Fonctionnalités

- Lecture interactive via `readline` avec historique.
- Parsing complet en plusieurs passes : tokenisation → expansion (`$VAR`, `$?`) → word splitting → préprocess → parsing final.
- Exécution de commandes simples et chaînées par des pipes.
- Redirections d’entrée et de sortie (`<`, `>`, `>>`) et here-doc (`<<`).
- Gestion des signaux (Ctrl-C, Ctrl-\, Ctrl-D) et des codes d’erreur.
- Environnement géré sous forme de liste chaînée, conversion en tableau pour `execve`.
- Builtins: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`.

## Démonstration rapide

```bash
make
./minishell
> echo "Hello"
Hello
> ls | wc -l
42
> cat << EOF | grep hello
hello world
EOF
hello world
```

## Installation

Prérequis:

- Compilateur C compatible (cc/clang/gcc)
- `readline` installé
- `make`

Sur macOS (Homebrew):

```bash
brew install readline
```

## Compilation

```bash
make
```

La cible construit la bibliothèque `libft` puis lie `minishell` avec `-lreadline` (les chemins Homebrew sont gérés dans le `Makefile`).

Commandes utiles:

- `make` : build complet
- `make clean` : supprime les objets
- `make fclean` : clean complet (libft + binaire)
- `make re` : recompile tout

## Utilisation

```bash
./minishell
```

- Invite par défaut: `> `
- Historique actif si l’entrée est un TTY
- `Ctrl-D` ferme proprement le shell

## Builtins supportés

- `echo [args...]` : affiche les arguments
- `cd [dir]` : change de répertoire (`~`, `--`, `-` gérés)
- `pwd` : affiche le répertoire courant
- `export NAME=VALUE` : définit/maj une variable d’environnement (validation d’identifiant)
- `unset NAME` : supprime une variable d’environnement
- `env` : affiche l’environnement
- `exit [status]` : quitte le shell (libération mémoire et historique)

## Redirections et pipes

- Entrée: `< file`
- Sortie (truncate): `> file`
- Sortie (append): `>> file`
- Here-doc: `<< LIMITER` (gestion des signaux et fermeture propre)
- Pipes: `cmd1 | cmd2 | cmd3`

## Variables d’environnement et expansion

- Expansion de `$VAR` et de `$?` (dernier code de retour)
- `export` met à jour `env`, remplacé si variable existante
- Word splitting après expansion conformément aux règles implémentées

## Gestion des erreurs et codes de retour

- Codes POSIX respectés autant que possible
- `g_sig_mode` relaie les signaux dans le code de retour (`128 + signal` lorsqu’applicable)
- Émissions d’erreurs cohérentes (stderr) et sorties propres via gestion centralisée

## Architecture

Répertoires principaux:

- `src/` : code source
  - `exec/` : exécution, pipes, duplication de descripteurs, utils
  - `exec/builtins/` : implémentations des builtins
  - `parsing/` : pipeline de parsing (tokenisation, expansion, splitting, parse final)
- `includes/` : en-têtes (`minishell.h`, parsing, exec, structures)
- `libft/` : librairie utilitaire (string, listes, etc.)

Fichiers clés:

- `src/minishell.c` : boucle interactive, gestion signaux, pipeline parsing → exécution
- `includes/minishell.h` : includes globaux, constantes, `g_sig_mode`
- `Makefile` : construction du binaire `minishell`

Un schéma d’ensemble figure dans `docs/ARCHITECTURE.md`.

## Dépendances & compatibilité

- `readline` (headers et lib)
- `libft` (fournie dans le dépôt)
- macOS (Homebrew) et Linux supportés; adaptez les chemins de `readline` si nécessaire
