//////////////////////////////////////////////////////////////////////////////
//	My_guiClass.h
//	AUTOR
//	Aurea Desarrollo Tecnológico.
//	FECHA
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
//////////////////////////////////////////////////////////////////////////////
#ifndef MY_GUICLASS_H
#define MY_GUICLASS_H
// your public header include
#include "ADT_GTK.h"
#include "ADT_TCPSocket.h"
// the declaration of your class...
//------------------------------------------------------------------------------
class T_GTKapp : public ADT_GTK
{
 public:

	GtkWidget *window;

	
	//main window items
	//GtkWidget *autocap_checkbutton;
	//GtkIconTheme *myTheme;
	
	GtkWidget* server_entry;
	GtkWidget* port_entry;
	//member functions
	T_GTKapp();
	T_GTKapp(const char *fileName);

	//void guiInit();	
	//const char* fileChooserDialog(vector<char*> filters);
	//void guiRefresh();

};
//------------------------------------------------------------------------------
extern T_GTKapp *GTKapp;
extern ADT_TCPSocket* myServer;
#endif
