# Cahier des Charges simplifié

Automates à simuler :
- 1D
- 2D (jeu de la vie)

## Architecture :
- Pouvoir intégrer facilement de nouveaux types d'automates sans tout casser
    + Intégrer un automate de notre choix pour le prouver
- Faciliter l'ajout des composants suivants :
    + Nouveaux automates cellulaires
    + Nouveaux générateurs d'états pour un automate
    + Modification de la partie IHM sans tout casser

## Fonctionnalités

### Configuration automate
- choisir l'état initial: cellule par cellule ou bien parmi des propositions
- pour le 1D: définir le nombre de cases, nombre d'états, règle de transition
- pour le jeu de la vie: définir dimensions de matrices, nombre de voisins min et max pour être en vie ou non

### Sauvegarde et chargement
- save / load automate
- save / load conf
- Stockage csv / xml / bdd au choix

### Simulation
- Start / stop / reset d'une simulation
- Pas la même représentation graphique selon la dimension
    + lecture simple avec vitesse de lecture configurable
    + lecture pas à pas

## Problèmes :
- comment intégrer la dimension
