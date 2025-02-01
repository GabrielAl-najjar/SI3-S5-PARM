# Projet PARM SI3

Voir la documentation en PDF dans le dossier `doc`.

## Parser d'assembleur ARM

Le parser a été écrit en C++, cmake est utilisé pour la compilation. 
Pour le compiler, il suffit de se placer dans le dossier `assembly_parser` situé dans le dossier `code_asm` et de lancer les commandes suivantes :
```bash
cmake .
```
dans le but de générer les fichiers de configuration de cmake, puis
```bash
make
```
pour compiler le programme.

Enfin le programme peut être lancé avec la commande suivante :
```bash
./out/assembly_parser <fichier_asm>
```

## En-têtes C

| Programme | Description |
|-|-|
| crypto | Cryptographie |
| fixed | Nombres décimaux à virgule fixe |
| math | Outils mathématiques |
| parm | En-tête principale |
| stdio | Entrées/sorties textuelles (clavier, terminal) |
| string | Implémentation basique de chaînes |
| string2 | Autre implémentation basique de chaînes |
| trigo | Fonctions trigonométriques (séries de Taylor) |
| utils | Outils de débogage |
| video | Écran matriciel |

## Programmes fournis en exemple

### Programmes C

| Programme | Description |
|-|-|
| calckeyb		| Calculatrice avec clavier et terminal                                                    |
| calculator	| Calculatrice avec DIP-switches                                                           |
| simple_add | Effectue l'addition de deux variables et l'affiche dans RES
| testfp		| Démonstration des macros de nombres à virgule fixe                                       |
| tty			| Affiche "Projet PARM" dans le terminal                                                     |

## MMIO

Voir `parm.h` pour la documentation technique des broches.