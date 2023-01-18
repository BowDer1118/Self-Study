package com.imooc.spring.ioc.entity;

public class Child {
    private String name;
    private Apple apple; //Child喜歡吃的蘋果

    public Child() {
    }

    public Child(String name, Apple apple) {
        this.name = name;
        this.apple = apple;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Apple getApple() {
        return apple;
    }

    public void setApple(Apple apple) {
        this.apple = apple;
    }

    public void eat(){
        System.out.println(name+"吃到了"+apple.getOrigin()+"種植的"+apple.getTitle());
    }
}
