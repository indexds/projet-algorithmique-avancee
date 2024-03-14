#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *textbox1, *textbox2;
    GtkWidget *button_find_animal, *button_find_chars;
    (void)user_data;

    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "Akinator de Aldi");
    gtk_window_set_default_size(GTK_WINDOW(window), 310, 90);

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    textbox1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), textbox1, 0, 0, 1, 1);

    // Button "Find Animal"
    button_find_animal = gtk_button_new_with_label("Find Animal");
    gtk_grid_attach(GTK_GRID(grid), button_find_animal, 0, 1, 1, 1);

    // Button "Find Chars"
    button_find_chars = gtk_button_new_with_label("Find Characs.");
    gtk_grid_attach(GTK_GRID(grid), button_find_chars, 2, 1, 1, 1);

    textbox2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), textbox2, 2, 0, 1, 1);

    gtk_widget_set_visible(window, true); // Show all widgets
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