# PROJET IRC

## Règles générales

- Votre programme ne doit en aucun cas se bloquer (même s'il manque de mémoire).
- Il ne doit pas s'arrêter de manière inattendue.
- Si cela se produit, votre projet sera considéré comme non fonctionnel
votre note sera de 0.
- Vous devez fournir un Makefile qui compilera vos fichiers sources. Il ne doit pas
relink.
- Votre Makefile doit au moins contenir les règles suivantes :
	- $(NAME), all, clean, fclean et re.
- Compilez votre code avec c++ et les drapeaux -Wall -Wextra -Werror
- Votre code doit être conforme à la norme C++ 98.
- Essayez de toujours développer en utilisant le plus de fonctionnalités C++ possible (par exemple, choisissez
 - <cstring> plutôt que <string.h>). 
- Les bibliothèques externes et les bibliothèques Boost sont interdites.

# Partie obligatoire

## Nom du programme:
	
	- ircserv

## Fichiers:

	- Makefile -> NAME, all, clean, fclean, re
	- *.{h, hpp}
	- *.cpp
	- *.tpp
	- fichiers de configuration optionnels

## Arguments:

	- port: le port d ecoute.
	- password: the connection password.

## Fonctions utilisables:
	
	- Toutes en C++98.
	- socket
	- close
	- setsockopt
	- getsockname
	- getprotobyname
	- gethostbyname
	- getaddrinfo
	- freeaddrinfo
	- bind
	- connect
	- listen
	- accept
	- htons
	- htonl
	- ntohs
	- ntohl
	- inet_addr
	- inet_ntoa
	- send
	- recv
	- signal
	- sigaction
	- lseek
	- fstat
	- fcntl
	- poll

## Description:

• Un serveur IRC en C++98:

	- Vous ne devez pas développer un client.
	- Vous ne devez pas gérer la communication de serveur à serveur.

• Votre exécutable sera exécuté comme suit :

```cpp
./ircserv <port> <password>
```

• port:

	- Le numéro de port sur lequel votre serveur IRC écoutera les connexions IRC entrantes.

• password:

	- Le mot de passe de connexion.
 	- Il sera nécessaire à tout client IRC qui essaiera de se connecter à votre serveur.
  
> Même si poll() est mentionné dans le sujet et l'échelle d'évaluation, vous pouvez
> utiliser un équivalent tel que select(), kqueue() ou epoll().

## Exigences:

- Le serveur doit être capable de gérer plusieurs clients en même temps et de ne jamais se bloquer.
- forkc() n'est pas autorisée. Toutes les opérations d'E/S doivent être non bloquantes.
- Un seul poll() (ou équivalent) peut être utilisé pour gérer toutes ces opérations (lecture, écriture, mais aussi écoute, etc...).

>  [!CAUTION]
> Comme vous devez utiliser des descripteurs de fichiers non bloquants, il est possible d'utiliser 
> des fonctions de lecture/récupération ou d'écriture/envoi sans poll() (ou équivalent), et votre serveur ne serait pas bloquant.
> 
> Mais il consommerait plus de ressources système.
> Ainsi, si vous essayez de lire/recourir ou d'écrire/envoyer dans n'importe quel descripteur de fichier
> sans utiliser poll() (ou équivalent), votre note sera de 0.
