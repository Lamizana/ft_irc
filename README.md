<div align="center">

<p align="center">
    <a href="https://isocpp.org/"><img src="https://img.shields.io/badge/Language-C%2B%2B98-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++98"></a>
    <a href="https://datatracker.ietf.org/doc/html/rfc1459"><img src="https://img.shields.io/badge/Protocol-RFC_1459-000000?style=for-the-badge&logo=internetexplorer&logoColor=white" alt="RFC 1459"></a>
    <a href="https://github.com/42School/norminette"><img src="https://img.shields.io/badge/Code_Style-Norminette-brightgreen?style=for-the-badge&logo=42&logoColor=white" alt="Norminette"></a>
    <a href="https://hexchat.github.io/"><img src="https://img.shields.io/badge/Compatibility-HexChat-02A8F3?style=for-the-badge&logo=chat&logoColor=white" alt="HexChat"></a>
    <a href="https://fr.wikipedia.org/wiki/École_42"><img src="https://img.shields.io/badge/Licence-42-lightgrey?style=for-the-badge&logo=42&logoColor=white" alt="Licence 42"></a>
</p>

# FT_IRC

<p align="center">
  <strong>Projet 42</strong>
</p>

<p align="center">
  <em>Serveur IRC développé en C++98 (RFC 1459)<br>Permet à plusieurs clients de communiquer en temps réel via TCP/IP (IPv4)<em>
</p>

<a href="https://lamizana.github.io/ZehdBox/projets/ft_irc/">
  <img src="https://img.shields.io/badge/Portfolio-ZehdBox-8A2BE2?style=for-the-badge&logo=githubpages&logoColor=white" alt="Portfolio ZehdBox">
</a>

</div>

---



