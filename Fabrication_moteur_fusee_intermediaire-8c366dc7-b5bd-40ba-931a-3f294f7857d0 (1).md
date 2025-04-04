# Fabriquer et lancer une fusée à eau plus complexe!

Vous aimez les défis ? Vous souhaitez assembler une fusée plus complexe ? Passons à un assemblage adapté à votre niveau !

Nous allons prendre le temps de préparer, calculer et fabriquer une fusée à eau utilisant des matériaux plus complexes, incluant des composants électroniques et un programme. Cette fusée comprendra un cœur électronique permettant de lire, enregistrer et présenter des données télémétriques. Le tout avec des performances mécaniques plus poussées, incluant une récupération sécuritaire grâce à un déploiement de parachutes.

Dans ce document, nous allons nous concentrer sur la dimension de la section **moteur** (réservoir) de la fusée, en utilisant les sciences et les mathématiques pour obtenir des résultats optimaux.

Commençons donc par établir les paramètres essentiels pour la confection du réservoir de notre fusée.

## Choix des paramètres du réservoir

Il est essentiel de définir les performances attendues, la quantité d'énergie et la poussée potentielle du réservoir.

### Section moteur, réservoir et tuyère

- Paramètres du réservoir
- Volume du réservoir
- Proportions d'eau et d'air pressurisé
- Énergie et puissance déployée
- Calculs selon les paramètres du réservoir

Les matériaux et calculs suivants utiliseront des paramètres à titre d'exemples. Il vous incombera de déterminer les performances, dimensions et autres paramètres.

### Exemple de matériel utilisé

Nous utiliserons des matériaux de construction standards, faciles à manipuler et solides. Par exemple, des tuyaux de PVC pour la plomberie.

#### Liste des matériaux :

- Tuyau de PVC de 4" (intérieur) Schedule 40
- Capuchon mâle de 4" avec bouchon et joint torique étanche
- Joint femelle de 4"
- Réduit court mâle de 4" à 3"
- Réduit court mâle de 3" à 2"
- Réduit court mâle de 2" à 1"1/2
- Tuyau de 1"1/4 (intérieur)
- Réduit de 2" à 1"1/2 formant une tuyère "Bell" simple
- Colle PVC pour l'assemblage

### ⚠️ **Note importante** :
L’utilisation de tuyaux de PVC de plomberie nous permet d’atteindre des capacités de pression élevées tout en garantissant un montage facile et solide. Cependant, il est crucial que l'assemblage soit effectué dans un environnement contrôlé. Un tuyau PVC de Schedule 40 reste léger et solide. Néanmoins, il est **fortement recommendé de ne jamais dépasser 100 psi (6.89 bar)**. Pour l'assemblage, nous vous recommandons de faire appel à un adulte expérimenté.

---

# Calculs mathématiques de l'énergie disponible

Nous utiliserons un diamètre de **4" (0.0508 m)** pour les équations à titre d'exemple.

## Variables à déterminer

- **h** : Hauteur du réservoir, variable à déterminer. *(Vous pouvez modifier cette variable)*
- **W** : Énergie disponible, variable ultime à calculer.

## Variables connues

- **R = 0.0508 mètres** : Rayon du tuyau de 4" converti au système métrique international.
- **𝛾 = 1.4** : Constante qui vient de la formule du travail d'une expansion adiabatique d'un gaz.
- **\( P_i = 689.5 \) kPa** : Pression cible utilisée de 100 psi convertie en kilopascals. *(Vous pouvez modifier cette variable)*
- **\( P_f = 101.3 \) kPa** : Pression atmosphérique constante de l'air au niveau de la mer en kilopascals.

## Volumes simplifiés

- \( V_{\text{tot}} = \pi R^2 h \) → Noté **V1** : Volume total du réservoir.
- \( V_{\text{air},i} = \frac{2}{3} V_{\text{tot}} \) → Noté **V2** : Volume initial de l'air dans le réservoir.
- \( V_{\text{air},f} = V_{\text{tot}} \) → Noté **V3** : Volume final de l'air dans le réservoir.

## Calcul de l'énergie disponible

L'énergie disponible est donnée par la formule du travail d'une expansion adiabatique :

\[
W = \frac{P_i V_2 - P_f V_3}{\gamma - 1}
\]

En remplaçant les volumes :

\[
W = \frac{P_i \cdot \frac{2}{3} \pi R^2 h - P_f \cdot \pi R^2 h}{\gamma - 1}
\]

En mettant \( \pi R^2 h \) en facteur :

