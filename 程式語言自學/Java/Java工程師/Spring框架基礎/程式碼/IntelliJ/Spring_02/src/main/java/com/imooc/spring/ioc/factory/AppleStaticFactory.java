package com.imooc.spring.ioc.factory;

import com.imooc.spring.ioc.entity.Apple;

//靜態工廠
public class AppleStaticFactory {
    //透過靜態方法創建物件，隱藏創建的細節
    public static Apple createSweetApple(){
        System.out.println("使用靜態工廠方法產生物件");
        Apple apple=new Apple();
        apple.setTitle("紅富士");
        apple.setOrigin("歐洲");
        apple.setColor("紅色");
        return apple;
    }
}
