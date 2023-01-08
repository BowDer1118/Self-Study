package com.bowder.junit;

public class Calculator {
    public int add(int a,int b){
        return a+b;
    }
    public int subtract(int a,int b){
        return a-b;
    }
    public int multiply(int a,int b){
        return a*b;
    }
    public double divide(int a,int b){
        if(b==0){
            throw new ArithmeticException("除數不能為0");
        }
        return (a*1d)/b;
    }
}
