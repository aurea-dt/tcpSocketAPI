//////////////////////////////////////////////////////////////////////////////
//	My_guiClass.cpp
//	AUTOR
//	Aurea Desarrollo Tecnológico.
//	FECHA
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "My_guiClass.h"
#include "My_callbacks.h"
using namespace std;
T_GTKapp *GTKapp;
ADT_TCPSocket* myServer;
//------------------------------------------------------------------------------
T_GTKapp::T_GTKapp()
{
}
//------------------------------------------------------------------------------
T_GTKapp::T_GTKapp(const char *fileName)
{
        buildFromFile(fileName);
	window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
	server_entry = GTK_WIDGET (gtk_builder_get_object (builder, "server_entry"));
	port_entry = GTK_WIDGET (gtk_builder_get_object (builder, "port_entry"));
        //add your code here...
     	//myTheme=  gtk_icon_theme_get_default();
	//gtk_icon_theme_append_search_path(myTheme, "icons/");  

	//main window items...


	g_object_unref (G_OBJECT (builder));
}
//------------------------------------------------------------------------------
//		Member functions
//------------------------------------------------------------------------------
/*
void T_GTKapp::guiInit()
{
	guiRefresh() ;
}
//------------------------------------------------------------------------------
void T_GTKapp::guiRefresh()
{	

}
//------------------------------------------------------------------------------
const char* T_GTKapp::fileChooserDialog(vector<char*> filters)
{
	char *filename = NULL;
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new ("Open Image",
					      (GtkWindow*)window,
					      GTK_FILE_CHOOSER_ACTION_OPEN,
					      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					      NULL);

	for(unsigned int i=0; i<filters.size(); i++)
	{
		GtkFileFilter *filter = gtk_file_filter_new ();
		gtk_file_filter_add_pattern (filter, filters[i]);
		gtk_file_chooser_add_filter((GtkFileChooser*)dialog, filter);
	}

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	}
	gtk_widget_destroy (dialog);
	return filename;
}
//------------------------------------------------------------------------------
*/
