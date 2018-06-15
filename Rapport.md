# Projet LO21 - Autocell

_Par Samy Nastuzzi, Simon Bazin et Alexandre Brasseur_


[TOC]

## Préambule
L'application AutoCell a pour but d'implémenter des automates cellulaires à 1 et 2 dimensions afin de réaliser des simulations. Ces simulations peuvent être utiles notamment dans le domaine médicale, avec le développement de bactéries afin de prévoir des situations.
Un automate est une grille virtuelle, dont les dimensions peuvent être sélectionnées. De plus, l'évolution d'étape en étape suit des règles prédéfinies. Cette évolution concerne des cellules, ici des cases du tableau, qui possèdent des états. Ces états sont à définir et réprésentent un état de vie d'une cellule. Ainsi, les états basiques sont les états morts et vivant, qui indiquent le statut de la cellule. Pour passer d'un état à un autre, des règles sont définies et concernent le nombre de voisins entourant chaque case.
Cet automate concerne le 1D, 2D, 3D ou toute autre dimension.

Dans le cadre de ce projet, des automates cellulaires à 1 dimension et à 2 dimensions sont réalisés. Les états, règles et états de départs sont laissés au libre choix de l'utilisateur.
De plus, le célèbre Jeu de la Vie proposé par le mathématicien britannique John Horton Conway est implémenté.

Au sein de ce rapport, la définition de l'implémentation, la présentation de la structure du projet, et une explication des méthodes réalisées seront énoncées.


## Architecture du projet

Tous les fichiers C++ du projet se trouvent dans le dossier `projet/` :
- `interface/`: composants de l'interface Qt
- `autocell/` : l'ensemble des classes modélisant le problème Autocell

### Architecture MVC

L'architecture de notre projet est basé sur une architecture MVC: Model, View, Controller.
Les fichiers du dossier `autocell/` sont propres à l'implémentation du backend. Ils correspondent au Modèle(Model). Ils permettent de gérer les différentes structures.
Les fichiers du dossier `interface/` sont utilisés pour la construction de l'interface qui a été réalisée avec le logiciel Qt. Ceci représente la Vue (View). Toute l'interface graphique est réalisée au sein de ces fichiers seulement.
Une liaison entre l'interface et les structures permet de rendre dynamique l'utilisation.
Enfin, le Manager implémenté en Backend permet de contrôler (Controller) et superviser la bonne utilisation des automates. En effet, il est le seul à pouvoir autoriser la création, modification, suppression ou implémentation d'automates et autres attributs lui correspondant.

### Une architecture modulable

Tout d'abord, l'architecture MVC permet de séparer les différents éléments structurels et, ainsi, autorisent les développeurs à se concentrer sur les aspects souhaités de manipulation. L'architecture a donc été réalisée pour être la plus extensible possible.

Tout d'abord, toutes les classes ont été implémentées avec un maximum d'héritage. Ceci permet d'avoir des classes abstraites regroupant un maximum de fonctions et attributs en leur sain. De ce fait, si de nouveaux automates doivent être implémenter, ils pourront hériter des méthodes d'une classe mère qui leur apportera une implémentation légère. Au niveau du frontend comme du backend, le maximum de méthodes et d'attributs ont été implémenté au sein de la classe mère.


## Backend


## Frontend



