package com.imooc.spring.ioc.factory;

import com.imooc.spring.ioc.entity.Apple;

//使用工廠方法創建對象:IoC容器必須先對工廠類進行實例化再調用對應的方法產生物件
public class AppleFactoryInstance {
    //不使用static方法
    public Apple createSweetApple(){
        System.out.println("使用非靜態工廠方法產生物件");
        Apple apple=new Apple();
        apple.setTitle("紅富士");
        apple.setOrigin("歐洲");
        apple.setColor("紅色");
        return apple;
    }
}
