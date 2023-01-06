package com.bowder.reflect;

import com.bowder.reflect.entity.Employee;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

//利用Method類方法調用method
public class MethodSample {
    public static void main(String[] args) {
        try {
            Class employeeClass=Class.forName("com.bowder.reflect.entity.Employee");
            Constructor constructor=employeeClass.getConstructor(new Class[]{Integer.class,String.class,Float.class,String.class});
            Employee employee=(Employee) constructor.newInstance(new Object[]{100,"寶德",60000.0f,"資訊工程部"});
            //透過method的名稱來獲取該method但必須指定參數，因為可能會有overloading的函數
            Method updateSalaryMethod=employeeClass.getMethod("updateSalary",new Class[]{Float.class});
            //使用invoke()對指定的class執行函數並傳入參數
            Employee updatedEmployee=(Employee) updateSalaryMethod.invoke(employee,new Object[]{40000.0f});
            System.out.println(updatedEmployee);
        } catch (Exception e){
            e.printStackTrace();
        }

    }
}