\[
W = \frac{\pi R^2 h}{\gamma - 1} \left( \frac{2}{3} P_i - P_f \right)
\]

### Résultat:

L'énergie disponible **W** est une fonction **linéaire** de la hauteur **h**, ce qui signifie que plus le réservoir est haut, plus l'énergie stockée est grande.

### Voici donc un exemple du calcul d'énergie disponible en Joules avec une hauteur connue.

Nouvelle valeur de la hauteur du réservoir :

**h** = 0.6096 m (2')

Nouvelle équation et résultat :

\[
W = \frac{\pi R^2 h}{\gamma - 1} \left( \frac{2}{3} P_i - P_f \right)
\]

En remplaçant les valeurs :

\[
W = \frac{\pi (0.0508)^2 (0.6096)}{1.4 - 1} \left( \frac{2}{3} \times 689500 - 101300 \right)
\]

\[
W \approx 4428 \text{ Joules}
\]

# Calculs mathématiques d'une poussée potentielle

C'est bien beau de connaître l'énergie disponible dans un réservoir, mais encore faut-il être capable d'en tirer une poussée capable de déplacer un objet.

Encore une fois, nous allons avoir besoin des variables connues et des variables à déterminer pour nous donner un résultat.

## Variables connues

- **W** : Énergie disponible (déjà calculée),
- **ρ** : Densité de l'eau (1000 kg/m³),
- **P** : Pression derrière l'eau (100 psi).

## Variables à déterminer

- **r** : Rayon de la sortie (tuyère, exemple à 1"1/4 soit 0.0254m)
- **A** : Aire de la sortie.

### 1. Hauteur du réservoir

Le réservoir fait 2 pieds de haut et est rempli à 1/3 d'eau. Pour déterminer la hauteur de l'eau :

\[
h_{\text{eau}} = \frac{2}{3} \, \text{pieds} = \frac{2}{3} \times 0.3048 \, \text{m} = 0.2032 \, \text{m}
\]

Donc, la hauteur de l'eau dans le réservoir est de \( h_{\text{eau}} = 0.2032 \, \text{m} \).

### 2. Pression derrière l'eau

La pression derrière l'eau est de \( 100 \, \text{psi} \). Convertissons cette pression en pascals :

\[
1 \, \text{psi} = 6894.76 \, \text{Pa}
\]

Donc, la pression derrière l'eau en pascals est :

\[
P = 100 \, \text{psi} \times 6894.76 \, \text{Pa/psi} = 689476 \, \text{Pa}
\]

Cette pression va influencer la vitesse d’éjection de l’eau, donc elle doit être prise en compte dans les équations.


### 3. Calcul de la vitesse d’éjection avec pression

Pour déterminer la vitesse d’éjection en tenant compte de la pression, nous utilisons la relation entre l'énergie potentielle et cinétique. La pression est liée à l'énergie par l'équation :

\[
\frac{P}{\rho} = \frac{v^2}{2}
\]

Où :
- \( P \) est la pression (en pascals),
- \( \rho \) est la densité de l'eau (\( 1000 \, \text{kg/m}^3 \)),
- \( v \) est la vitesse d'éjection de l'eau.

Nous réarrangeons cette formule pour exprimer \( v \) :

\[
v = \sqrt{\frac{2P}{\rho}}
\]

Substituons les valeurs :

\[
v = \sqrt{\frac{2 \times 689476}{1000}}
\]

\[
v = \sqrt{1378.952}
\]

\[
v \approx 37.15 \, \text{m/s}
\]

### 4. Calcul du débit massique \(\dot{m}\)

Le débit massique est donné par la formule :

\[
\dot{m} = \rho A v
\]

Où :
- \( A = \pi r^2 = 3.1416 \times (0.015875)^2 = 0.000793 \, \text{m}^2 \) (aire de la sortie),
- \( v \approx 37.15 \, \text{m/s} \) (vitesse d’éjection calculée ci-dessus),
- \( \rho = 1000 \, \text{kg/m}^3 \).

Calculons donc le débit massique :

\[
\dot{m} = 1000 \times 7.93 \times 10^{-4} \times 37.15
\]

\[
\dot{m} \approx 29.5 \, \text{kg/s}
\]

### 5. Force de poussée (F)

La force de poussée est donnée par :

\[
F = \dot{m} v
\]

En utilisant les valeurs de \( \dot{m} \approx 29.5 \, \text{kg/s} \) et \( v \approx 37.15 \, \text{m/s} \), on obtient :

\[
F = 29.5 \times 37.15
\]

\[
F \approx 1091.31 \, \text{N}
\]

### En effectuant les calculs :

1. **Hauteur de l'eau dans le réservoir** : \( 0.2032 \, \text{m} \)
2. **Pression derrière l'eau** : \( 689476 \, \text{Pa} \) (100 psi)
3. **Vitesse d’éjection** : \( 37.15 \, \text{m/s} \)
4. **Débit massique** : \( 29.5 \, \text{kg/s} \)
5. **Force de poussée** : \( 1091.31 \, \text{N} \)

### Résultat

Nous venons donc de déterminer qu'avec un réservoir de 4" de diamètre et 2' de haut contenant environ 4428 Joules d'énergie, et en utilisant une sortie de 1"1/4 de diamètre, nous pouvons convertir l'énergie en une poussée d’environ **1091.31 Newtons**.

Convertissons cette valeur de poussée en kg (kg-f) :

1 kg-f = 9.81 N

\[
\frac{1091.31}{9.81} \approx 111.34 \, \text{kg-f}
\]

Nous voici donc avec une **force de poussée de 111.84 kg**

#### Explication des calculs 

1. **Aire de la sortie (A)** : Nous avons utilisé le rayon de la sortie pour déterminer l'aire de la tuyère. Cela est important car l'aire détermine la quantité d'eau qui peut sortir du réservoir par unité de temps, influençant ainsi le débit massique et la force de poussée.

2. **Masse d'eau éjectée (m)** : Nous avons estimé que 1.5 kg d'eau est éjecté par seconde, ce qui dépend de la densité de l'eau, de l'aire de la sortie et de la vitesse d'éjection.

3. **Vitesse d’éjection (v)** : Utilisant la formule de Torricelli, nous avons trouvé que la vitesse d'éjection dépend de la hauteur de la colonne d'eau, qui diminue au fur et à mesure de l'éjection. La vitesse est initialement élevée mais décroît rapidement au fur et à mesure que l'eau est éjectée.

4. **Débit massique ( \(\dot{m}\) )** : Le débit massique est la quantité de masse d'eau éjectée par seconde. Ce calcul prend en compte l'aire de la sortie et la vitesse d'éjection de l'eau. Cela nous permet de déterminer combien d'eau est expulsée par seconde et à quelle vitesse.

5. **Force de poussée (F)** : En utilisant le débit massique et la vitesse d'éjection, nous calculons la force de poussée générée par l'éjection de l'eau. Cette poussée est ce qui propulse la fusée dans l'air.


## Énergie disponible et poussée potentielle?

Nos calculs nous ont permis de déterminer une quantité d'énergie et une poussée "**potentielle**". Ces chiffres sont intéressants, mais ils ne représentent que la situation idéale au tout début de l'éjection de l'eau. En réalité, ces données ne sont exactes qu'au **début de l'éjection**. En effet, à mesure que le réservoir se vide de son eau, la pression interne de l'air diminue, ce qui réduit l'énergie disponible et la poussée au fil du temps. Ainsi, la poussée initiale sera très importante, mais elle diminuera rapidement et progressivement à mesure que l'eau est éjectée.

Dans une fusée à eau de ce type, l'éjection de l'eau peut varier énormément en fonction des dimensions utilisées. L'éjection peut durer moins d'une seconde, ou plusieurs secondes, selon les paramètres de la fusée.

## Conclusion

Les mathématiques et la recherche vous intéressent ? Nous vous invitons à pousser vos recherches plus loin, notamment dans les domaines suivants :

- **Déterminer le temps d'éjection de l'eau**, et donc le temps de propulsion potentiel.
- **Choisir le bon diamètre pour l'éjection de l'eau** : plus grand pour une poussée plus puissante mais plus courte, et plus petit pour une poussée moins importante mais plus longue.
- **Estimer une altitude potentielle** : tenez compte du poids de la fusée à vide, du poids total avec son "carburant" (l'eau), ainsi que de la puissance et du temps de l'accélération, sans oublier la diminution progressive de ces valeurs au fil du temps.
- **Calculer la différence de vitesse d'éjection de l'eau** et améliorer les performances en ajoutant une tuyère de type "Bell".

Notez que les équations et estimations vues plus haut sont basées sur des exemples. À vous de déterminer les dimensions et capacités souhaitées en modifiant les paramètres. Les matériaux et dimensions utilisés dans les exemples sont un bon point de départ.

Pour l'assemblage de la tête de la fusée, voir le document **Assemblage_tete_fusee_code_parachutes**.md

