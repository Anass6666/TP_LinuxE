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



# 1.4 Découverte de la cible
  # 1.4.1 Exploration des dossiers /sys/class et /proc
Sous la racines nous avons les dossier suivant: /usr , /proc , /root , /sys etc..En tapant la commande cpuinfo on voit que l’on a un processeur dual core  ARMv7 
iomem : Ce fichier nous donne des informations sur l’allocation de la mémoire des entrées sorties du systeme, il nous donne les plages de mémoire utilisées pour chaque périphérique.
Par exemple , dans le répertoire "sys/class/leds/..", nous pouvons trouver les LED disponibles en tant que périphériques.le répertoire /sys/class contient les peripheriques,GPIO, DMA, I2C ect..La difference entre le fichier /proc/device-tree/sopc@0 et le fichier iomem est que le premier nous affiche les timer en plus.
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/4a428c67-8c9a-474a-b8c2-5692e1e28912)

# 1.4.3 Hello world !
Une fois la configuration et l'exploration des ressources de la carte terminées,On va créé un premier fichier "Hello World" et le compiler à l'aide de la machine virtuelle.
On procéde à la compilation du fichier source en utilisant la commande adéquate, généralement "arm-linux-gnueabihf-gcc -o hello.c hello". Pour transférer le fichier exécutable vers la carte VEEK, on utilise le protocole SSH avec la commande SCP (Secure Copy).

![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/ff2ccf91-045e-41b8-9884-4260e3a8481f)
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/772843cc-3b8e-4795-849c-b74a3c437f63)
![compilation](https://github.com/Anass6666/TP_LinuxE/assets/145018011/c649a7d4-c232-4fae-9ea9-1e60e631cbc3)
# 1.4.4 Accès au matériel
á l'aide de la commande echo "1" > /sys/class/leds/fpga_led1/brightness , on teste d’allumer et d’éteindre la LED.
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/4067cd7f-1370-421c-9eb8-64547424a7e8)
# 1.4.5 Chenillard (Et oui, encore !)
On a écrit le code qui réalise un chenillard et ça marche très bien , On crée  un fichier "main" dans lequel nous ouvrons le fichier brightness, modifie sa valeur, puis on referme le fichier. Cette séquence est répétée pour chaque LED du chenillard
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/7aa86f6d-e3b1-4f4f-98c6-b27b84d5379c)
# 2 Modules kernel (TP2)
# 2.0 Reprise du TP1
J'ai réussi à me connecter et communiquer avec la carte VEEK cependant.Cependant l'adresse IP a changé 
![rootip](https://github.com/Anass6666/TP_LinuxE/assets/145018011/2e43d737-3d3b-4610-8bf7-5b13e9c6c44d)
# 2.1 Accès aux registres
Pour accéder aux registres, une étape importante consiste appelée re-mappage de la mémoire, elle fait correspondre une adresse physique à une adresse virtuelle dans l'espace d'adressage du processus en cours d'exécution, dans un code nous allons interroger l’OS en lui donnant une adresse physique pour qu’il nous renvoie par la suite une adresse virtuelle utilisable qui nous permettra d’allumer une LED à l’adresse 0xFF203000. 

int main(void) {
	uint32_t * p;
	int i=0;
	int fd = open("/dev/mem", O_RDWR);
	p = (uint32_t*)mmap(NULL, 4, PROT_WRITE|PROT_READ, MAP_SHARED,fd, 0xFF203000);
	while (1)
	{
		for (i=1;i<10;i++)
		{
			*p = (1<<i);
			usleep(500000);
			*p = (0<<i);
		}
	}	
	return 0;
}
# 2.2 Compilation de module noyau sur la VM
Pour compiler des modules noyau dans la VM, On a besoin des paquets suivant :
sudo apt install linux-headers-amd64
sudo apt install bc
À partir du Makefile et du fichier source hello.c disponibles sur moodle,j'ai compilé notre premier module
Pour charger : sudo insmod <nom_du_module.ko>
Pour décharger : sudo rmmod<nom_du_module.ko>
Pour avoir des informations sur le module: sudo modinfo<nom_du_module.ko>
sudo lsmod : pour afficher le status des modules dans le noyau linux. cela nous affiche
une list des modules chargés.
sudo dmesg: ça affiche les messages dans le journal du noyau
![compilation_module_noyeau](https://github.com/Anass6666/TP_LinuxE/assets/145018011/329ae68f-7d89-4d81-b7a2-ea770d52837a)

On teste le programme suivant : — utilisation de paramètres au chargement du module,avec la meme  démarche pour la compilation. 
![modulehello](https://github.com/Anass6666/TP_LinuxE/assets/145018011/adc039cc-8a20-4c87-b2af-6d89244d722d)
![Capture du 2024-05-30 15-30-48](https://github.com/Anass6666/TP_LinuxE/assets/145018011/25c89164-e73f-4440-a9c8-909855234142)
Pour charger le module avec le paramètre on tape: “sudo insmod le_module.ko param=0”.
Création d’une entrée dans /proc:
Avec les memes démarches pour la compilation , on ajoute une entrée proc:(Le code source est dans le fichier src/proc
TIMER:
![Timer](https://github.com/Anass6666/TP_LinuxE/assets/145018011/e9e2e529-1934-4f13-91a1-a1f69d1a3639)
# 2.3 CrossCompilation de modules noyau
# 2.3.0 Récupération du Noyau Terasic
  # 2.3.1 Préparation de la compilation
sudo apt install bc
sudo apt install crossbuild-essential-armhf
sudo apt install binutils-multiarch
Le chemin vers ces compilateurs : whereis arm-linux-gnueabihf-gcc
# 2.3.2 Récupéreation de la configuration actuelle du noyau
— Quel est le rôle des lignes commençant par export ? Création de variable d’environnement qui peuvent etre utilisé pendant l’exécution du shell
— Pourquoi le chemin fini par un tiret "-" ? Car la ligne dans le make est suivie d’un gcc donc on a pas besoin de le specifier.
![2 3 2make_scripts_](https://github.com/Anass6666/TP_LinuxE/assets/145018011/8633741b-3a5e-4e3c-b244-7e2b316425dc)
# 2.3.3 Hello World
![commande cross_compile_makeprapare](https://github.com/Anass6666/TP_LinuxE/assets/145018011/529427d6-17ce-40fa-822f-66556a1c55d5)
On crée un fichier CROSS dans Src pour pouvoir tester par la suite nos modules . 
la compilation s’effectue sans encombre , lorsque l’on charge le module et grâce a la commande dmesg on peut voir afficher le parametre .

![make](https://github.com/Anass6666/TP_LinuxE/assets/145018011/d5e51bd0-ed33-46df-963b-89f12b29f5fd)
![image](https://github.com/Anass6666/TP_LinuxE/assets/145018011/884f0b35-48ed-49bb-8f36-8e9359aa21f4)

TIMER : 
Chargement et déchargement du module : 

![2 3 4ChargementModuleTimer](https://github.com/Anass6666/TP_LinuxE/assets/145018011/09156dbc-e975-4ab1-a50d-94975b5b7425)
![2 3 4 DechargementTimer](https://github.com/Anass6666/TP_LinuxE/assets/145018011/b6b14706-14c5-44ae-9f08-3f2b73ddbd48)

On voit bien le bon fonctionnement de la crossCompilation (Parametre et TIMER ) 







