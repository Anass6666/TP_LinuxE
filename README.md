# TP Linux Embarqué
# 1.2 Démarrage
J'ai inséré la carte SD programmé, et j'ai également allumé la carte.
On a un navigateur, et tous les applications linux disponibles.
# 1.3 Connexion au système
 # 1.3.1 Liaison série
 On a utilisé le cable 1 usb mini : uart to usb .Pour se connecter , on utilise le port série , PORT 0:   minicom -D /dev/ttyUSB0 -b 115200
— login : root
— password : aucun (vraiment rien, ne tapez que sur entrée)
Nous avons redémarré le SoC pour observer la séquence de démarrage avec la commande reboot
on observe que lors du reboot on stop tous les processus, le système demande si l’on veut annuler le reboot , puis il démarre le kernel
L’image flashé précédemment occupe 1.3 Go et l’espace disponible est de 3Go aprés avoir tapé les deux commandes 
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/55e2b35a-dab8-47e6-862b-2113968a52c8)
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/d2421c21-be83-4ed1-9236-90fd29842111)
# 1.3.3 Configuration réseau
lorsqu’on branche la carte avec le switch , l’adresse que l’on se voit attribuée est la suivantes: 192.168.88.56
Après le redémarrage, nous pouvons vérifier l'adresse IP locale de la carte en utilisant la commande "ifconfig".Pour vérifier le bon fonctionnement nous faisons un ping
, et nous utilisons le protocole sécurisé SSH.Le ping fonctionne correctement.
On vérifie aussi que dans le fichier /etc/ssh/sshd_config, la ligne suivante est présente : PermitEmptyPasswords yes
![ifconfig](https://github.com/Anass6666/TP_LinuxE/assets/145018011/2ff032ca-2cf2-4c1c-addc-afdfe437781a)
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/61679a98-62c1-4798-a222-f01faacf78a8)


# 1.4 Découverte de la cible
  # 1.4.1 Exploration des dossiers /sys/class et /proc
Sous la racines nous avons les dossier suivant: /usr , /proc , /root , /sys etc..En tapant la commande cpuinfo on voit que l’on a un processeur dual core  ARMv7 
iomem : Ce fichier nous donne des informations sur l’allocation de la mémoire des entrées sorties du systeme, il nous donne les plages de mémoire utilisées pour chaque périphérique.
Par exemple , dans le répertoire "sys/class/leds/..", nous pouvons trouver les LED disponibles en tant que périphériques.le répertoire /sys/class contient les peripheriques,GPIO, DMA, I2C ect..La difference entre le fichier /proc/device-tree/sopc@0 et le fichier iomem est que le premier nous affiche les timer en plus.
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/4a428c67-8c9a-474a-b8c2-5692e1e28912)

# 1.4.3 Hello world !

![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/ff2ccf91-045e-41b8-9884-4260e3a8481f)


![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/772843cc-3b8e-4795-849c-b74a3c437f63)

# 1.4.5 Chenillard (Et oui, encore !)
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/7aa86f6d-e3b1-4f4f-98c6-b27b84d5379c)
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/4067cd7f-1370-421c-9eb8-64547424a7e8)
