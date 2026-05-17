# NomCool — entraînement au calcul mental

Petite application Qt en C++ pour s'entraîner aux tables de multiplication.
On choisit une difficulté, on répond à des questions à choix multiples, on gagne
de l'XP et de l'or, et on dépense l'or dans une boutique de skins pour la
mascotte.

## Compilation

Le projet utilise CMake et Qt 6 (modules `Core`, `Widgets`, `Multimedia`).
Le chemin par défaut vers Qt est `$HOME/Qt/6.10.2/macos` (voir
`CMakeLists.txt`), à adapter si besoin via `-DCMAKE_PREFIX_PATH=...`.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Exécution

Une fois compilé :

```sh
./build/bin/Debug/NomCool        # application
ctest --test-dir build           # tests unitaires
```

L'application stocke sa progression (XP, or, skins possédés, paramètres) via
`QSettings`, donc la progression est conservée entre deux lancements.

## Fonctionnalités

**Cœur** — questions de multiplication à choix multiples générées
aléatoirement, avec un bouton « Je ne sais pas ». La bonne réponse est
indiquée en cas d'erreur.

**Difficulté** — trois niveaux (Facile, Normal, Difficile). Le mode
Difficile est verrouillé tant qu'on n'a pas atteint le niveau 2, et propose
des distracteurs proches du bon résultat (résultat ± 1) pour brouiller les
pistes.

**Chronomètre par question** — activable ou non depuis l'écran de
configuration. Si le temps imparti est dépassé, la question compte comme
ratée.

**Nombre de questions** — infini, ou borné par une valeur choisie. En mode
borné, la partie se termine quand on a posé le nombre demandé.

**Mascotte** — petite mascotte personnalisable, affichée à côté de la
question, qui réagit aux réponses via une bulle de dialogue. Elle peut être
masquée depuis les paramètres ; dans ce cas, le retour visuel passe par un
bandeau coloré.

**Système de progression (gamification)** — chaque bonne réponse rapporte
de l'XP et de l'or, modulés par la difficulté et par un bonus de série.
L'XP fait monter de niveau (atteindre le niveau 2 débloque la difficulté
Difficile), l'or permet d'acheter de nouveaux skins dans la boutique.

**Boutique et création de skins** — cinq skins prédéfinis à acheter, plus
un éditeur pour créer ses propres skins (nom + couleur de teinte) qui sont
ensuite directement disponibles dans le sélecteur.

**Musique de fond** — un morceau d'ambiance qui peut être activé ou coupé
depuis les paramètres ; la mascotte tourne sur elle-même quand la musique
joue.

## Organisation du code

Le code est séparé en deux dossiers pour isoler la logique métier de
l'interface graphique. C'est cette séparation qui permet, en principe, de
remplacer le front Qt sans toucher au reste.

Les ressources (icônes, image de mascotte, musique) sont regroupées dans
`src/resources/` et empaquetées dans `resource.qrc`.

## Choix techniques


**Découpage par page (`HomePage`, `GameSetupPage`, `GamePage`)** —
`MainWindow` ne fait qu'orchestrer un `QStackedWidget` qui passe d'une page
à l'autre. Chaque page assemble ses propres widgets : ça évite d'avoir un
`MainWindow` monolithique qui ferait tout.

**Widgets atomiques** — `ExperienceBar`, `QuestionTimer`, `Mascot`,
`SpeechBubble`, `ToggleSwitch`, `ScoreDisplay` sont des petits `QWidget`
indépendants qui ne savent rien du reste du jeu. Ils prennent une donnée en
entrée et l'affichent. Ça permet de les réutiliser (la barre d'XP apparaît
sur l'accueil *et* en jeu, la mascotte aussi) et de les tester / modifier
isolément.

**Persistance via `QSettings`** — pas de fichier maison à parser : `XP`,
`or`, skins possédés, skin sélectionné, skins custom et préférences
(mascotte/musique) sont tous stockés dans `QSettings` sous l'organisation
`NomCool/NomCool`. Code de chargement/sauvegarde regroupé dans les classes
métier concernées (`Experience::save/load`, `SkinManager::save/load`).

**Signals/slots Qt plutôt que callbacks maison** — la communication entre
pages, dialogues et widgets passe par les signaux Qt (`playClicked`,
`startGame`, `skinPurchased`, `musicToggled`, etc.). Les pages exposent
leurs signaux et `MainWindow` les relie, ce qui garde les pages
indépendantes les unes des autres.

**Réponses** sous forme de codes (`"Correct"`, `"Incorrect"`,
`"I don't know"`, `"Time's up"`)** — le générateur de questions associe à
chaque bouton une réponse-clé que `GamePage` compare ; ça évite de coupler
la logique de scoring au texte affiché et permet par exemple d'avoir une
réponse « Je ne sais pas » qui produit un message dédié.

**Skins teintés à la volée** — un skin est défini par une couleur (`QColor`,
alpha = 0 pour le défaut). L'image de mascotte de base est colorisée à
l'affichage via `QGraphicsColorizeEffect` (ou un mélange pixel à pixel dans
l'aperçu de la boutique), ce qui évite d'avoir à fournir une image par
skin.

## Utilisation de l'IA

Utilisée ponctuellement pour me débloquer quand je restais trop longtemps
sur un point précis, et pour la mascotte qui tourne avec la musique
(petit gag visuel sur lequel je ne voulais pas passer de temps).
