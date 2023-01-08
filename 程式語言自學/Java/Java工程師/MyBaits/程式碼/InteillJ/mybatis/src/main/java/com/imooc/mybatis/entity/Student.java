package com.imooc.mybatis.entity;

public class Student {
    private Integer id;
    private Integer regNo;
    private String name;
    private String sex;
    private int age;
    private String grade;
    private String major;

    @Override
    public String toString() {
        return "Student{" +
                "用戶編號=" + id +
                ", 學號=" + regNo +
                ", 姓名='" + name + '\'' +
                ", 性別='" + sex + '\'' +
                ", 年齡=" + age +
                ", 年級='" + grade + '\'' +
                ", 專業='" + major + '\'' +
                '}';
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getRegNo() {
        return regNo;
    }

    public void setRegNo(Integer regNo) {
        this.regNo = regNo;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getGrade() {
        return grade;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }

    public String getMajor() {
        return major;
    }

    public void setMajor(String major) {
        this.major = major;
    }
}
