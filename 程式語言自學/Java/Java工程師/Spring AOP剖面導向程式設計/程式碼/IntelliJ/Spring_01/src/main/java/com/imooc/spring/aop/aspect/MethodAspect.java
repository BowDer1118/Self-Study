package com.imooc.spring.aop.aspect;

import org.aspectj.lang.JoinPoint;

import java.text.SimpleDateFormat;
import java.util.Date;

//針對method的切面類
public class MethodAspect {
    //切面方法，用於擴展額外的功能
    //參數JoinPoint:連接點，通過連接點可以獲取目標類/方法的訊息
    public void printExecutionTime(JoinPoint joinPoint){
        //時間格式方式
        SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss SSS");
        //格式當前系統時間
        String now=sdf.format(new Date());
        //獲取到目標物件的類別名稱
        String className=joinPoint.getTarget().getClass().getName();
        //獲取到目標執行的method名稱
        String methodName=joinPoint.getSignature().getName();
        //獲取目標method所接收的參數
        Object[] args=joinPoint.getArgs();
        System.out.println("---->"+now+":"+className+"."+methodName);
        System.out.println("---->參數個數:"+args.length);
        for(Object arg:args){
            System.out.println("---->參數:"+arg.getClass().getSimpleName()+" "+arg);
        }
    }

    //後置通知
    public void doAfter(JoinPoint joinPoint){
        System.out.println("<----觸發後置通知");
    }

    //返回後通知要執行的函數:第二個參數為目標method執行後的返回值
    public void doAfterReturning(JoinPoint joinPoint,Object ret){
        System.out.println("<----返回後通知，返回值類型:"+ret);
    }

    //異常後通知要執行的函數:第二個參數為Throwable，是所有異常的父類
    public void doAfterThrowing(JoinPoint joinPoint,Throwable th){
        System.out.println("<----異常通知:"+th.getMessage());
    }
}
