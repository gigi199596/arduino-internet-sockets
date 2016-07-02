#Preamble - Préambule
This is my first project on github, feel free to give me advices in the "Issues" tab. <br>
Ceci est mon premier projet sur github, n'hésitez pas à me donner des conseils ou votre avis dans la section "Issues". <br>
The first part of this "readme" file is in english, the second part is in french. <br>
La première partie de ce fichier "readme" est en anglais, la seconde partie est en français. <br>
#Arduino internet sockets
##Or how to control some socket with a low cost arduino server
I decided to make this project on github for the french community due to a lack of well documented projects in french. The main goal of the project is to learn and build concrete stuff to simplifies the every day life and allow access to the technology for anyone. And last but not least: reduce costs with low costs chips like arduino's.

#What you will need
1x Arduino microcontroller pro mini based on ATMEGA328 or any card with better performances <br>
1x relay card with one or many relays (you will only need to change the code to adapt to the number of sockets used. <br>
1x 5v ACDC transformer. <br>
1x circuit ENC28J60 (this is the board which is connecting the Arduino to the internet). <br>
(optionnal) 1x IR remote control <br>
(optionnal) 1x board with some switches to turn the sockets on/off manually <br>
(optionnal) 1x thermal sensor (in the case we want to remotely control a radiator) <br>

#Libraires to import 
[Bounce2](https://github.com/thomasfredericks/Bounce2): to avoid bounce when pushing on switches. <br>
[EtherCard](https://github.com/jcw/ethercard): act as the driver of the ENC28J60 module. <br>

#Arduino et ses prises controlées à travers le net
##Ou comment contrôler des prises avec un server arduino "lowcost"
J'ai décidé de réaliser ce projet github en raison du manque de projets concrets bien documentés en français. Je le traduis aussi en anglais afin de le partager avec cette magnifique communauté qui est celle des technologie des IoT (Internet of Things ou [l'internet des objets](https://fr.wikipedia.org/wiki/Internet_des_objets)). L'objectif principal de ce projet est d'apprendre et de réaliser des projets concrets qui me permettent de simplifier les choses de la vie de tous les jours et de permettre l'accès à la technologie à quiconque s'y intéresse. Et le plus important c'est de réduire les couts de cette technologie.

##Matériel utilisé
1x microcontrôleur Arduino pro mini ATMEGA328 ou n'importe quelle carte arduino plus puissante <br>
1x carte avec 1 ou plusieurs relais (il suffira de changer le code pour l'adapter au nombre de prises utilisées) <br>
1x transformateur ACDC 5v <br> 
1x circuit ENC28J60 (c'est le circuit qui relie le microcontroleur à l'internet via une prise RJ45) <br>
(optionnel) 1x télécommande avec capteur IR (InfraRouge) <br>
(optionnel) 1x circuit avec des boutons pour allumer manuellement les prises <br>
(optionnel) 1x un capteur de température (dans le cas ou l'on voudrait commander un radiateur à distance) <br>

##Bibliothèques à importer
[Bounce2](https://github.com/thomasfredericks/Bounce2): afin d'éviter les rebonds lorsque l'on presse sur les boutons. <br>
[EtherCard](https://github.com/jcw/ethercard): afin de prendre en charge le module ENC28J60

