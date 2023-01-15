run: main.c settings.c controleGrille.c ia0.c ia1.c ia2.c
	clang -o run main.c settings.c controleGrille.c ia0.c ia1.c ia2.c -lm -I.