package com.imooc.restful.interceptor;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class AccessHistoryInterceptor implements HandlerInterceptor {
    private Logger logger
            = LoggerFactory.getLogger(AccessHistoryInterceptor.class);
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        StringBuilder log=new StringBuilder();
        //獲取用戶IP
        log.append(request.getRemoteAddr());
        log.append("|");
        //獲取用戶訪問的URL
        log.append(request.getRequestURL());
        log.append("|");
        //獲取客戶端環境
        log.append(request.getHeader("user-agent"));
        //將資訊寫入日誌中
        logger.info(log.toString());
        //紀錄用戶資訊
        return true;
    }
}
