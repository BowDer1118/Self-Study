package com.imooc.spring.aop.service;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.text.SimpleDateFormat;
import java.util.Date;

//實現InvocationHandler也就是JDK的反射類，用於在動態代理中對目標method進行增強
//InvocationHandler就類似於AOP通知中的環繞通知
public class ProxyInvocationHandler implements InvocationHandler {
    private Object target; //持有目標物件
    private ProxyInvocationHandler(Object target){
        this.target=target;
    }

    /**
     * 實作Invoke方法，對目標的method進行增強
     * @param proxy 代理類的物件
     *
     * @param method 目標method的物件
     *
     * @param args 目標method所接收的參數列表
     *
     * @return 目標method執行後的回傳值
     * @throws Throwable 目標method拋出的異常物件
     */
    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        //加入代理類的增強功能(相當於AOP的前置通知)
        String timeForatted=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss SSS").format(new Date());
        System.out.println("代理前置功能:"+timeForatted);
        //執行代理目標的method
        Object ret=method.invoke(target,args);
        return ret; //將目標method的回傳值返回
    }

    public static void main(String[] args) {
        //創建接口
        UserService userService=new UserServiceImpl();
        //產生InvocationHandler物件:傳入接口
        ProxyInvocationHandler proxyInvocationHandler=new ProxyInvocationHandler(userService);
        //創建基於userService接口的動態代理類:將Interface的加載器、Interface本體、InvocationHandler物件
        UserService userServiceProxy= (UserService)Proxy.newProxyInstance(
                userService.getClass().getClassLoader(), userService.getClass().getInterfaces(),
                proxyInvocationHandler);
        //基於代理物件調用method
        userServiceProxy.createUser();


        EmployeeService employeeService=new EmployeeServiceImpl();
        EmployeeService employeeServiceProxy=(EmployeeService) Proxy.newProxyInstance(employeeService.getClass().getClassLoader()
                ,employeeService.getClass().getInterfaces(),
                new ProxyInvocationHandler(employeeService));
        employeeServiceProxy.createEmployee();
    }
}
