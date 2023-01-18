package com.imooc.spring.ioc.entity;

public class Apple {
    private String title; //品種
    private String color; //顏色
    private String origin; //產地

    public Apple(String title, String color, String origin) {
        this.title = title;
        this.color = color;
        this.origin = origin;
        System.out.println("使用帶參Constructor創建Apple物件:"+this.toString());
    }

    public Apple() {
        System.out.println("使用無參Constructor創建Apple物件:"+this.toString());
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public String getOrigin() {
        return origin;
    }

    public void setOrigin(String origin) {
        this.origin = origin;
    }

    @Override
    public String toString() {
        return "Apple{" +
                "title='" + title + '\'' +
                ", color='" + color + '\'' +
                ", origin='" + origin + '\'' +
                '}';
    }
}
