//////////////////////////////////////////////////////////////////////////////
//	My_callbacks.cpp
//	AUTOR
//	Aurea Desarrollo Tecnológico.
//	FECHA 
//----------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
//////////////////////////////////////////////////////////////////////////////
#include "My_callbacks.h"
#include "My_guiClass.h"
#include <iostream>
using namespace std;
//------------------------------------------------------------------------------
int on_idle_callback(void *data)
{

 return true;
}
//------------------------------------------------------------------------------
void on_main_window_destroy(GtkObject *object, void* user_data)
{
        gtk_main_quit();
}
//------------------------------------------------------------------------------
void hide_on_window_delete_event(GtkObject *object, void* user_data)
{//cout<<"hide"<<endl;
	gtk_widget_hide_on_delete((GtkWidget*)object);
}
//------------------------------------------------------------------------------
void on_connect_action_activate(GtkAction *action, void* user_data)
{
	cout << "on_connect_action_activate" << endl;
	const char* server = gtk_entry_get_text((GtkEntry *)GTKapp->server_entry);
	const char* port = gtk_entry_get_text((GtkEntry *)GTKapp->port_entry);
	cout << "server: " << server << endl;
	cout << "port: " << port << endl;
	myServer->connectToServer(server, atoi(port));
}
//------------------------------------------------------------------------------
void on_sendAsClient_action_activate(GtkAction *action, void* user_data)
{
	const char* server = gtk_entry_get_text((GtkEntry *)GTKapp->server_entry);
	const char* port = gtk_entry_get_text((GtkEntry *)GTKapp->port_entry);
	cout << "server: " << server << endl;
	cout << "port: " << port << endl;
	myServer->sendData(server, atoi(port), "HELLO", 5);
}
//------------------------------------------------------------------------------
void on_sendAsServer_action_activate(GtkAction *action, void* user_data)
{
	cout << "on_sendAsServer_action_activate" << endl;
	myServer->sendData("HELLO", 5);
}
//------------------------------------------------------------------------------
