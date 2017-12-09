#include <gtk/gtk.h>
#include <glib/gprintf.h>  // g_sprintf
#include <stdlib.h>        // system (web link)
#include <gdk/gdkkeysyms.h>// GDK_Escape

/* Well, by golly, this program uses widgets: */
typedef struct {
	GtkWidget *window1;
} AppWidgets;



void file_save_as(){
}

void file_save(GtkWidget *widget){
}

void file_open(GtkWidget *widget){
}

void file_new(GtkWidget *widget){
}

/* Show the About box */
void Select_file_click(GtkWidget *widget){
	gtk_dialog_run(GTK_DIALOG(widget));
	gtk_widget_hide(widget);
}

/* Somebody clicked on our web page link */
void link_click(GtkWidget *widget){
	const gchar *link=gtk_link_button_get_uri(GTK_LINK_BUTTON(widget));
	gchar *lloc=g_strconcat("htmlview ",link,NULL);
	system(lloc);
	g_slice_free(gchar,lloc);
	g_printf("clicked %s\n",gtk_widget_get_name(widget));
}




/* Somebody ran our program */
int main(int argc, char **argv) {
	GtkBuilder *builder;
	AppWidgets *app = g_slice_new(AppWidgets);
	GError *err = NULL;

	gtk_init(&argc, &argv);
	builder=gtk_builder_new();
	gtk_builder_add_from_file(builder, "GUI.glade", &err);

	if (err) {
		g_error(err->message);
		g_error_free(err);
		g_slice_free(AppWidgets, app);
		return 1;
	}

	//Get handles to our app widgets.
	#define appGET(xx) \
	app->xx=GTK_WIDGET(gtk_builder_get_object(builder,#xx))
	appGET(window1);
	gtk_builder_connect_signals(builder, app);
	g_object_unref(G_OBJECT(builder));

	gtk_main();
	g_slice_free(AppWidgets, app);
	return 0;
}
