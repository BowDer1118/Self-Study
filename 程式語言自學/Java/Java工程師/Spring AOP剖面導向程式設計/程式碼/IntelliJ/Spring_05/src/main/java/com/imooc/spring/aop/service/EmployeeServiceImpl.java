package com.imooc.spring.aop.service;

public class EmployeeServiceImpl implements EmployeeService{
    @Override
    public void createEmployee() {
        System.out.println("執行創建員工業務邏輯");
    }
}
