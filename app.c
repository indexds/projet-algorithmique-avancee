#include "app.h"

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *textbox1, *textbox2;
    GtkWidget *image;
    (void)user_data;

    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "Akinator mais que pour les animaux");
    gtk_window_set_default_size(GTK_WINDOW(window), 750, 750);

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    textbox1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), textbox1, 0, 0, 1, 1);

    image = gtk_image_new_from_file("dog.jpg");
    gtk_widget_set_size_request(image, 300, 300);
    gtk_grid_attach(GTK_GRID(grid), image, 1, 0, 1, 1);

    textbox2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), textbox2, 2, 0, 1, 1);

    gtk_window_present(GTK_WINDOW(window));
}

int app(void)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);

    return status;
}
