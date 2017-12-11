#include "Segmentation/main.h"
#include "Reseau_de_Neuronne/main.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

typedef struct
{
  GtkBuilder *builder;
  gpointer user_data;
  GtkImage *image;
  int nbcharacters;
  float **mats;
  GtkEntry *entry;
  char* filename;
} SGlobalData;
void callback_about (GtkMenuItem *menuitem, gpointer user_data);
void analysebuttonpressed(GtkMenuItem *menuitem, gpointer user_data);

int main(int argc, char *argv[]) {
  GtkWidget *fenetre_principale = NULL;
  SGlobalData data;
  GError *error = NULL;
  gchar *filename = NULL;
  /* Initialisation de la bibliothèque Gtk. */
  gtk_init(&argc, &argv);

  /* Ouverture du fichier Glade de la fenêtre principale */
  data.builder = gtk_builder_new();

  /* Création du chemin complet pour accéder au fichier test.glade. */
  /* g_build_filename(); construit le chemin complet en fonction du système */
  /* d'exploitation. ( / pour Linux et \ pour Windows) */
  filename =  g_build_filename ("GUI/GUI.glade", NULL);

  /* Chargement du fichier test.glade. */
  gtk_builder_add_from_file (data.builder, filename, &error);
  g_free (filename);
  if (error)
  {
    gint code = error->code;
    g_printerr("%s\n", error->message);
    g_error_free (error);
    return code;
  }

  /* Affectation des signaux de l'interface aux différents CallBacks. */
  gtk_builder_connect_signals (data.builder, &data);

  /* Récupération du pointeur de la fenêtre principale */
  fenetre_principale = GTK_WIDGET(gtk_builder_get_object (data.builder, "window1"));
  data.image = GTK_IMAGE(gtk_builder_get_object (data.builder, "image1"));
  data.entry = GTK_ENTRY(gtk_builder_get_object (data.builder, "entry1"));
  /* Affichage de la fenêtre principale. */
  gtk_widget_show_all (fenetre_principale);

  gtk_main();
  //if (argc < 2) {return 1;}
/*  char c = 97;
  for (size_t j = 0; j<10; j++){
    for (int i = 0; i<nbcharacters; i++){
      if (mats[i][0] != -2){
        learn(mats[i], c);
        c += 1;
      }
    }
    c = 97;
  }*/
  return 0;
}
static GtkImage* create_image (SGlobalData *data)
{
  gtk_image_set_from_file (data->image, data->filename);
  return data->image;
}
void postbuttonpressed(GtkMenuItem* UNUSED(menuitem), gpointer user_data)
{
  SGlobalData *data = (SGlobalData*) user_data;
  int nbcharacters = 0;
  data->nbcharacters = nbcharacters;
  data->mats = decoupe(data->filename,&data->nbcharacters);
  data->filename = "bin.bmp";
  create_image(data);
}
void writeres(char *res)
{
  FILE *f = fopen("file.txt", "w");
  fprintf(f, "%s\n",res);
  fclose(f);
}
void analysebuttonpressed(GtkMenuItem* UNUSED(menuitem), gpointer user_data)
{
  SGlobalData *data = (SGlobalData*) user_data;
  char* a = malloc(data->nbcharacters);
  char c;
  for (int i = 0; i<data->nbcharacters; i++){
    c = result(data->mats[i]);
    *(a+i) = c;
  }
  gtk_entry_set_text(data->entry, a);
  writeres(a);
  free(data->mats);
  free(a);

}

void quit(GtkMenuItem* UNUSED(menuitem), gpointer UNUSED(user_data))
{
  gtk_main_quit();
}
void callback_about (GtkMenuItem* UNUSED(menuitem), gpointer user_data)
{
  /* Transtypage du pointeur user_data pour récupérer nos données. */
  SGlobalData *data = (SGlobalData*) user_data;
  GtkWidget *dialog = NULL;
  dialog = GTK_WIDGET(gtk_builder_get_object (data->builder, "filechooserdialog1"));
  gtk_dialog_run (GTK_DIALOG (dialog));
  char *filename;
  GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
  filename = gtk_file_chooser_get_filename (chooser);
  /* On cache la fenêtre de dialogue. Si on la détruisait le prochain appel */
  /* à ce callback provoquerait un segdefault! */
  gtk_widget_hide (dialog);
  data->filename = filename;
  create_image(data);
}
