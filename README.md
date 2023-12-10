# Gomoku
Gomoku en C, avec une ia utilissant l'algorithme MinMax

Le gomoku se joue sur un plateau quadrillé de 19 lignes horizontales et 19 lignes verticales formant, comme un jeu de go, 361 intersections. Le nombre de pions est toutefois nettement inférieur, puisque les joueurs n'en reçoivent que 60, qu'ils posent un à un et à tour de rôle sur les intersections.

Le joueur qui a choisi ou obtenu par un tirage au sort les pions noirs (et que l'on appelle Noir par convention) joue toujours le premier en plaçant son premier pion sur l'intersection centrale du damier. Blanc doit alors poser son pion. Noir fait la même chose, et ainsi de suite, le but du jeu étant de prendre l'adversaire de vitesse et de réussir le premier à aligner 5 pions de sa couleur, dans les trois directions possibles : vertical, horizontal ou diagonal.

Si les deux joueurs placent tous leurs pions sans qu'aucun ne parvienne à réaliser un alignement, le jeu est déclaré nul, et ils recommencent. Une partie se dispute généralement en deux manches, afin que celui qui a commencé avec les noirs ait les blancs la seconde fois.
