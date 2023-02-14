package com.imooc.springmvc.controller;

import com.imooc.springmvc.entity.User;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.ModelAndView;

import java.util.Date;

@Controller
//在類上使用RequestMapping表示訪問method的前綴
@RequestMapping("/um")
public class URLMappingContrlloer {
    @GetMapping("/g")
    @ResponseBody
    public String getMapping(String name){ //處理get類型的request
        System.out.println(name);
        return "This is get method";
    }

    @PostMapping("p")
    @ResponseBody
    public String postMapping(@RequestParam("username") String userName, String password){ //處理post類型的request
        System.out.println(userName+" "+password);
        return "This is post method";
    }

//    @PostMapping("/p1")
    @ResponseBody
    public String postMapping1(User user){
        System.out.println(user);
        return "This is post method";
    }

//    @PostMapping("/p1")
    @ResponseBody
    public String postMapping2(String username,
                               Long password,
                               @DateTimeFormat(pattern = "yyyy-MM-dd") Date createTime){
        System.out.println(username+password+createTime.toString());
        return username+password+createTime.toString();
    }

    @PostMapping("/p1")
    @ResponseBody
    public String postMapping3(User user){
        System.out.println(user);
        return user.toString();
    }

    /**
     *
     * @return 一個ModelAndView物件，用來攜帶數據跳轉畫面
     */
    @GetMapping("/view")
    public ModelAndView showView(Integer userId){
        //SpringMVC提供的物件，將要跳轉的頁面地址填入
        ModelAndView modelAndView=new ModelAndView("/view.jsp");
        User user=new User();
        if(userId==1){
            user.setUsername("Lily");
        }else if(userId==2){
            user.setUsername("Smith");
        }else if(userId==3){
            user.setUsername("Lina");
        }
        /**
         * 透過ModelAndView中的addObject()
         * 在當前的Request加入一個物件攜帶到指定的頁面
         * 語法:ModelAndView.addObject(識別名稱,物件);
         */
        modelAndView.addObject("u",user);
        return modelAndView;
    }

    //使用String與ModelMap實現ModelAndView功能

    /**
     * Controller的method返回String的情況
     * 1.method被@ResponseBody描述:SpringaMVC直接將該String以String的方式response給客戶端
     * 結果為一個字串顯示在瀏覽器上
     * 2.method不被@ResponseBody描述:SpringMVC將處理String對String指向的view進行處理並結合ModelMap進行渲染
     * 結果為一個JSP頁面顯示在瀏覽器上
     */
    @GetMapping("/xxxx")
    public String showView1(Integer userId, ModelMap modelMap){
        String view="/view.jsp";
        User user=new User();
        if(userId==1){
            user.setUsername("Lily");
        }else if(userId==2){
            user.setUsername("Smith");
        }else if(userId==3){
            user.setUsername("Lina");
        }
        //與modelAndView.addObject()功能相同
        modelMap.addAttribute("u",user);
        return view;
    }
}