## Sommaire
- [Fonctionnalités](#fonctionnalités)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Compilation](#compilation)
- [Lancement](#lancement)
- [Utilisation](#utilisation)
- [HexChat](#hexchat)
- [Structure du projet](#structure-du-projet)
- [Tests](#tests)
- [Limitations connues](#limitations-connues)
- [Auteurs](#auteurs)

## Fonctionnalités

- Authentification par mot de passe (`PASS`)
- Pseudonyme et nom d'utilisateur (`NICK`, `USER`)
- Canaux publics `#` et locaux `&` (`JOIN`, `PART`)
- Messages privés et messages de canal (`PRIVMSG`)
- Opérateurs de canaux : `KICK`, `INVITE`, `TOPIC`, `MODE`
- Modes de canaux : `+i`, `+t`, `+k`, `+o`, `+l`
- Gestion multi-clients non bloquante via `select()`
- Bonus : bot Pierre-Papier-Ciseaux (`BOT`) et compatibilité HexChat (`CAP`)

## Prérequis

- Système Unix/Linux (macOS pris en charge)
- Compilateur `c++` compatible norme C++98
- `make`
- `nc` ou un client IRC (HexChat, irssi, WeeChat...) pour se connecter

## Installation

### Récupération du dépôt

```bash
git clone https://github.com/Lamizana/ft_irc.git
cd ft_irc
```

> [!NOTE]
> Variante SSH : `git clone git@github.com:Lamizana/ft_irc.git`

## Compilation

```bash
make        # règle all
```
- Le Makefile fournit les règles : `all`, `clean`, `fclean` et `re`.
- Compilation avec `c++` et les drapeaux `-Wall -Wextra -Werror` en norme C++98.
- Le Makefile ne relink pas.

```bash
make clean      # supprime les fichiers objets (.o)
make fclean     # supprime les objets + l'exécutable
make re         # fclean + all
```

## Lancement

```bash
./ircserv <port> <password>
```
- **port** : numéro de port sur lequel le serveur IRC écoutera les connexions entrantes.
- **password** : mot de passe de connexion requis pour tout client.

> Exemple :
```bash
./ircserv 6667 toto
```

## Utilisation

### Connexion avec nc
```bash
nc 127.0.0.1 6667
PASS toto
NICK toto
USER toto
JOIN #general
```

### Connexion avec un client IRC (HexChat, irssi, WeeChat...)
- Adresse : `127.0.0.1`
- Port    : `6667`
- Mot de passe : `toto`

### Commandes implémentées

| Commande | Description |
| --- | --- |
| CAP | Négociation de capacités (compatibilité client) |
| PASS | Authentification (mot de passe du serveur) |
| NICK | Définir / changer de pseudonyme |
| USER | Définir le nom d'utilisateur (inchangeable) |
| PRIVMSG | Message privé à un utilisateur ou à un canal |
| JOIN | Rejoindre ou créer un canal (#canal) |
| KICK | Éjecter un client d'un canal (opérateur) |
| INVITE | Inviter un client à un canal |
| TOPIC | Modifier ou afficher le thème d'un canal |
| MODE | Changer les modes du canal |
| PART | Quitter un canal |
| BOT | Bonus : jouer à Pierre-Papier-Ciseaux |

### Modes de canal (MODE)

| Mode | Description |
| --- | --- |
| +i / -i | Canal sur invitation uniquement |
| +t / -t | Restreindre TOPIC aux opérateurs |
| +k / -k | Définir / supprimer le mot de passe du canal |
| +o / -o | Donner / retirer le statut d'opérateur |
| +l / -l | Définir / supprimer la limite d'utilisateurs |

### Exécution des commandes

> [!IMPORTANT]
> - Chaque commande se tape sur **UNE SEULE ligne**, directement dans la connexion (nc ou client IRC), **sans slash** (le `/` est un raccourci propre aux clients graphiques, pas au protocole brut).
> - Les commandes sont **sensibles à la casse** : utilisez uniquement des **MAJUSCULES** (`PASS`, `NICK`, `JOIN`...).
> - Le mot de passe s'envoie sur la **même ligne** que `PASS` : `PASS toto` (jamais `PASS` sur une ligne puis `toto` sur la suivante).
> - Ordre obligatoire : `PASS` → `NICK` → `USER`. Le serveur répond alors `: 001 <pseudo> :Welcome to the IRC Network...`.
> - Les autres commandes (`JOIN`, `PRIVMSG`, `MODE`...) ne fonctionnent qu'**après** ce message de bienvenue.

| Ce que vous tapez | Effet |
| --- | --- |
| `PASS toto` | Authentification (doit correspondre au mot de passe de lancement) |
| `NICK alice` | Définit le pseudonyme (unique, max 9 caractères) |
| `USER alice` | Définit le nom d'utilisateur (inchangeable ensuite) |
| `JOIN #general` | Crée ou rejoint le canal `#general` |
| `JOIN #securise mdp` | Rejoint un canal protégé par mot de passe |
| `PRIVMSG #general :salut !` | Diffuse un message à tout le canal |
| `PRIVMSG bob :coucou` | Envoie un message privé à `bob` |
| `TOPIC #general :Bienvenue` | Modifie le sujet du canal |
| `TOPIC #general` | Affiche le sujet du canal |
| `INVITE bob #general` | Invite `bob` dans le canal |
| `KICK #general bob :troll` | Éjecte `bob` (opérateur requis) |
| `MODE #general +t` | Active un mode du canal (`i`, `t`, `k`, `o`, `l`) |
| `PART #general :a+` | Quitte le canal |
| `BOT PAPER` | Bonus : joue à Pierre-Papier-Ciseaux avec le BOT |

### Exemple de session :
```bash
./ircserv 6667 toto     # Terminal 1 : lancement du serveur

# Terminal 2 : connexion au serveur
nc 127.0.0.1 6667
PASS toto
NICK alice
USER alice
JOIN #general
TOPIC #general :Bienvenue
INVITE bob #general
PRIVMSG #general :salut tout le monde !
PART #general
```

## HexChat

### Installation (Ubuntu/Debian) :
```bash
sudo apt update
sudo apt install hexchat
```

### Lancement :
```bash
hexchat
```
- Fenêtre « Réseaux » : bouton **+ Add** pour créer un réseau.
- Onglet **Connexion** : cocher « Utiliser un mot de passe » et saisir `toto`.
- Onglet **Utilisateur** : définir le pseudo et le nom d'utilisateur.
- Dans « Serveurs », ajouter `127.0.0.1/6667` puis cliquer sur **Connecter**.

### Ou en commandes internes à HexChat :
```bash
/server 127.0.0.1 6667 toto
/join #general
```

### Exemple de session :
```bash
/server 127.0.0.1 6667 toto
/join #general
/topic #general Bienvenue
/msg #general salut tout le monde !
/msg alice coucou en privé
/invite alice #general
/kick #general alice troll    (opérateur requis)
/part #general
```

## Structure du projet

```
ft_irc/
├── Makefile              # règles all, clean, fclean, re
├── main.cpp              # boucle serveur (select) et gestion des connexions
├── define.hpp            # numerics et messages IRC
├── library.hpp           # bibliothèques et includes communs
├── utils.cpp / utils.hpp # helpers (trim, validation des arguments)
├── Channel/
│   └── Channel.cpp / Channel.hpp    # canal : utilisateurs, opérateurs, modes
├── Client/
│   ├── Client.cpp / Client.hpp      # client : socket, buffer, enregistrement
│   ├── bot.cpp, invite.cpp, join.cpp, kick.cpp   # handlers des commandes
│   ├── mode.cpp, nick.cpp, part.cpp, pass.cpp
│   └── prvmsg.cpp, topic.cpp, user.cpp
└── Server/
    ├── Server.cpp / Server.hpp      # logique serveur et dispatch
    ├── ServerDebug.cpp              # affichage de débogage (<<)
    ├── ServerMode.cpp               # implémentation des modes
    ├── ServerSwitch.cpp             # aiguillage des commandes
    └── allClient.cpp                # réponses NAMES/ENDOFNAMES
```

## Tests

### Connexion multiple
Ouvrir plusieurs terminaux et se connecter simultanément (`nc 127.0.0.1 <port>`) pour vérifier la gestion multi-clients.

### Réception de données partielles
Envoyer une commande en plusieurs fragments avec nc et Ctrl+D :
```bash
$> nc 127.0.0.1 6667
com^Dman^Dd
$>
```
`com`, puis `man`, puis `d` + Entrée reconstruisent la commande transmise au serveur.

### Commandes opérateurs
Créer un canal, donner `+o` à un utilisateur, puis tester `KICK`, `TOPIC` et `MODE`.

### Valgrind
```bash
valgrind --track-origins=yes --leak-check=full --track-fds=yes ./ircserv <port> <password>
```

## Limitations connues

- **PING/PONG non implémenté** : les clients IRC se déconnectent après ~60 s d'inactivité (« Ping timeout » dans HexChat).

---

## Auteurs

**Alex Lamizana** : Étudiant 42 Angoulême, spécialisation Data & IA

**mvitiell**

**nminotte**

<div align="center">

*Ce projet a été réalisé conformément à la norme et au sujet officiel de 42.*

</div>

---
