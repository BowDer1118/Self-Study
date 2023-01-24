package com.imooc.spring.aop.aspect;

import org.aspectj.lang.ProceedingJoinPoint;

import java.text.SimpleDateFormat;
import java.util.Date;

//檢查method的執行效率
public class MethodChecker {
    //ProceedingJoinPoint是JoinPoint的升級版本，在原有的功能以外，還可以控制目標method是否執行
    public Object check(ProceedingJoinPoint pjp) throws Throwable {

        try {
            long startTime=new Date().getTime();
            //執行目標method，並接收返回值
            Object ret=pjp.proceed();
            long endTime=new Date().getTime();
            long duration=endTime-startTime;
            if(duration>=1000){ //如果耗時大於1000毫秒
                SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss SSS");
                String timeFormatted=sdf.format(new Date());
                String className=pjp.getTarget().getClass().getSimpleName();
                String classMethod=pjp.getSignature().getName();
                System.out.println("===="+timeFormatted+":"+className+"."+classMethod+"took "+duration+" (ms) is too long!");
            }
            return ret; //回傳目標方法的返回值
        } catch (Throwable throwable) {
            //如果捕獲到異常，要將異常丟出去給系統中正常的處理程序處理，如果不這麼做，則異常就等於被圍繞通知吃掉了
            System.out.println("在圍繞通知中，捕獲到異常:" + throwable.getMessage());
            throw throwable;
        }
    }

    public Object welcome(ProceedingJoinPoint pjp) throws Throwable {
        System.out.println("歡迎光臨書店");
        Object ret=pjp.proceed();
        System.out.println("歡迎再次光臨");
        return ret;
    }
}
