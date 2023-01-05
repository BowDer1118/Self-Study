#include <stdio.h>
#include <gtk/gtk.h>

/*待綁定的事件:輸出HelloWorld*/
static void print_hello(GtkWidget *widget,gpointer data){
    g_print("Hello World\n");
}
/*帶綁定事件:視窗啟動*/
static void activate(GtkApplication *app,gpointer user_data){
    //創建Widget
    GtkWidget *window= gtk_application_window_new(app);
    //設定視窗名稱
    gtk_window_set_title(GTK_WINDOW(window),"HelloWorld");//使用GTK_WINDOW()強轉資料類型
    //設定尺寸
    gtk_window_set_default_size(GTK_WINDOW(window),200,200);
    //橫向放置的按鈕容器
    GtkButtonBox *buttonBox= (GtkButtonBox *) gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    //將容器加入Widget中
    gtk_container_add(GTK_WINDOW(window),buttonBox);
    //按鈕物件
    GtkButtonBox *button= gtk_button_new_with_label("Hello World");
    //向容器添加按鈕
    gtk_container_add(buttonBox,button);
    //綁定print_hello到按鈕的clicked事件上
    g_signal_connect(button,"clicked",G_CALLBACK(print_hello),NULL);
    //綁定gtk_window_close到按鈕上
    g_signal_connect_swapped(button,"clicked", G_CALLBACK(gtk_window_close),window);

    gtk_widget_show_all(window);
}

int main(int argc,char **argv) {
    GtkApplication  *app= gtk_application_new("bow.der",G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);

    //啟動app
    int status= g_application_run(app,argc,argv);
    //釋放app的引用
    g_object_unref(app);
    return status;
}
