package com.imooc.spring.ioc.entity;

public class Apple {
    private String title;
    private String color;
    private String origin;

    @Override
    public String toString() {
        return "Apple{" +
                "title='" + title + '\'' +
                ", color='" + color + '\'' +
                ", origin='" + origin + '\'' +
                '}';
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
}
