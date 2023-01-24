package com.imooc.spring.aop.aspect;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.springframework.stereotype.Component;

import java.text.SimpleDateFormat;
import java.util.Date;

/*
* 使用@Component註解將切面類加入IoC容器中管理
* 使用@Aspect註解標註MethodChecker類為切面擴展類
* */
@Component
@Aspect
public class MethodChecker {
    //使用@Around註解標示此method為環繞通知，並加入pointcut的expression表達式指定作用範圍
    @Around("execution(public * com.imooc..*Service.*(..))")
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
}
