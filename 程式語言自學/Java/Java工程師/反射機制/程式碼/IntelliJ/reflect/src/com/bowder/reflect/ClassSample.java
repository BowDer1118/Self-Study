package com.bowder.reflect;

import com.bowder.reflect.entity.Employee;

//使用Class類動態加載Class
public class ClassSample {
    public static void main(String[] args) {
        try {
            //使用Class.forName將調用靜態塊加載Class到JVM中，並返回該Class
            Class employeeClass=Class.forName("com.bowder.reflect.entity.Employee");
            System.out.println("Employee已被加載到JVM");
            //使用newInstance()會調用默認的Constructor來構造並返回Object類(需要強制轉換)
            Employee employee=(Employee) employeeClass.newInstance();
            System.out.println(employee);
        } catch (ClassNotFoundException e) { //forName加載Class失敗時會拋出
            e.printStackTrace();
        } catch (InstantiationException e) { //物件創造失敗時會拋出(例如抽象類)
            e.printStackTrace();
        } catch (IllegalAccessException e) { //在外部訪問private等級時會拋出
            e.printStackTrace();
        }
    }
}
