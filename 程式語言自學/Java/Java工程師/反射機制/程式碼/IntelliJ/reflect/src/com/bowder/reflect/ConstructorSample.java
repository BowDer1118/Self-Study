package com.bowder.reflect;

import com.bowder.reflect.entity.Employee;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

//使用Constructor類調用不同構造方法
public class ConstructorSample {
    public static void main(String[] args) {
        try {
            //先加載類到JVM
            Class empolyeeClass=Class.forName("com.bowder.reflect.entity.Employee");
            //透過getConstructor來獲得特定的構造方法
            //創建Class[]並放入要指定的Constructor接收的參數類型
            Class[] constructorParameterDataTypes=new Class[]{
                    Integer.class,String.class,Float.class,String.class
            };
            //透過傳入Class[]來獲取指定的Constructor物件
            Constructor constructor=empolyeeClass.getConstructor(constructorParameterDataTypes);
            //準備要傳給Constructor的參數
            Object[] parameters=new Object[]{100,"寶德",60000.0f,"軟體工程部"};
            //使用constructor物件的newInstance()透過傳入參數來執行constructor構造出物件
            Employee employee=(Employee) constructor.newInstance(parameters);
            System.out.println(employee);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) { //沒有指定的構造方法時拋出
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            //當被調用的方法拋出異常而沒有被處理時，會由此拋出異常
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
    }
}
