#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <string.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"



int main (int argc, char ** argv) {
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	int activC = 1;

	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);


	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}


	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	cairo_surface_t *cs;
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY );
	while(1) {

		XNextEvent(dpy, &e);
		 switch (e.type){
			 case Expose:
			 {
				 if(e.xexpose.count<1){
					  paint(cs,g);
						break;
					}

			 }
			case ButtonPress:
								{ 	if(e.xbutton.button == 1){
																efface_paint(cs);
																evolue(&g,&gc);
																paint(cs,g);
																	break;
										}
										if(e.xbutton.button == 3){
											cairo_surface_destroy(cs); // destroy cairo surface
											XCloseDisplay(dpy);
											return 0;
											break;
										}

								}
				case KeyPress:
				{
						if(e.xkey.keycode == 57) {
							char nv_grille[12] = {0};
							char repert[] = "grilles/";
						printf("Quelle grille voulez vous ? :" );
						scanf("%s", nv_grille );
						printf("\n" );
						init_grille_from_file(strcat(repert, nv_grille), &g);
						alloue_grille (g.nbl, g.nbc, &gc);
						efface_paint(cs);
						paint(cs,g);


					}
					if(e.xkey.keycode == 54){				//c
						activC ++;
					commande_cyclique(activC);

					}
					if(e.xkey.keycode == 55){

							*activation_vieillesse +=1;
					}//v

				else break;
				}
				default : break;
				}
			 }




		// n= 57;
			/*	switch(e.xbutton.button){
					case 1 :
					{
						evolue(&g,&gc);
						break;

					}
					case 3 : break;
					default : break;
				}


		} else  break; */



	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;

}
