
Ca marche bien en utilisant l'encodage Windows 1252 (Latin-1) au sens où:

-j'arrive à lire et écrire un fichier texte via FatFS
- je le vois par USB et peux le relire sur PC W7 et Mac OS X
- mais Linux me dit qu'il ne peut pas l'ouvrir --même si je lui dis oui quand il me propose (entre autres) 1252 au lieu de Unicode...

Si j'essaie d'encoder en Unicode-8 via FatFS (ce qui nécessite d'utiliser le mode LFN pour Long File Name, entre autres) j'ai des erreurs à la compil

Je n'ai pas essayé LFN sans le mode Unicode (i.e. juste pour permettre les longs noms de fichiers)


