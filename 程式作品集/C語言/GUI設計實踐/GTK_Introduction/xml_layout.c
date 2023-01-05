#include <stdio.h>
#include <gtk/gtk.h>

/*待綁定的事件:輸出HelloWorld*/
static void print_string(GtkWidget *widget,gpointer data){
    char *str=(char*)data;
    g_print("Hello, %s\n",str);
}

int main(int argc,char **argv) {

    gtk_init(&argc,&argv);

    //用Builder解析XML文件
    GtkBuilder  *builder=gtk_builder_new();
    //用來指向錯誤訊息
    GError  *error=NULL;
    //檢查是否成功載入檔案
    if(gtk_builder_add_from_file(builder,"builder.ui",&error)==0){
        //載入失敗(輸出訊息)
        g_printerr("Error loading file: %s\n",error->message);
        g_clear_error(&error);
        return 1;
    }else{
        /*載入成功*/

        //從檔案內部獲取window物件(透過object_id獲取)
        GObject  *window= gtk_builder_get_object(builder,"window"); //window的class名稱為window
        //綁定destroy事件到window上
        g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
        //獲取按鈕物件
        GObject *button1= gtk_builder_get_object(builder,"button1");
        g_signal_connect(button1,"clicked",G_CALLBACK(print_string),"button1");
        GObject *button2= gtk_builder_get_object(builder,"button2");
        g_signal_connect(button2,"clicked",G_CALLBACK(print_string),"button2");
        GObject *quit= gtk_builder_get_object(builder,"quit");
        g_signal_connect(quit,"clicked",G_CALLBACK(gtk_main_quit),NULL);

        //釋放builder資源
        g_object_unref(builder);
        //啟動window窗口
        gtk_main();
    }
    return 0;
}
