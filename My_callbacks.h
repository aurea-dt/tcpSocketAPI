////////////////////////////////////////////////////////////////////////////////
//	My_callbacks.h
//	AUTOR
//	Aurea Desarrollo Tecnológico.
//	FECHA
//------------------------------------------------------------------------------
//	DESCRIPCIÓN
//	Notas:	
//		
////////////////////////////////////////////////////////////////////////////////
#ifndef MY_CALLBACKS_H
#define MY_CALLBACKS_H

// your public header include
#include "ADT_GTK.h"
// the declaration of your class...
int on_idle_callback(void *data);
extern "C" void on_main_window_destroy	(GtkObject *object, void* user_data);
extern "C" void on_autocap_change	(GtkObject *object, void* user_data);
extern "C" void hide_on_window_delete_event(GtkObject *object, void* user_data); //oculatar la ventana en vez de destruirla
extern "C" void on_connect_action_activate(GtkAction *action, void* user_data);
extern "C" void on_sendAsClient_action_activate(GtkAction *action, void* user_data);
extern "C" void on_sendAsServer_action_activate(GtkAction *action, void* user_data);
#endif
