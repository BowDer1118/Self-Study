package com.bowder.i18n;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.util.Properties;

public class Application {
    public static void say(){
        Properties properties=new Properties();
        //獲取設定檔
        String configPath=Application.class.getResource("/config.properties").getPath();
        try {
            //轉換編碼
            configPath=new URLDecoder().decode(configPath,"UTF-8");
            properties.load(new FileInputStream(configPath));
            //獲取language屬性的值
            String language=properties.getProperty("language");
            //動態加載Class
            I18N i18n=(I18N) Class.forName(language).newInstance();
            System.out.println(i18n.say());
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Application.say();
    }
}
