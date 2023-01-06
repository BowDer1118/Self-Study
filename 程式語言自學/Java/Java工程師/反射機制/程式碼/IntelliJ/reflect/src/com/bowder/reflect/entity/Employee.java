package com.bowder.reflect.entity;

public class Employee  {
    //使用靜態塊(只有類被加載時會被呼叫，且只會執行一次)
    static{
        System.out.println("Employee已被加載到JVM並完成初始化");
    }
    private Integer eno; //編號
    public String ename; //姓名
    private Float salary;//薪資
    private String dname;//部門名稱

    //Default Constructor
    public Employee(){
        System.out.println("默認構造方法已被執行");
    }
    //帶參構造方法
    public Employee(Integer eno,String ename,Float salary,String dname){
        this.eno=eno;
        this.ename=ename;
        this.salary=salary;
        this.dname=dname;
        System.out.println("Employee帶參構造方法已被執行");
    }

    @Override
    public String toString() {
        return "Employee{" +
                "eno=" + eno +
                ", ename='" + ename + '\'' +
                ", salary=" + salary +
                ", dname='" + dname + '\'' +
                '}';
    }

    public Integer getEno() {
        return eno;
    }

    public void setEno(Integer eno) {
        this.eno = eno;
    }

    public String getEname() {
        return ename;
    }

    public void setEname(String ename) {
        this.ename = ename;
    }

    public Float getSalary() {
        return salary;
    }

    public void setSalary(Float salary) {
        this.salary = salary;
    }

    public String getDname() {
        return dname;
    }

    public void setDname(String dname) {
        this.dname = dname;
    }

    //更新員工薪水
    public Employee updateSalary(Float val){
        this.salary=this.salary+val;
        System.out.println(this.ename+"調薪至"+this.salary+"元");
        return this;
    }
}
