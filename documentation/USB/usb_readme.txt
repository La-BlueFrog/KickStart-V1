Récapitulatif pour l'utilisation de la librairie : STM32_USB-FS-Device_Driver

Couche base :
	- usb_reg(.h,.c) : couche d'abstration matérielle
	- usb_int(.h,.c) : definition du type de routine de transfert.
	- usb_mem(.h,.c) : copie les données de l'utilisateur vers le paquet de zone mémoire (PMA) et vise et versa
Couche medium :
	- usb_init(.h,.c) : initialise les routines et les variables globales
	- usb_core(.h,.c) : "kernel", machine état du protocol USB, sous-routine, etc ...
	- usb_sil(.h,.c) : module additionnel de la couche d'abstration, opération de lecture et d'écriture
	- usb_type.h / usb_def.h : définissent les types (structures) des variables USB.
	- platform_config.h : definit la configuration de la carte (peut être configurée par l'utilisateur)

Interface d'application__
Couche haute:
	- usb_conf.h : personnalise la demo USB et configure le matériel suivant :
		- definit le nombre d'endpoints (EP_NUM)
		- active l'utilisation d'endpoints et de routines (EP1_IN_Callback, INTR_SOFINTR_Callback
		Vous pouvez utiliser le fichier pour :
			- configurer la BTABLE et tout les endpoint dans le PMA (BTABLE_ADDRESS, ENDP0_RXADDR, 
			END0_TXADDR ...)
			- definir les interruptions ... IMR_MSK
	- usb_desc(.h,.c) : contient tout les descriptifs pour créer une application.
	- usb_prop(.h,.c) : utilisé pour implémenter les propriètés du matériel, sa table et ses requètes standards
		- void Init(void) : initialisation USB
		- void Reset(void) : procédure de reset du périphérique USB
		- void Process_Status_IN(void) : appelée lorsqu'un état entrant est terminé
		- void Process_Status_OUT(void): appelée lorsqu'un état sortant est terminé
		- ...
	- usb_endp.c : manipuler les tranferts de routines correctes pour les endpoints autre que 0 (EP0)
	- usb_istr.c : manipule toutes les interruptions USB.
	- usb_pwr(.h,.c) : controle l'alimentation du matériel USB.

MASS STORAGE DEMO (Chapitre 6) - Bulk transfert

