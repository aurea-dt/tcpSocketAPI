//////////////////////////////////////////////////////////////////////////////
//	main.cpp
//	AUTOR
//	Aurea Desarrollo Tecnológico.
//	FECHA
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
//gcc -Wall -g main.c -o GTKapp -export-dynamic `pkg-config --cflags --libs gtk+-2.0`
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <gtk/gtk.h>
#include "My_guiClass.h"
#include "My_callbacks.h"

using namespace std;
//------------------------------------------------------------------------------
int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	if(argc < 2)
	{
		cerr << "too few arguments" << endl;
		return EXIT_FAILURE;
	}
	
	GTKapp =new T_GTKapp("ui.glade");
	//g_idle_add(on_idle_callback, NULL);
        gtk_widget_show (GTKapp->window);
	//GTKapp->guiInit();
	myServer = new ADT_TCPSocket(atoi(argv[1]));
        gtk_main ();
 return 0;
}

//gcc -Wall -g -o tutorial main.c -export-dynamic `pkg-config --cflags --libs gtk+-2.0`
