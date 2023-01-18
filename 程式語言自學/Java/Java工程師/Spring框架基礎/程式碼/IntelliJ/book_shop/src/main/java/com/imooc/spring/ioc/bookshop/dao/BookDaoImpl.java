package com.imooc.spring.ioc.bookshop.dao;

public class BookDaoImpl implements BookDao{
    public void insert(){
        System.out.println("向MySQL Book table插入一條資料");
    }
}
