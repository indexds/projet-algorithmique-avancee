# Projet Algorithmique Avancee (N3S6)

Petit utilitaire avec moteur d'inférence permettant de trouver les animaux verifiant certaines caractéristiques.

# Compilation

Le programme nécessite gtk pour compiler, disponible [ici](https://www.gtk.org/docs/installations/windows/)

Dans un shell quelconque, lancer:

```bash
make
```
Une fois compilé, le programme génère un main.exe. Toujours dans le même shell, lancer

```bash
./main
```

# Utilisation

Pour utiliser le programme il faudra d'abord rentrer les règles dans le fichier ```rules.kbs```.<br>
Des règles de base sont prédéfinies et peuvent être étendues autant que désiré.<br>
La syntaxe est la suivante: ```Condition1 Condition2 ConditionN -> Implication```. <br>

-Un espace entre chaque mot et une fleche pour indiquer l'implication. <br>
-Une règle par ligne.<br>
-Les bouts de chaine doivent etre définis en ajoutant une règle ```FindeChaine -> END```<br>

### Exemple

```Osteichtyen 4_Membres -> Tetrapode```<br>
```Tetrapode Gesier Plumes -> Oiseau```<br>
```Oiseau -> END```<br>

## Find Animal

Pour trouver un animal en particulier, on rentre simplement les caractéristiques désirées. Le programme retournera soit l'animal s'il en trouve un soit "Not Found."

## Prove Animal

Pour "prouver" un animal, on rentre les caractéristiques suivies d'une flèche puis de l'implication souhaitée.<br>
Le programme renverra Vrai ou Faux en fonction de si les caractéristiques correspondent bel et bien à cet animal.<br>

### Exemple

![exemple gif](https://cdn.discordapp.com/attachments/1216732436604387402/1218300027630518412/Animation.gif?ex=66072951&is=65f4b451&hm=bc4fe59893ed57014e1a26e5832e6c590da1777bac0e4ad5babda547d9997336&)
