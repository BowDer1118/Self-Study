package com.imooc.spring.ioc.service;

import com.imooc.spring.ioc.dao.UserDao;

public class UserService {
    private UserDao userDao;

    public void createUser(){
        System.out.println("調用創建使用者業務程式碼");
        userDao.insert();
    }

    public UserDao getUserDao() {
        return userDao;
    }

    public void setUserDao(UserDao userDao) {
        this.userDao = userDao;
    }
}
