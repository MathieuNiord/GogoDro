Projet de Théorie des langages et Compilation
Auteurs : Fréjoux Gaëtan, Niord Mathieu

Université de Poitiers, Année 2021-2022

Sujet : Conception d'un langage permettant de contrôler un robot capable de dessiner à l'intérieur d'une zone prédéfinie.
Contraintes : Actions prédéfinies, syntaxe et complexité des mécanismes doivent être accessibles à un niveau type "collège".
Technologies : Flex, Yacc et C++.

INFORMATIONS :

    Un makefile est fourni dans le répertoire, lancez la commande make help pour
    voir l'ensemble des commandes proposées.

    Trois fichiers de test sont fournis dans le répertoire "tests_files/".

SYNTAXE :

    ATTENTION : La syntaxe présentée ci-dessous, est à respecter scrupuleusement !

    Le robot caligraphe, la tortue ou simplement le crayon, se déplace sur un axe (x, y) dans quatre directions.
    Soit un axe p(x, y) tq à l'initialisation p.x = 0 et p.y = 0 :
    
    - Directions :
    
        HAUT        : p(0, -1)
        BAS         : p(0, 1)
        GAUCHE      : p(-1, 0)
        DROITE      : p(1, 0)
        
    La syntaxe actuelle ne permet pas de réaliser directement un tracé diagonal. Par conséquent, il faudra
    faire avancer le crayon case par case en escaliers. Soit, en d'autres termes :
    
        fct diag()
            for i = 0 to nb
                write;
                stop;
                move(left);
                move(up;)
            end for;
        ;;
        
    Dans le cadre de ce projet, il existe des couleurs prédéfinies, permutables, qui correspondent à
    l' "encre" du crayon au moment de l'écriture.
    
    
    - Couleurs :
    
        NOIR    : Pas une vraie couleur. Le programme est initialisé à cette valeur.
        BLEU
        JAUNE
        ROSE
        ROUGE
        VERT
        VIOLET


    - Instructions :

        Lever                                   : Lève le crayon, déplacements sans écriture.
        Ecrire                                  : Baisse le crayon, déplacements avec écriture.
        Couleur(<color>)                        : Permute la couleur actuelle avec color.
        Centrer                                 : Repositionne le robot, sans écriture, au centre de l'image.
        <variable> <- <expression>              : Affectation, c'est une instruction qui appartient à l'arithmétique du langage.
        nombre <nom_variable>                   : Déclaration de la variable nom_variable.
        nombre <nom_variable> <- <expression>   : Déclaration de la variable nom_variable puis affectation de la valeur expression (float).
        Deplacer(<direction>, <n>)              : Déplace le robot dans la direction donnée de n pixels.
        Ligne(<direction>, <taille>)            : Dessine une ligne de longueur <taille> dans la direction fournie.
                                                  La position finale vaut p_start + taille, en fonction de la direction.
        Rectangle(<l>, <h>)                     : Dessine un rectangle (plein), centré sur le crayon, d'aire l * h.
                                                  Le crayon garde sa position.
        Cercle(<diametre>)                      : Dessine un cercle (plein) de diametre fourni, centré sur la position actuelle.
                                                  Le crayon garde sa position.
        pour(i, 1, 10)                          : Boucle itérative allant de 1 à 10 inclus (10 itérations).
        fin pour                                : Spécificateur de fin de boucle.
        
        A NOTER : Toutes les instructions doivent se terminer par un point-virgule.
        
        
    - Arithmétique :
    
        <expression> + <expression>         : somme
        <expression> - <expression>         : soustraction
        <expression> * <expression>         : multiplication
        <expression> / <expression>         : division
    
    
    - BONUS :
    
        - Macros :
    
        #NOM <nom_image>                    : permet à l'utilisateur de redéfinir le nom du fichier à sauvegarder.
        #CHEMIN /mon/chemin/de/sauvegarde/  : permet à l'utilisateur de modifier le chemin de sauvegarde du fichier.
        #SAUVER (<nom_image>?)              : force la sauvegarde du fichier dans son état, possiblement sous le nom fourni.
        #NOUVEAU (<nom_image>?)             : efface l'image précédente (pas de sauvegarde) et en créé une nouvelle, avec un nom optionnellement.
    
        ...et la possibilité d'écrire des commentaires sur une ligne en débutant par "//".
    
        ATTENTION : La macro #CHEMIN ne permet de créer qu'un seul et unique répertoire. Par conséquent, (au moins) tout ce qui précéde
        le dernier nom devra exister au préalable. Le chemin à fournir doit être exprimer comme tel (entre guillemets) :
        /mon/chemin/ ou /../mon/chemin/, avec le répertoire "mon/" préalablement créé.
    
    
AMELIORATIONS :
    
    - Possibilité d'écrire des commentaires ;
    - Macros utiles à la configuration de l'image ;
    - Ajout de couleurs : puisque les couleurs sont à indiquer uniquement à partir de leur identifiant, nous avons ajouté la possibilité d'en créer ;
    - Instructions Centrer et Cercle ;
    - Les variables et expressions sont traitées telles que des double dans le but d'améliorer la précision du curseur ;
    - Possibilité d'affecter une valeur directement lors de la déclaration (raccourci certes facile à implémenter mais reste utile).
