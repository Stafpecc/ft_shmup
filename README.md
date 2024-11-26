# FT_SHMUP

---

### 👾 FT_SHMUP

FT_SHMUP est un projet développé dans le cadre d’un rush à 42. Inspiré de Space Invaders, ce shoot'em up met vos réflexes à rude épreuve :

- Pilotez un vaisseau spatial
- Esquivez les tirs ennemis
- Détruisez des vagues d’ennemis
- Utilisez des pouvoirs spéciaux grâce à des touches dédiées
- Survivez le plus longtemps possible (si le hasard ne vous achève pas d’abord 😅)


---


### 🏃 Qu’est-ce qu’un rush ?

Un rush est une sorte de hackathon à 42 en très peu de temps (souvent 48 heures) : les équipes doivent développer un projet complet. C’est une expérience intense qui demande un développement rapide et une bonne collaboration

FT_SHMUP est un rush qui se distingue par sa flexibilité : il offre beaucoup de liberté dans l’interprétation et le choix des fonctionnalités


---


### 🕹️ Lancer le jeu
Vous pouvez facilement lancer le jeu grâce à Docker. Suivez ces étapes :

Clonez le projet sur votre machine :

`git clone <url_du_dépôt>`
`cd <nom_du_dépôt>`
Construisez et exécutez le jeu avec la commande suivante :

`make docker`
Le jeu s’ouvrira automatiquement. Bonne chance, pilote ! 🚀


---


### 🎮 Contrôles et personnalisation
Le jeu est conçu pour un clavier *QWERTY*, et certaines touches permettent d'utiliser des pouvoirs spéciaux. Si vous utilisez un clavier *AZERTY* ou souhaitez modifier les touches :

Ouvrez le fichier `ft_move.c`.
Modifiez la fonction getmv pour définir les touches adaptées à votre configuration









