package com.bowder.reflect;

import com.bowder.reflect.entity.Employee;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

//使用getDeclared獲取所有權限修飾的屬性或函數
public class getDeclaredSample {
    public static void main(String[] args) {
        Class employeeClass= null;
        try {
            employeeClass = Class.forName("com.bowder.reflect.entity.Employee");
            Constructor constructor=employeeClass.getConstructor(new Class[]{Integer.class,String.class,Float.class,String.class});
            Employee employee=(Employee) constructor.newInstance(new Object[]{100,"寶德",60000.0f,"資訊部"});
            //使用getDeclaredFields()獲取所有屬性
            Field[] fields=employeeClass.getDeclaredFields();
            //遍歷所有屬性
            for(Field field:fields){
//                System.out.println(field.getName());
                //判斷權限修飾符
                if(field.getModifiers()==1){ //1:public
                    Object val=field.get(employee);
                    System.out.println(field.getName()+":"+val);
                }else if(field.getModifiers()==2){//2:private
                    //獲取getter函數名稱
                    String methodName="get"+field.getName().substring(0,1).toUpperCase()+field.getName().substring(1);
                    //獲取方法物件
                    Method getMethod=employeeClass.getMethod(methodName);
                    //輸出返回值
                    Object ret=getMethod.invoke(employee);
                    System.out.println(ret);
                }
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }

    }
}
